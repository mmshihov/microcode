#include "cpc2dcalu1.h"

CPc2DcAlu1::CPc2DcAlu1()
    : CAlu(8, 0, Y_COUNT, P_COUNT)
    , mRg1(8)
    , mXor1(8)
    , mCt1(8)
{}

const CRegister *CPc2DcAlu1::Register(unsigned int index) const {
    switch (index) {
    case 1: return &mRg1;
    }
    return 0;
}

const CCounter *CPc2DcAlu1::Counter(unsigned int index) const {
    switch (index) {
    case 1: return &mCt1;
    }
    return 0;
}

const CXor *CPc2DcAlu1::Xor(unsigned int index) const {
    switch (index) {
    case 1: return &mXor1;
    }
    return 0;
}

CBitBlock CPc2DcAlu1::BusMaker(unsigned int index) const {
    switch (index) {
    case 1: return BusOut1();
    }
    return CBitBlock();
}

CBitBlock CPc2DcAlu1::DoDataOutput() const {
    if (ControlInput().IsSetAt(Y_BD1_OUT))
        return BusOut1();
    return CBitBlock();
}

CBitBlock CPc2DcAlu1::DoControlOutput() const {
    CBitBlock output(ControlOutputDim());
    output.SetBoolAt(P_RG1_7, mRg1.Output().IsSetAt(7));
    return output;
}

unsigned int CPc2DcAlu1::DoDataOutCount() const {
    return
            (ControlInput().IsSetAt(Y_BD1_OUT) ? 1 : 0)
            ;
}

CBitBlock CPc2DcAlu1::BusOut1() const {
    return mCt1.Output();
}

void CPc2DcAlu1::ClearAllControls() {
    mCt1.ClearAllControls();
    mRg1.ClearAllControls();
}

unsigned int CPc2DcAlu1::Ct1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_INC)) ? CCounter::INC : 0;
    return controls;
}

unsigned int CPc2DcAlu1::Rg1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_WR)) ? CRegister::WR : 0;
    return controls;
}

void CPc2DcAlu1::DoShiftState() {
    mCt1.ShiftState();
    mRg1.ShiftState();
}

void CPc2DcAlu1::DoSpreadInput() {
    mRg1.SetInput(DataInput().BitsAt(7,0));

    CBitBlock xor1Input(mRg1.Output());
    xor1Input.ClearAt(7);
    mXor1.SetInput(xor1Input);
    mXor1.SetInvert(ControlInput().IsSetAt(Y_XR1_NOT));

    mCt1.SetInput(mXor1.Output());

    //controls
    ClearAllControls();

    mRg1.SetMaskedControls(Rg1Controls());
    mCt1.SetMaskedControls(Ct1Controls());

    CheckErrors();
}

void CPc2DcAlu1::DoReset() {
    ResetCt1();
    ResetRg1();
}

void CPc2DcAlu1::CheckErrors() {
    if (mCt1.IsConflictedControls()) {
        mErrorState.SetCounterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (mRg1.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (!IsDataInput()) {
        if (ControlInput().IsSetAt(Y_RG1_WR)) {
            mErrorState.SetError(CErrorState::ALU_SOURCE, CErrorState::READ_EMPTY_BUS);
        }
    }
}

void CPc2DcAlu1::ResetCt1() {
    mCt1.ClearAllControls();
    mCt1.SetMaskedControls(CCounter::RST);
    mCt1.ShiftState();
}

void CPc2DcAlu1::ResetRg1() {
    mRg1.ClearAllControls();
    mRg1.SetMaskedControls(CRegister::RST);
    mRg1.ShiftState();
}

