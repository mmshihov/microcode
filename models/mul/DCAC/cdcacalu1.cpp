#include "cdcacalu1.h"

CDcacAlu1::CDcacAlu1()
    : CAlu(8, 0, Y_COUNT, P_COUNT)
    , mRg1(9)
    , mRg2(8)
    , mRg3(9)
    , mRg4(8)
    , mCt1(4)
    , mXor1(9)
    , mSm1(9)
{}

const CRegister *CDcacAlu1::Register(unsigned int index) const {
    switch (index) {
    case 1: return &mRg1;
    case 2: return &mRg2;
    case 3: return &mRg3;
    case 4: return &mRg4;
    }
    return 0;
}

const CCounter *CDcacAlu1::Counter(unsigned int index) const {
    switch (index) {
    case 1: return &mCt1;
    }
    return 0;
}

const CSummator *CDcacAlu1::Summator(unsigned int index) const {
    switch (index) {
    case 1: return &mSm1;
    }
    return 0;
}

const CXor *CDcacAlu1::Xor(unsigned int index) const {
    switch (index) {
    case 1: return &mXor1;
    }
    return 0;
}

CBitBlock CDcacAlu1::BusMaker(unsigned int index) const {
    switch (index) {
    case 1: return BusOut1();
    case 2: return BusOut2();
    }
    return CBitBlock();
}

CBitBlock CDcacAlu1::DoDataOutput() const {
    if (ControlInput().IsSetAt(Y_BD1_OUT))
        return BusOut1();
    if (ControlInput().IsSetAt(Y_BD2_OUT))
        return BusOut2();
    return CBitBlock();
}

CBitBlock CDcacAlu1::DoControlOutput() const {
    CBitBlock output(ControlOutputDim());
    output.SetBoolAt(P_CT1_3, mCt1.Output().IsSetAt(3));
    output.SetBoolAt(P_RG1_0, mRg1.Output().IsSetAt(0));
    output.SetBoolAt(P_RG1_1, mRg1.Output().IsSetAt(1));
    return output;
}

unsigned int CDcacAlu1::DoDataOutCount() const {
    return
            (ControlInput().IsSetAt(Y_BD1_OUT) ? 1 : 0)
          + (ControlInput().IsSetAt(Y_BD2_OUT) ? 1 : 0);
}

CBitBlock CDcacAlu1::BusOut1() const {
    return mRg3.Output().BitsAt(7,0);
}

CBitBlock CDcacAlu1::BusOut2() const {
    return mRg4.Output().BitsAt(7,0);
}

void CDcacAlu1::ClearAllControls() {
    mCt1.ClearAllControls();

    mRg1.ClearAllControls();
    mRg2.ClearAllControls();
    mRg3.ClearAllControls();
    mRg4.ClearAllControls();
}

unsigned int CDcacAlu1::Ct1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_INC)) ? CCounter::INC : 0;
    return controls;
}

unsigned int CDcacAlu1::Rg1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_SHR)) ? CRegister::SHR : 0;
    controls |= (mRg1.Output().IsSetAt(8)) ? CRegister::LV : 0;
    return controls;
}

unsigned int CDcacAlu1::Rg2Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_WR)) ? CRegister::WR : 0;
    return controls;
}

unsigned int CDcacAlu1::Rg3Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_WR))  ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_RG4_SHR)) ? CRegister::SHR : 0;
    controls |= (mRg3.Output().IsSetAt(8)) ? CRegister::LV : 0;
    return controls;
}

unsigned int CDcacAlu1::Rg4Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_RG4_SHR)) ? CRegister::SHR : 0;
    controls |= (mRg3.Output().IsSetAt(0)) ? CRegister::LV : 0;
    return controls;
}

void CDcacAlu1::DoShiftState() {
    mCt1.ShiftState();
    mRg1.ShiftState();
    mRg2.ShiftState();
    mRg3.ShiftState();
    mRg4.ShiftState();
}

void CDcacAlu1::DoSpreadInput() {
    CBitBlock rg1Val(9,0);
    rg1Val.CopyFrom(DataInput().BitsAt(7,0), 1);
    mRg1.SetInput(rg1Val);
    mRg2.SetInput(DataInput().BitsAt(7,0));

    mCt1.SetInput(CBitBlock(4, 0));

    CBitBlock xorVal(9,0);
    xorVal.CopyFrom(mRg2.Output(), 0);
    xorVal.SetBoolAt(8, mRg2.Output().IsSetAt(7));
    mXor1.SetInput(xorVal);
    mXor1.SetInvert(ControlInput().IsSetAt(Y_SM1_C_RG2_NOT));

    mSm1.SetLeftInput(mRg3.Output());
    mSm1.SetRightInput(mXor1.Output());
    mSm1.SetC(ControlInput().IsSetAt(Y_SM1_C_RG2_NOT));

    mRg3.SetInput(mSm1.Output().BitsAt(8,0));

    //controls
    ClearAllControls();

    mCt1.SetMaskedControls(Ct1Controls());

    mRg1.SetMaskedControls(Rg1Controls());
    mRg2.SetMaskedControls(Rg2Controls());
    mRg3.SetMaskedControls(Rg3Controls());
    mRg4.SetMaskedControls(Rg4Controls());

    CheckErrors();
}

void CDcacAlu1::DoReset() {
    ResetCt1();
    ResetRg1();
    ResetRg2();
    ResetRg3();
    ResetRg4();
}

void CDcacAlu1::CheckErrors() {
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

void CDcacAlu1::ResetCt1() {
    mCt1.ClearAllControls();
    mCt1.SetMaskedControls(CCounter::RST);
    mCt1.ShiftState();
}

void CDcacAlu1::ResetRg1() {
    mRg1.ClearAllControls();
    mRg1.SetMaskedControls(CRegister::RST);
    mRg1.ShiftState();
}

void CDcacAlu1::ResetRg2() {
    mRg2.ClearAllControls();
    mRg2.SetMaskedControls(CRegister::RST);
    mRg2.ShiftState();
}

void CDcacAlu1::ResetRg3() {
    mRg3.ClearAllControls();
    mRg3.SetMaskedControls(CRegister::RST);
    mRg3.ShiftState();
}

void CDcacAlu1::ResetRg4() {
    mRg4.ClearAllControls();
    mRg4.SetMaskedControls(CRegister::RST);
    mRg4.ShiftState();
}
