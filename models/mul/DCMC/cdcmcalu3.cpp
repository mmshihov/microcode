#include "cdcmcalu3.h"

CDcmcAlu3::CDcmcAlu3()
    : CAlu(8, 0, Y_COUNT, P_COUNT)
    , mRg1(8)
    , mRg2(8)
    , mRg3(16)
    , mCt1(4)
    , mMs1(16,1)
    , mXor1(16)
    , mSm1(16)
{}

const CRegister *CDcmcAlu3::Register(unsigned int index) const {
    switch (index) {
    case 1: return &mRg1;
    case 2: return &mRg2;
    case 3: return &mRg3;
    }
    return 0;
}

const CCounter *CDcmcAlu3::Counter(unsigned int index) const {
    switch (index) {
    case 1: return &mCt1;
    }
    return 0;
}

const CSummator *CDcmcAlu3::Summator(unsigned int index) const {
    switch (index) {
    case 1: return &mSm1;
    }
    return 0;
}

const CMultiplexor *CDcmcAlu3::Multiplexor(unsigned int index) const {
    switch (index) {
    case 1: return &mMs1;
    }
    return 0;
}

const CXor *CDcmcAlu3::Xor(unsigned int index) const {
    switch (index) {
    case 1: return &mXor1;
    }
    return 0;
}

CBitBlock CDcmcAlu3::BusMaker(unsigned int index) const {
    switch (index) {
    case 1: return BusOut1();
    case 2: return BusOut2();
    }
    return CBitBlock();
}

CBitBlock CDcmcAlu3::DoDataOutput() const {
    if (ControlInput().IsSetAt(Y_BD1_OUT))
        return BusOut1();
    if (ControlInput().IsSetAt(Y_BD2_OUT))
        return BusOut2();
    return CBitBlock();
}

CBitBlock CDcmcAlu3::DoControlOutput() const {
    CBitBlock output(ControlOutputDim());
    output.SetBoolAt(P_CT1_3, mCt1.Output().IsSetAt(3));
    output.SetBoolAt(P_RG1_7, mRg1.Output().IsSetAt(7));
    output.SetBoolAt(P_RG2_7, mRg2.Output().IsSetAt(7));
    return output;
}

unsigned int CDcmcAlu3::DoDataOutCount() const {
    return
            (ControlInput().IsSetAt(Y_BD1_OUT) ? 1 : 0)
          + (ControlInput().IsSetAt(Y_BD2_OUT) ? 1 : 0);
}

CBitBlock CDcmcAlu3::BusOut1() const {
    return mRg3.Output().BitsAt(15,8);
}

CBitBlock CDcmcAlu3::BusOut2() const {
    return mRg3.Output().BitsAt(7,0);
}

void CDcmcAlu3::ClearAllControls() {
    mCt1.ClearAllControls();

    mRg1.ClearAllControls();
    mRg2.ClearAllControls();
    mRg3.ClearAllControls();
}

unsigned int CDcmcAlu3::Ct1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_INC)) ? CCounter::INC : 0;
    return controls;
}

unsigned int CDcmcAlu3::Rg1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_SHL)) ? CRegister::SHL : 0;
    return controls;
}

unsigned int CDcmcAlu3::Rg2Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_WR)) ? CRegister::WR : 0;
    return controls;
}

unsigned int CDcmcAlu3::Rg3Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_WR))  ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_SHL))  ? CRegister::SHL : 0;
    return controls;
}

void CDcmcAlu3::DoShiftState() {
    mCt1.ShiftState();
    mRg1.ShiftState();
    mRg2.ShiftState();
    mRg3.ShiftState();
}

void CDcmcAlu3::DoSpreadInput() {
    mRg1.SetInput(DataInput().BitsAt(7,0));
    mRg2.SetInput(DataInput().BitsAt(7,0));

    mCt1.SetInput(CBitBlock(4, 0));

    CBitBlock ms1Plex1(16);
    ms1Plex1.CopyFrom(mRg1.Output(), 0);
    ms1Plex1.ClearRange(15, 8);
    mMs1.SetInput(1,ms1Plex1);
    CBitBlock ms1Plex0(16);
    ms1Plex0.CopyFrom(mRg2.Output(), 0);
    ms1Plex0.ClearRange(15, 8);
    mMs1.SetInput(0,ms1Plex0);
    mMs1.SetInputIndex(ControlInput().IsSetAt(Y_MS1_SEL) ? 1 : 0);

    mXor1.SetInput(mMs1.Output());
    mXor1.SetInvert(ControlInput().IsSetAt(Y_SM1_C_MS1_NOT));

    mSm1.SetLeftInput(mXor1.Output());
    mSm1.SetRightInput(mRg3.Output());
    mSm1.SetC(ControlInput().IsSetAt(Y_SM1_C_MS1_NOT));

    mRg3.SetInput(mSm1.Output());

    //controls
    ClearAllControls();

    mCt1.SetMaskedControls(Ct1Controls());

    mRg1.SetMaskedControls(Rg1Controls());
    mRg2.SetMaskedControls(Rg2Controls());
    mRg3.SetMaskedControls(Rg3Controls());

    CheckErrors();
}

void CDcmcAlu3::DoReset() {
    ResetCt1();
    ResetRg1();
    ResetRg2();
    ResetRg3();
}

void CDcmcAlu3::CheckErrors() {
    if (mCt1.IsConflictedControls()) {
        mErrorState.SetCounterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (mRg1.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (mRg2.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 2);
    } else if (mRg3.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 3);
    } else if (!IsDataInput()) {
        if (       ControlInput().IsSetAt(Y_RG1_WR)
                && ControlInput().IsSetAt(Y_RG2_WR)) {
            mErrorState.SetError(CErrorState::ALU_SOURCE, CErrorState::READ_EMPTY_BUS);
        }
    }
}

void CDcmcAlu3::ResetCt1() {
    mCt1.ClearAllControls();
    mCt1.SetMaskedControls(CCounter::RST);
    mCt1.ShiftState();
}

void CDcmcAlu3::ResetRg1() {
    mRg1.ClearAllControls();
    mRg1.SetMaskedControls(CRegister::RST);
    mRg1.ShiftState();
}

void CDcmcAlu3::ResetRg2() {
    mRg2.ClearAllControls();
    mRg2.SetMaskedControls(CRegister::RST);
    mRg2.ShiftState();
}

void CDcmcAlu3::ResetRg3() {
    mRg3.ClearAllControls();
    mRg3.SetMaskedControls(CRegister::RST);
    mRg3.ShiftState();
}
