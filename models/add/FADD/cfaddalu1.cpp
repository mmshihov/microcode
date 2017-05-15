#include "cfaddalu1.h"
#include "cfaddtestvector.h"

CFaddAlu1::CFaddAlu1()
    : CAlu(16, 0, Y_COUNT, P_COUNT)
    , mRg1(11)
    , mRg2(11)
    , mCt1(8)
    , mCt2(8)
    , mXor1(8)
    , mSm1(11)
    , mSm2(8)
    , mMs1(16,2)
{}

const CRegister *CFaddAlu1::Register(unsigned int index) const {
    switch (index) {
    case 1: return &mRg1;
    case 2: return &mRg2;
    }
    return 0;
}

const CCounter *CFaddAlu1::Counter(unsigned int index) const {
    switch (index) {
    case 1: return &mCt1;
    case 2: return &mCt2;
    }
    return 0;
}

const CSummator *CFaddAlu1::Summator(unsigned int index) const {
    switch (index) {
    case 1: return &mSm1;
    case 2: return &mSm2;
    }
    return 0;
}

const CXor *CFaddAlu1::Xor(unsigned int index) const {
    switch (index) {
    case 1: return &mXor1;
    }
    return 0;
}

const CMultiplexor *CFaddAlu1::Multiplexor(unsigned int index) const {
    switch (index) {
    case 1: return &mMs1;
    }
    return 0;
}

CBitBlock CFaddAlu1::BusMaker(unsigned int index) const {
    switch (index) {
    case 1: return BusOut1();
    case 2: return BusOut2();
    }
    return CBitBlock();
}

bool CFaddAlu1::Logic(unsigned int index) const {
    switch(index) {
    case P_CT1_IS_GT_10:        return IsCt1Gt10();
    case P_CT1_IS_LT_MINUS_10:  return IsCt1LtMinus10();
    case P_CT1_IS_ZERO:         return IsCt1Zero();
    case P_RG2_IS_ZERO:         return IsRg2Zero();
    }
    return false;
}

CBitBlock CFaddAlu1::DoDataOutput() const {
    if (ControlInput().IsSetAt(Y_BD1_OUT))
        return BusOut1();
    if (ControlInput().IsSetAt(Y_BD2_OUT))
        return BusOut2();
    return CBitBlock();
}

CBitBlock CFaddAlu1::DoControlOutput() const {
    CBitBlock output(ControlOutputDim());
    output.SetBoolAt(P_CT1_6,               mCt1.Output().IsSetAt(6));
    output.SetBoolAt(P_CT1_7,               mCt1.Output().IsSetAt(7));
    output.SetBoolAt(P_RG2_9,               mRg2.Output().IsSetAt(9));
    output.SetBoolAt(P_RG2_10,              mRg2.Output().IsSetAt(10));
    output.SetBoolAt(P_CT1_IS_GT_10,        IsCt1Gt10());
    output.SetBoolAt(P_CT1_IS_LT_MINUS_10,  IsCt1LtMinus10());
    output.SetBoolAt(P_CT1_IS_ZERO,        !IsCt1Zero());
    output.SetBoolAt(P_RG2_IS_ZERO,        !IsRg2Zero());
    return output;
}

unsigned int CFaddAlu1::DoDataOutCount() const {
    return
              (ControlInput().IsSetAt(Y_BD1_OUT) ? 1 : 0)
            + (ControlInput().IsSetAt(Y_BD2_OUT) ? 1 : 0)
            ;
}

CBitBlock CFaddAlu1::BusOut1() const {
    CBitBlock block(16);
    block.CopyFrom(mCt1.Output().BitsAt(5, 0), 0);
    block.CopyFrom(mRg2.Output().BitsAt(10,1), 6);
    return block;
}

CBitBlock CFaddAlu1::BusOut2() const {
    return mMs1.Output();
}


void CFaddAlu1::ClearAllControls() {
    mCt1.ClearAllControls();
    mCt2.ClearAllControls();

    mRg1.ClearAllControls();
    mRg2.ClearAllControls();
}

unsigned int CFaddAlu1::Ct1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_RST)) ? CCounter::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_INC)) ? CCounter::INC : 0;
    controls |= (ControlInput().IsSetAt(Y_CT1_DEC)) ? CCounter::DEC : 0;
    return controls;
}

unsigned int CFaddAlu1::Ct2Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_CT2_WR)) ? CCounter::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_CT2_INC)) ? CCounter::INC : 0;
    controls |= (ControlInput().IsSetAt(Y_CT2_DEC)) ? CCounter::DEC : 0;
    return controls;
}

unsigned int CFaddAlu1::Rg1Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG1_SHR)) ? CRegister::SHR : 0;
    controls |= (mRg1.Output().IsSetAt(10)) ? CRegister::LV : 0;
    return controls;
}

unsigned int CFaddAlu1::Rg2Controls() const {
    unsigned int controls = 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_RST)) ? CRegister::RST : 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_WR)) ? CRegister::WR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_SHR)) ? CRegister::SHR : 0;
    controls |= (ControlInput().IsSetAt(Y_RG2_SHL)) ? CRegister::SHL : 0;
    controls |= (mRg2.Output().IsSetAt(10)) ? CRegister::LV : 0;
    return controls;
}

