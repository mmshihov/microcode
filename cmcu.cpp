#include <QtGlobal>

#include "cmcu.h"
#include "cengineerror.h"

CMcu::CMcu(unsigned int stateDim,
           unsigned int controlInputDim,
           unsigned int controlOutputDim)
    : CFunctionalUnit(0, 0, controlInputDim, controlOutputDim)
    , mRomAddressRegister(stateDim)
{
    mRomAddressDim = stateDim;
}

CMcu::~CMcu() {}

void CMcu::SetRomAddress(unsigned int address) {
    CBitBlock block(RomAddressDim(), address);

    SetRomAddressRegisterWriteInput(block);
    RomAddressRegisterShift();
}

unsigned int CMcu::RomAddress() const {
    return mRomAddressRegister.Output().AsInt();
}

unsigned int CMcu::MinDimensionFor(unsigned int xmax) {
    unsigned int dim = 1;

    while (1) {
        unsigned int power = (1 << dim);

        if (power > xmax)
            return dim;

        if (power == 0)
            return 0;

        ++dim;
    }

    return 0;
}

unsigned int CMcu::PowerForDimension(unsigned int dim) {return 1 << dim;}

void CMcu::SetRomAddressRegisterWriteInput(const CBitBlock &value) {
    mRomAddressRegister.SetInput(value);
    mRomAddressRegister.ClearAllControls();
    mRomAddressRegister.SetMaskedControls(CRegister::WR);
}

void CMcu::RomAddressRegisterShift() {
    mRomAddressRegister.ShiftState();
}

void CMcu::ResetRomAddressRegister() {
    mRomAddressRegister.ClearAllControls();

    CBitBlock block(RomAddressDim(), 0);

    mRomAddressRegister.SetInput(block);
    mRomAddressRegister.SetMaskedControls(CRegister::WR);

    mRomAddressRegister.ShiftState();
}

void CMcu::DoReset() {
    CBitBlock zero(RomAddressDim(), 0);

    SetRomAddressRegisterWriteInput(zero);
    RomAddressRegisterShift();
}

//------------------------manual------------------------------
CManualMcu::CManualMcu(unsigned int stateDim, unsigned int controlInputDim, unsigned int controlOutputDim)
    : CMcu(stateDim, controlInputDim, controlOutputDim)
{
    CreateSharedRom();
}

const CRegister *CManualMcu::Register(unsigned int i) const {
    switch (i) {
    case ROM_ADDRESS_REGISTER_INDEX: return RomAddressRegister();
    }
    return 0;
}

CBitBlock CManualMcu::DoControlOutput() const {
    CRom::Address address;
    address.row = RomAddressRegister()->Output().AsInt();
    address.col = 0;

    return mProgramRom->Cell(address);
}

void CManualMcu::CreateSharedRom() {
    unsigned int colDims[1] = {ControlOutputDim()};
    CRom *prom = new CRom(PowerForDimension(RomAddressDim()), 1, colDims);
    SharedPtr<CRom> sharedRom(prom);
    mProgramRom = sharedRom;
}


//------------------------automate------------------------------
CAutomate::CAutomate(unsigned int stateDim,
                     unsigned int controlInputGroupDim,
                     unsigned int controlInputDim,
                     unsigned int controlOutputDim)
    : CMcu(stateDim, controlInputDim, controlOutputDim)
    , mGroupDim(controlInputGroupDim)
    , mGroupsCount((controlInputDim + controlInputGroupDim - 1)/controlInputGroupDim)
{}

CBitBlock CAutomate::ControlInputGroup(unsigned int index) const {
    if (index >= mGroupsCount) {
        const_cast<CAutomate*>(this)->mErrorState.SetMuxControlError(CErrorState::MCU_SOURCE, 1);
        return ControlInput().BitsAt(mGroupDim - 1, 0);
    }

    return ControlInput().BitsAt(mGroupDim*(index + 1) - 1, mGroupDim*index);
}


//--------------------------mili--------------------------------
CMiliAutomate::CMiliAutomate(unsigned int stateDim,
                             unsigned int controlInputGroupDim,
                             unsigned int controlInputDim,
                             unsigned int controlOutputDim)
    : CAutomate(stateDim, controlInputGroupDim, controlInputDim, controlOutputDim)
    , mGroupMux(controlInputGroupDim, MinDimensionFor((controlInputDim + controlInputGroupDim - 1)/controlInputGroupDim))
    , mStateMux(stateDim, controlInputGroupDim)
    , mControlOutputMux(controlOutputDim, controlInputGroupDim)
{
    CreateSharedRom();
}

const CRegister *CMiliAutomate::Register(unsigned int i) const {
    switch (i) {
    case STATE_REGISTER_INDEX: return RomAddressRegister();
    }
    return 0;
}

const CMultiplexor *CMiliAutomate::Multiplexor(unsigned int i) const {
    switch (i) {
    case GROUP_MUX_INDEX:   return &mGroupMux;
    case STATE_MUX_INDEX:   return &mStateMux;
    case CONTROL_MUX_INDEX: return &mControlOutputMux;
    }
    return 0;
}

const CRom *CMiliAutomate::Rom(unsigned int i) const {
    switch (i) {
    case PROGRAM_ROM_INDEX: return mProgramRom.raw();
    }
    return 0;
}

