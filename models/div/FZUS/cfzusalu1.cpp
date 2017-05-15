#include "cfzusalu1.h"


CFzusAlu1::CFzusAlu1()
    : CAlu(8, 0, Y_COUNT, P_COUNT)
    , mRg1(8)
    , mRg2(8)
    , mRg3(17)
    , mRg4(8)
    , mCt1(4)
    , mXor1(17)
    , mSm1(17)
{}

const CRegister *CFzusAlu1::Register(unsigned int index) const {
    switch (index) {
    case 1: return &mRg1;
    case 2: return &mRg2;
    case 3: return &mRg3;
    case 4: return &mRg4;
    }
    return 0;
}

const CCounter *CFzusAlu1::Counter(unsigned int index) const {
    switch (index) {
    case 1: return &mCt1;
    }
    return 0;
}

const CSummator *CFzusAlu1::Summator(unsigned int index) const {
    switch (index) {
    case 1: return &mSm1;
    }
    return 0;
}

const CXor *CFzusAlu1::Xor(unsigned int index) const {
    switch (index) {
    case 1: return &mXor1;
    }
    return 0;
}

CBitBlock CFzusAlu1::BusMaker(unsigned int index) const {
    switch (index) {
    case 1: return BusOut1();
    case 2: return BusOut2();
    case 3: return BusOut3();
    }
    return CBitBlock();
}

CBitBlock CFzusAlu1::DoDataOutput() const {
    if (ControlInput().IsSetAt(Y_BD1_OUT))
        return BusOut1();
    if (ControlInput().IsSetAt(Y_BD2_OUT))
        return BusOut2();
    if (ControlInput().IsSetAt(Y_BD3_OUT))
        return BusOut3();
    return CBitBlock();
}

CBitBlock CFzusAlu1::DoControlOutput() const {
    CBitBlock output(ControlOutputDim());
    output.SetBoolAt(P_CT1_3,  mCt1.Output().IsSetAt(3));
    output.SetBoolAt(P_RG3_16, !mRg3.Output().IsSetAt(16));
    return output;
}

unsigned int CFzusAlu1::DoDataOutCount() const {
    return
              (ControlInput().IsSetAt(Y_BD1_OUT) ? 1 : 0)
            + (ControlInput().IsSetAt(Y_BD2_OUT) ? 1 : 0)
            + (ControlInput().IsSetAt(Y_BD3_OUT) ? 1 : 0)
            ;
}

CBitBlock CFzusAlu1::BusOut1() const {
    return mRg4.Output();
}

CBitBlock CFzusAlu1::BusOut2() const {
    return mRg3.Output().BitsAt(15,8);
}

CBitBlock CFzusAlu1::BusOut3() const {
    return mRg3.Output().BitsAt(7,0);
}

void CFzusAlu1::ClearAllControls() {
    mCt1.ClearAllControls();

    mRg1.ClearAllControls();
    mRg2.ClearAllControls();
    mRg3.ClearAllControls();
    mRg4.ClearAllControls();
}

unsigned int CFzusAlu1::Ct1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_INC)) ? CCounter::INC : 0;
    return controls;
}

unsigned int CFzusAlu1::Rg1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_RG2_SHR)) ? CRegister::SHR : 0;
    return controls;
}

unsigned int CFzusAlu1::Rg2Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_RG2_SHR)) ? CRegister::SHR : 0;
    controls |= (mRg1.Output().IsSetAt(0)) ? CRegister::LV : 0;
    return controls;
}

unsigned int CFzusAlu1::Rg3Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_WR))  ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_SHL)) ? CRegister::SHL : 0;
    return controls;
}

unsigned int CFzusAlu1::Rg4Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG4_SHL)) ? CRegister::SHL : 0;
    controls |= (!mRg3.Output().IsSetAt(16)) ? CRegister::RV : 0;
    return controls;
}

void CFzusAlu1::DoShiftState() {
    mCt1.ShiftState();
    mRg1.ShiftState();
    mRg2.ShiftState();
    mRg3.ShiftState();
    mRg4.ShiftState();
}

void CFzusAlu1::DoSpreadInput() {
    mRg1.SetInput(DataInput().BitsAt(7,0));
    mRg2.SetInput(DataInput().BitsAt(7,0));

    mCt1.SetInput(CBitBlock(4, 0));

    CBitBlock xor1Val(17);
    xor1Val.CopyFrom(mRg2.Output());
    xor1Val.CopyFrom(mRg1.Output(), 8);
    xor1Val.ClearAt(16);
    mXor1.SetInput(xor1Val);
    mXor1.SetInvert(ControlInput().IsSetAt(Y_SM1_C_XR1_NOT));

    mSm1.SetLeftInput(mXor1.Output());
    mSm1.SetRightInput(mRg3.Output());
    mSm1.SetC(ControlInput().IsSetAt(Y_SM1_C_XR1_NOT));

    mRg3.SetInput(mSm1.Output());

    //controls
    ClearAllControls();

    mCt1.SetMaskedControls(Ct1Controls());

    mRg1.SetMaskedControls(Rg1Controls());
    mRg2.SetMaskedControls(Rg2Controls());
    mRg3.SetMaskedControls(Rg3Controls());
    mRg4.SetMaskedControls(Rg4Controls());

    CheckErrors();
}

void CFzusAlu1::DoReset() {
    ResetCt1();
    ResetRg1();
    ResetRg2();
    ResetRg3();
    ResetRg4();
}

void CFzusAlu1::CheckErrors() {
    if (mCt1.IsConflictedControls()) {
        mErrorState.SetCounterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (mRg1.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (mRg2.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 2);
    } else if (mRg3.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 3);
    } else if (mRg4.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 4);
    } else if (!IsDataInput()) {
        if (       ControlInput().IsSetAt(Y_RG1_WR)
                && ControlInput().IsSetAt(Y_RG2_WR)) {
            mErrorState.SetError(CErrorState::ALU_SOURCE, CErrorState::READ_EMPTY_BUS);
        }
    }
}

void CFzusAlu1::ResetCt1() {
    mCt1.ClearAllControls();
    mCt1.SetMaskedControls(CCounter::RST);
    mCt1.ShiftState();
}

void CFzusAlu1::ResetRg1() {
    mRg1.ClearAllControls();
    mRg1.SetMaskedControls(CRegister::RST);
    mRg1.ShiftState();
}

void CFzusAlu1::ResetRg2() {
    mRg2.ClearAllControls();
    mRg2.SetMaskedControls(CRegister::RST);
    mRg2.ShiftState();
}

void CFzusAlu1::ResetRg3() {
    mRg3.ClearAllControls();
    mRg3.SetMaskedControls(CRegister::RST);
    mRg3.ShiftState();
}

void CFzusAlu1::ResetRg4() {
    mRg4.ClearAllControls();
    mRg4.SetMaskedControls(CRegister::RST);
    mRg4.ShiftState();
}