void CFaddAlu1::DoShiftState() {
    mCt1.ShiftState();
    mCt2.ShiftState();

    mRg1.ShiftState();
    mRg2.ShiftState();
}

void CFaddAlu1::DoSpreadInput() {
    CBitBlock rg1val(CFaddTestVector::MANT_LEN + 1);
    rg1val.CopyFrom(DataInput().BitsAt(15,6));
    rg1val.SetBoolAt(CFaddTestVector::MANT_LEN, DataInput().IsSetAt(15));
    mRg1.SetInput(rg1val);

    CBitBlock ct2val(CFaddTestVector::CHAR_LEN + 2);
    ct2val.CopyFrom(DataInput().BitsAt(5,0));
    ct2val.ClearRange(7,6);
    mCt2.SetInput(ct2val);


    mSm1.SetLeftInput(mRg2.Output());
    mSm1.SetRightInput(mRg1.Output());
    mSm1.SetC(false);

    mRg2.SetInput(mSm1.Output());


    mXor1.SetInput(mCt2.Output());
    mXor1.SetInvert(ControlInput().IsSetAt(Y_XR1_NOT_SM2_C));

    mSm2.SetLeftInput(mCt1.Output());
    mSm2.SetRightInput(mXor1.Output());
    mSm2.SetC(ControlInput().IsSetAt(Y_XR1_NOT_SM2_C));

    mCt1.SetInput(mSm2.Output());


    mMs1.SetInput(0, CBitBlock(DataDim(), CFaddTestVector::EC_RESULT_DEFINED));
    mMs1.SetInput(1, CBitBlock(DataDim(), CFaddTestVector::EC_NEGATIVE_OVF));
    mMs1.SetInput(2, CBitBlock(DataDim(), CFaddTestVector::EC_POSITIVE_OVF));
    mMs1.SetInput(3, CBitBlock(DataDim(), CFaddTestVector::EC_UNREAL_ZERO));

    mMs1.SetInputIndex(
              2*(ControlInput().IsSetAt(Y_MS1_SEL1) ? 1 : 0)
            +   (ControlInput().IsSetAt(Y_MS1_SEL0) ? 1 : 0));

    //controls
    ClearAllControls();

    mCt1.SetMaskedControls(Ct1Controls());
    mCt2.SetMaskedControls(Ct2Controls());

    mRg1.SetMaskedControls(Rg1Controls());
    mRg2.SetMaskedControls(Rg2Controls());

    CheckErrors();
}

void CFaddAlu1::DoReset() {
    ResetCt1();
    ResetCt2();

    ResetRg1();
    ResetRg2();
}

void CFaddAlu1::CheckErrors() {
    if (mCt1.IsConflictedControls()) {
        mErrorState.SetCounterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (mCt2.IsConflictedControls()) {
        mErrorState.SetCounterControlError(CErrorState::MCU_SOURCE, 2);
    } else if (mRg1.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 1);
    } else if (mRg2.IsConflictedControls()) {
        mErrorState.SetRegisterControlError(CErrorState::MCU_SOURCE, 2);
    } else if (!IsDataInput()) {
        if (       ControlInput().IsSetAt(Y_RG1_WR)
                && ControlInput().IsSetAt(Y_CT2_WR)) {
            mErrorState.SetError(CErrorState::ALU_SOURCE, CErrorState::READ_EMPTY_BUS);
        }
    }
}

void CFaddAlu1::ResetCt1() {
    mCt1.ClearAllControls();
    mCt1.SetMaskedControls(CCounter::RST);
    mCt1.ShiftState();
}

void CFaddAlu1::ResetCt2() {
    mCt2.ClearAllControls();
    mCt2.SetMaskedControls(CCounter::RST);
    mCt2.ShiftState();
}

void CFaddAlu1::ResetRg1() {
    mRg1.ClearAllControls();
    mRg1.SetMaskedControls(CRegister::RST);
    mRg1.ShiftState();
}

void CFaddAlu1::ResetRg2() {
    mRg2.ClearAllControls();
    mRg2.SetMaskedControls(CRegister::RST);
    mRg2.ShiftState();
}

bool CFaddAlu1::IsCt1Gt10() const {
    if (!mCt1.Output().IsSetAt(7))
        return mCt1.Output().AsInt() > 9;
    return false;
}

bool CFaddAlu1::IsCt1LtMinus10() const {
    if (mCt1.Output().IsSetAt(7)) {
        CBitBlock block(8, (~(mCt1.Output().AsInt())) + 1);
        return  block.AsInt() > 9;
    }
    return false;
}

bool CFaddAlu1::IsCt1Zero() const {
    return mCt1.Output().AsInt() == 0;
}

bool CFaddAlu1::IsRg2Zero() const {
    return mRg2.Output().BitsAt(10,1).AsInt() == 0;
}
