#include "cdcacalu2.h"

CDcacAlu2::CDcacAlu2()
    : CAlu(8, 0, Y_COUNT, P_COUNT)
    , mRg1(9)
    , mRg2(16)
    , mRg3(16)
    , mCt1(4)
    , mXor1(16)
    , mSm1(16)
{}

const CRegister *CDcacAlu2::Register(unsigned int index) const {
    switch (index) {
    case 1: return &mRg1;
    case 2: return &mRg2;
    case 3: return &mRg3;
    }
    return 0;
}

const CCounter *CDcacAlu2::Counter(unsigned int index) const {
    switch (index) {
    case 1: return &mCt1;
    }
    return 0;
}

const CSummator *CDcacAlu2::Summator(unsigned int index) const {
    switch (index) {
    case 1: return &mSm1;
    }
    return 0;
}

const CXor *CDcacAlu2::Xor(unsigned int index) const {
    switch (index) {
    case 1: return &mXor1;
    }
    return 0;
}

CBitBlock CDcacAlu2::BusMaker(unsigned int index) const {
    switch (index) {
    case 1: return BusOut1();
    case 2: return BusOut2();
    }
    return CBitBlock();
}

CBitBlock CDcacAlu2::DoDataOutput() const {
    if (ControlInput().IsSetAt(Y_BD1_OUT))
        return BusOut1();
    if (ControlInput().IsSetAt(Y_BD2_OUT))
        return BusOut2();
    return CBitBlock();
}

CBitBlock CDcacAlu2::DoControlOutput() const {
    CBitBlock output(ControlOutputDim());
    output.SetBoolAt(P_CT1_3, mCt1.Output().IsSetAt(3));
    output.SetBoolAt(P_RG1_0, mRg1.Output().IsSetAt(0));
    output.SetBoolAt(P_RG1_1, mRg1.Output().IsSetAt(1));
    return output;
}

unsigned int CDcacAlu2::DoDataOutCount() const {
    return
            (ControlInput().IsSetAt(Y_BD1_OUT) ? 1 : 0)
          + (ControlInput().IsSetAt(Y_BD2_OUT) ? 1 : 0);
}

CBitBlock CDcacAlu2::BusOut1() const {
    return mRg3.Output().BitsAt(15,8);
}

CBitBlock CDcacAlu2::BusOut2() const {
    return mRg3.Output().BitsAt(7,0);
}

void CDcacAlu2::ClearAllControls() {
    mCt1.ClearAllControls();

    mRg1.ClearAllControls();
    mRg2.ClearAllControls();
    mRg3.ClearAllControls();
}

unsigned int CDcacAlu2::Ct1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_INC)) ? CCounter::INC : 0;
    return controls;
}

unsigned int CDcacAlu2::Rg1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_SHR)) ? CRegister::SHR : 0;
    controls |= (mRg1.Output().IsSetAt(8)) ? CRegister::LV : 0;
    return controls;
}

unsigned int CDcacAlu2::Rg2Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_SHL)) ? CRegister::SHL : 0;
    return controls;
}

unsigned int CDcacAlu2::Rg3Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_WR))  ? CRegister::WR : 0;
    return controls;
}

void CDcacAlu2::DoShiftState() {
    mCt1.ShiftState();
    mRg1.ShiftState();
    mRg2.ShiftState();
    mRg3.ShiftState();
}

void CDcacAlu2::DoSpreadInput() {
    CBitBlock rg1Val(9,0);
    rg1Val.CopyFrom(DataInput().BitsAt(7,0), 1);
    mRg1.SetInput(rg1Val);
    CBitBlock rg2Val(16);
    rg2Val.CopyFrom(DataInput().BitsAt(7,0));
    rg2Val.SwitchRangeTo(15, 8, DataInput().IsSetAt(7));
    mRg2.SetInput(rg2Val);

    mCt1.SetInput(CBitBlock(4, 0));

    mXor1.SetInput(mRg2.Output());
    mXor1.SetInvert(ControlInput().IsSetAt(Y_SM1_C_RG2_NOT));

    mSm1.SetLeftInput(mXor1.Output());
    mSm1.SetRightInput(mRg3.Output());
    mSm1.SetC(ControlInput().IsSetAt(Y_SM1_C_RG2_NOT));

    mRg3.SetInput(mSm1.Output());

    //controls
    ClearAllControls();

    mCt1.SetMaskedControls(Ct1Controls());

    mRg1.SetMaskedControls(Rg1Controls());
    mRg2.SetMaskedControls(Rg2Controls());
    mRg3.SetMaskedControls(Rg3Controls());

    CheckErrors();
}

void CDcacAlu2::DoReset() {
    ResetCt1();
    ResetRg1();
    ResetRg2();
    ResetRg3();
}

void CDcacAlu2::CheckErrors() {
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

void CDcacAlu2::ResetCt1() {
    mCt1.ClearAllControls();
    mCt1.SetMaskedControls(CCounter::RST);
    mCt1.ShiftState();
}

void CDcacAlu2::ResetRg1() {
    mRg1.ClearAllControls();
    mRg1.SetMaskedControls(CRegister::RST);
    mRg1.ShiftState();
}

void CDcacAlu2::ResetRg2() {
    mRg2.ClearAllControls();
    mRg2.SetMaskedControls(CRegister::RST);
    mRg2.ShiftState();
}

void CDcacAlu2::ResetRg3() {
    mRg3.ClearAllControls();
    mRg3.SetMaskedControls(CRegister::RST);
    mRg3.ShiftState();
}