CBitBlock CMiliAutomate::DoControlOutput() const {
    return mControlOutputMux.Output();
}

void CMiliAutomate::DoSpreadInput() {
    CRom::Address address;
    address.row = RomAddress();
    address.col = 0;

    unsigned int groupIndex = mProgramRom->Cell(address).AsInt();
    if (groupIndex >= GroupsCount()) {
        mErrorState.SetMuxControlError(CErrorState::MCU_SOURCE, 1);
        groupIndex = GroupsCount() - 1;
    }

    mGroupMux.SetInputIndex(groupIndex);
    for (unsigned int i=0; i<GroupsCount(); ++i)
        mGroupMux.SetInput(i, ControlInputGroup(i));

    unsigned int colIndex = mGroupMux.Output().AsInt();

    mStateMux.SetInputIndex(colIndex);
    mControlOutputMux.SetInputIndex(colIndex);
    for (unsigned int j = 0; j<PowerForDimension(GroupDim()); ++j) {
        address.col = 1 + 2*j;
        mStateMux.SetInput(j, mProgramRom->Cell(address));

        address.col = 1 + 2*j + 1;
        mControlOutputMux.SetInput(j, mProgramRom->Cell(address));
    }

    SetRomAddressRegisterWriteInput(mStateMux.Output());
}

void CMiliAutomate::CreateSharedRom() {
    unsigned int romColCount = 1 + PowerForDimension(GroupDim()) * 2;
    unsigned int *romColDims = new unsigned int [romColCount];

    romColDims[0] = MinDimensionFor(GroupsCount() - 1);

    for (unsigned int i=0; i<PowerForDimension(GroupDim()); ++i) {
        romColDims[1 + i*2]     = RomAddressDim();
        romColDims[1 + i*2 + 1] = ControlOutputDim();
    }

    CRom *prom = new CRom(PowerForDimension(RomAddressDim()),
                          romColCount,
                          romColDims);
    SharedPtr<CRom> sharedRom(prom);
    mProgramRom = sharedRom;

    delete[] romColDims;
}


//---------------------------moore------------------------------
CMooreAutomate::CMooreAutomate(unsigned int stateDim,
                               unsigned int controlInputGroupDim,
                               unsigned int controlInputDim,
                               unsigned int controlOutputDim)
    : CAutomate(stateDim, controlInputGroupDim, controlInputDim, controlOutputDim)
    , mGroupMux(controlInputGroupDim, MinDimensionFor((controlInputDim + controlInputGroupDim - 1)/controlInputGroupDim))
    , mStateMux(stateDim, controlInputGroupDim)
{
    CreateSharedRom();
}

CBitBlock CMooreAutomate::DoControlOutput() const {
    CRom::Address address;
    address.row = RomAddress();
    address.col = 1 + PowerForDimension(GroupDim()); //Y - field (see picture in methodical)
    return mProgramRom->Cell(address);
}

const CRegister *CMooreAutomate::Register(unsigned int i) const {
    switch (i) {
    case STATE_REGISTER_INDEX: return RomAddressRegister();
    }
    return 0;
}

const CMultiplexor *CMooreAutomate::Multiplexor(unsigned int i) const {
    switch (i) {
    case GROUP_MUX_INDEX:   return &mGroupMux;
    case STATE_MUX_INDEX:   return &mStateMux;
    }
    return 0;
}

const CRom *CMooreAutomate::Rom(unsigned int i) const {
    switch (i) {
    case PROGRAM_ROM_INDEX: return mProgramRom.raw();
    }
    return 0;
}

void CMooreAutomate::DoSpreadInput() {
    CRom::Address address;
    address.row = RomAddress();
    address.col = 0;

    unsigned int groupIndex = mProgramRom->Cell(address).AsInt();
    if (groupIndex >= GroupsCount()) {
        mErrorState.SetMuxControlError(CErrorState::MCU_SOURCE, 1);
        groupIndex = GroupsCount() - 1;
    }

    mGroupMux.SetInputIndex(groupIndex);
    for (unsigned int i=0; i<GroupsCount(); ++i)
        mGroupMux.SetInput(i, ControlInputGroup(i));

    unsigned int colIndex = mGroupMux.Output().AsInt();

    mStateMux.SetInputIndex(colIndex);
    for (unsigned int j = 0; j<PowerForDimension(GroupDim()); ++j) {
        address.col = 1 + j;
        mStateMux.SetInput(j, mProgramRom->Cell(address));
    }

    SetRomAddressRegisterWriteInput(mStateMux.Output());
}

void CMooreAutomate::CreateSharedRom() {
    unsigned int romColCount = 2 + PowerForDimension(GroupDim());
    unsigned int *romColDims = new unsigned int [romColCount];

    romColDims[0] = MinDimensionFor(GroupsCount() - 1);

    for (unsigned int i=0; i<PowerForDimension(GroupDim()); ++i)
        romColDims[1 + i] = RomAddressDim();

    romColDims[romColCount - 1] = ControlOutputDim();

    CRom *prom = new CRom(PowerForDimension(RomAddressDim()),
                          romColCount,
                          romColDims);
    SharedPtr<CRom> sharedRom(prom);
    mProgramRom = sharedRom;

    delete[] romColDims;
}



