#include "cpcs1alu2.h"

CPcs1Alu2::CPcs1Alu2()
    : CAlu(8, 0, Y_COUNT, P_COUNT)
    , mRg1(7)
    , mRg2(14)
    , mRg3(14)
    , mCt1(4)
    , mSm1(14)
{}

const CRegister *CPcs1Alu2::Register(unsigned int index) const {
    switch (index) {
    case 1: return &mRg1;
    case 2: return &mRg2;
    case 3: return &mRg3;
    }
    return 0;
}

bool CPcs1Alu2::Trigger(unsigned int index) const {
    switch (index) {
    case 1: return mT1;
    case 2: return mT2;
    }
    return false;
}

const CCounter *CPcs1Alu2::Counter(unsigned int index) const {
    switch (index) {
    case 1: return &mCt1;
    }
    return 0;
}

const CSummator *CPcs1Alu2::Summator(unsigned int index) const {
    switch (index) {
    case 1: return &mSm1;
    }
    return 0;
}

bool CPcs1Alu2::Logic(unsigned int index) const {
    switch (index) {
    case XOR_T1_T2: return IsXorT1T2();
    case OR_RG3:    return IsOnesInRg3Bits();
    case AND_SIGN:  return IsSign();
    }
    return false;
}

CBitBlock CPcs1Alu2::BusMaker(unsigned int index) const {
    switch (index) {
    case 1: return BusOut1();
    case 2: return BusOut2();
    }
    return CBitBlock();
}

CBitBlock CPcs1Alu2::DoDataOutput() const {
    if (ControlInput().IsSetAt(Y_BD1_OUT))
        return BusOut1();
    if (ControlInput().IsSetAt(Y_BD2_OUT))
        return BusOut2();
    return CBitBlock();
}

CBitBlock CPcs1Alu2::DoControlOutput() const {
    CBitBlock output(ControlOutputDim());
    output.SetBoolAt(P_CT1_3, mCt1.Output().IsSetAt(3));
    output.SetBoolAt(P_RG1_0, mRg1.Output().IsSetAt(0));
    return output;
}

unsigned int CPcs1Alu2::DoDataOutCount() const {
    return
            (ControlInput().IsSetAt(Y_BD1_OUT) ? 1 : 0)
          + (ControlInput().IsSetAt(Y_BD2_OUT) ? 1 : 0);
}

CBitBlock CPcs1Alu2::BusOut1() const {
    CBitBlock block(8);

    block.CopyFrom(mRg3.Output().BitsAt(13,8), 0);
    block.ClearAt(6);
    block.SetBoolAt(7,IsSign());
    return block;
}

CBitBlock CPcs1Alu2::BusOut2() const {
    return mRg3.Output().BitsAt(7,0);
}

void CPcs1Alu2::ClearAllControls() {
    mCt1.ClearAllControls();

    mRg1.ClearAllControls();
    mRg2.ClearAllControls();
    mRg3.ClearAllControls();
}

unsigned int CPcs1Alu2::Ct1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_INC)) ? CCounter::INC : 0;
    return controls;
}

unsigned int CPcs1Alu2::Rg1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_SHR)) ? CRegister::SHR : 0;
    return controls;
}

unsigned int CPcs1Alu2::Rg2Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_SHL)) ? CRegister::SHL : 0;
    return controls;
}

unsigned int CPcs1Alu2::Rg3Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG3_WR))  ? CRegister::WR : 0;
    return controls;
}

void CPcs1Alu2::DoShiftState() {
    mCt1.ShiftState();
    mRg1.ShiftState();
    mRg2.ShiftState();
    mRg3.ShiftState();

    if (ControlInput().IsSetAt(Y_T1_C))
        mT1 = DataInput().IsSetAt(7);

    if (ControlInput().IsSetAt(Y_T2_C))
        mT2 = DataInput().IsSetAt(7);
}

void CPcs1Alu2::DoSpreadInput() {
    mRg1.SetInput(DataInput().BitsAt(6,0));

    CBitBlock Rg2val(14);
    Rg2val.CopyFrom(DataInput().BitsAt(6,0));
    Rg2val.CopyFrom(CBitBlock(7,0),7);

    mRg2.SetInput(Rg2val);

    mCt1.SetInput(CBitBlock(4, 1));

    mSm1.SetLeftInput(mRg3.Output());
    mSm1.SetRightInput(mRg2.Output());
    mSm1.SetC(false);

    mRg3.SetInput(mSm1.Output().BitsAt(13,0));

    //controls
    ClearAllControls();

    mCt1.SetMaskedControls(Ct1Controls());

    mRg1.SetMaskedControls(Rg1Controls());
    mRg2.SetMaskedControls(Rg2Controls());
    mRg3.SetMaskedControls(Rg3Controls());

    CheckErrors();
}

void CPcs1Alu2::DoReset() {
    ResetCt1();
    ResetRg1();
    ResetRg2();
    ResetRg3();
    ResetT1();
    ResetT2();
}

void CPcs1Alu2::CheckErrors() {
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
                && ControlInput().IsSetAt(Y_RG2_WR)
                && ControlInput().IsSetAt(Y_T1_C)
                && ControlInput().IsSetAt(Y_T2_C)) {
            mErrorState.SetError(CErrorState::ALU_SOURCE, CErrorState::READ_EMPTY_BUS);
        }
    }
}

bool CPcs1Alu2::IsXorT1T2() const {
    return (mT1 != mT2);
}

bool CPcs1Alu2::IsOnesInRg3Bits() const {
    return (mRg3.Output().AsInt() != 0);
}

bool CPcs1Alu2::IsSign() const {
    return IsXorT1T2() && IsOnesInRg3Bits();
}

void CPcs1Alu2::ResetCt1() {
    mCt1.ClearAllControls();
    mCt1.SetMaskedControls(CCounter::RST);
    mCt1.ShiftState();
}

void CPcs1Alu2::ResetRg1() {
    mRg1.ClearAllControls();
    mRg1.SetMaskedControls(CRegister::RST);
    mRg1.ShiftState();
}

void CPcs1Alu2::ResetRg2() {
    mRg2.ClearAllControls();
    mRg2.SetMaskedControls(CRegister::RST);
    mRg2.ShiftState();
}

void CPcs1Alu2::ResetRg3() {
    mRg3.ClearAllControls();
    mRg3.SetMaskedControls(CRegister::RST);
    mRg3.ShiftState();
}


