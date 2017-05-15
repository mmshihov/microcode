#include <stdlib.h>
#include "cfaddtestvector.h"
#include "cfaddinputdialog.h"


CFaddTestVector::CFaddTestVector() : CTestVector(/*inputCount      =*/2,
                                                 /*outputCount     =*/2,
                                                 /*dimension       =*/DIMENSION,
                                                 /*autoTestCount   =*/6,
                                                 /*inputUi         =*/new CFaddDebugInputSource()) {}

CBitBlock CFaddTestVector::MakeBitblockFromMantAndChar(unsigned int m, unsigned int c, bool &ok) {
    CBitBlock mBlock(MANT_LEN, m);
    CBitBlock cBlock(CHAR_LEN, c);

    CBitBlock block(MANT_LEN + CHAR_LEN, 0);
    block.CopyFrom(cBlock);
    block.CopyFrom(mBlock, CHAR_LEN);

    ok = IsNormalizedInternalMant(InternalMantFrom(m) << 1)
            || ((m == 0) && (c == 0))
            ;

    return block;
}

CBitBlock CFaddTestVector::CharOf(const CBitBlock &x) {
    return x.BitsAt((CHAR_LEN - 1), 0);
}

CBitBlock CFaddTestVector::MantOf(const CBitBlock &x) {
    return x.BitsAt((MANT_LEN + CHAR_LEN - 1), CHAR_LEN);
}

double CFaddTestVector::DoubleOf(const CBitBlock &x) {
    unsigned int m = InternalMantFrom(MantOf(x).AsInt());
    double rm;

    if (IsNegativeInternalMant(m)) {
        m = CBitBlock(MANT_LEN, (~m) + 1).AsInt();
        rm = -((double)m/(double)(1 << MANT_LEN));
    } else {
        rm = (double)m/(double)(1 << MANT_LEN);
    }

    double power = 2;
    int p = ((int)CharOf(x).AsInt() - (1 << (CHAR_LEN - 1)));
    if (p < 0) {
        p = -p;
        power = 0.5;
    }

    double rpower = 1; //быстрое возведение в степень Карацубы
    for (unsigned int i=0; i < CHAR_LEN; ++i) {
        if ((p & 1) != 0) {
            rpower *= power;
        }
        p = (p >> 1);
        power = (power * power);
    }

    return rm * rpower;
}

CBitBlock CFaddTestVector::RightAnswerPart(const CBitBlock &A, const CBitBlock &B, unsigned int partIndex) {
    unsigned int ca = CharOf(A).AsInt();
    unsigned int cb = CharOf(B).AsInt();

    if (ca < cb)
        return RightAnswerPart(B, A, partIndex);

    //ca >= cb
    unsigned int shiftCount = (ca - cb);
    if (shiftCount >= MANT_LEN)
        return ResultReturn(A, partIndex);

    unsigned int ma = InternalMantFrom(MantOf(A).AsInt());
    unsigned int mb = InternalMantShr(InternalMantFrom(MantOf(B).AsInt()), shiftCount);

    unsigned int mr = (ma + mb);
    unsigned int cr = ca;

    if (CBitBlock(MANT_LEN, mr).AsInt() == 0)
        return ResultReturn(CBitBlock(DIMENSION, 0), partIndex);

    if (IsNormalizedInternalMant(mr)) {
        cr = cr + 1;
        if (IsPositiveInternalCharOverflow(cr)) {
            if (IsNegativeInternalMant(mr))
                return ErrorReturn(EC_NEGATIVE_OVF, partIndex);
            return ErrorReturn(EC_POSITIVE_OVF, partIndex);
        }

        return ResultReturn(MakeResultFromInternals(mr, cr), partIndex);
    }

    mr = (mr << 1);

    while(!IsNormalizedInternalMant(mr)) {
        mr = (mr << 1);
        cr = cr - 1;

        if (IsNegativeInternalChar(cr))
            return ErrorReturn(EC_UNREAL_ZERO, partIndex);
    }

    return ResultReturn(MakeResultFromInternals(mr, cr), partIndex);
}

void CFaddTestVector::DoInitAutoTests() {
    CreateTest_Right_PaGtPb(0);
    CreateTest_Right_PbGtPa(1);
    CreateTest_Right_Zero(2);
    CreateTest_UnrealZero(3);
    CreateTest_PositiveOverflow(4);
    CreateTest_NegativeOverflow(5);
}

CBitBlock CFaddTestVector::DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const {
    CBitBlock A = InputPart(testIndex, 0);
    CBitBlock B = InputPart(testIndex, 1);

    return RightAnswerPart(A,B,partIndex);
}

bool CFaddTestVector::DoIsTestOk(unsigned int testIndex) const {
    if (OutputPart(testIndex, 0) != RightErrorPart(testIndex))
        return false;

    if (RightErrorPart(testIndex).AsInt() != EC_RESULT_DEFINED)
        return true;

    return OutputPart(testIndex, 1) == RightResultPart(testIndex);
}

void CFaddTestVector::CreateTest_PositiveOverflow(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, ~0);
    CBitBlock charB(CHAR_LEN, ~0);

    mantA.SetBoolAt(MANT_LEN - 2, true); //0110000000 111111
    mantA.SetBoolAt(MANT_LEN - 3, true);

    mantB.SetBoolAt(MANT_LEN - 2, true); //0100000000 111110
    charB.SetBoolAt(0,            false);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_NegativeOverflow(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, ~0);
    CBitBlock charB(CHAR_LEN, ~0);

    mantA.SetBoolAt(MANT_LEN - 1, true); //1010000000 111111
    mantA.SetBoolAt(MANT_LEN - 3, true);

    mantB.SetBoolAt(MANT_LEN - 1, true); //1000000000 111110
    charB.SetBoolAt(0,            false);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_UnrealZero(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, 0);
    CBitBlock charB(CHAR_LEN, 0);

    mantA.SetBoolAt(MANT_LEN - 2, true); // 0111000000 000000
    mantA.SetBoolAt(MANT_LEN - 3, true);
    mantA.SetBoolAt(MANT_LEN - 4, true);

    mantB.SetBoolAt(MANT_LEN - 1, true); // 1010000000 000000
    mantB.SetBoolAt(MANT_LEN - 3, true);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_DenormLeft(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, 0);
    CBitBlock charB(CHAR_LEN, 0);

    mantA.SetBoolAt(MANT_LEN - 2, true); //0110000000 100101
    mantA.SetBoolAt(MANT_LEN - 3, true);
    charA.SetBoolAt(CHAR_LEN - 1, true);
    charA.SetBoolAt(0,            true);
    charA.SetBoolAt(2,            true);

    mantB.SetBoolAt(MANT_LEN - 2, true); //0010000000 100101 -> 0100000000 100100
    charB.SetBoolAt(CHAR_LEN - 1, true);
    charB.SetBoolAt(2,            true);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_DenormRight(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, 0);
    CBitBlock charB(CHAR_LEN, 0);

    mantA.SetBoolAt(MANT_LEN - 2, true); // 0111100000 100101
    mantA.SetBoolAt(MANT_LEN - 3, true);
    mantA.SetBoolAt(MANT_LEN - 4, true);
    mantA.SetBoolAt(MANT_LEN - 5, true);
    charA.SetBoolAt(CHAR_LEN - 1, true); //-
    charA.SetBoolAt(0,            true);
    charA.SetBoolAt(2,            true);

    mantB.SetBoolAt(MANT_LEN - 1, true); //-0111000000 100101 -> 1001000000 100101
    mantB.SetBoolAt(MANT_LEN - 4, true);
    charB.SetBoolAt(CHAR_LEN - 1, true); //-
    charB.SetBoolAt(0,            true);
    charB.SetBoolAt(2,            true);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_NoDenorm(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, 0);
    CBitBlock charB(CHAR_LEN, 0);

    mantA.SetBoolAt(MANT_LEN - 2, true); // 0110000000 100101
    mantA.SetBoolAt(MANT_LEN - 3, true);
    charA.SetBoolAt(CHAR_LEN - 1, true); //-
    charA.SetBoolAt(0, true);
    charA.SetBoolAt(2, true);

    mantB.SetBoolAt(MANT_LEN - 2, true); // 0001100000 100101 -> 0110000000 100111
    mantB.SetBoolAt(MANT_LEN - 3, true);
    charB.SetBoolAt(CHAR_LEN - 1, true); //-
    charB.SetBoolAt(0,            true);
    charB.SetBoolAt(1,            true);
    charB.SetBoolAt(2,            true);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_Right_PaGtPb(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, 0);
    CBitBlock charB(CHAR_LEN, 0);

    mantA.SetBoolAt(MANT_LEN - 2, true); // 0100000000 101000
    charA.SetBoolAt(CHAR_LEN - 1, true); //-
    charA.SetBoolAt(CHAR_LEN - 3, true);

    mantB.SetBoolAt(MANT_LEN - 2, true); // 0100000000 100001
    charB.SetBoolAt(CHAR_LEN - 1, true); //-
    charB.SetBoolAt(0,            true);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_Right_PbGtPa(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, 0);
    CBitBlock charB(CHAR_LEN, 0);

    mantA.SetBoolAt(MANT_LEN - 2, true); // 0100000000 101000
    charA.SetBoolAt(CHAR_LEN - 1, true); //-
    charA.SetBoolAt(CHAR_LEN - 3, true);

    mantB.SetBoolAt(MANT_LEN - 2, true); // 0100000000 100001
    charB.SetBoolAt(CHAR_LEN - 1, true); //-
    charB.SetBoolAt(0,            true);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, B); //<-- HERE
    ProgramInputPart(testIndex, 1, A);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFaddTestVector::CreateTest_Right_Zero(unsigned int testIndex) {
    CBitBlock mantA(MANT_LEN, 0);
    CBitBlock mantB(MANT_LEN, 0);

    CBitBlock charA(CHAR_LEN, 0);
    CBitBlock charB(CHAR_LEN, 0);

    mantA.SetBoolAt(MANT_LEN - 2, true); // 0100000000 100101
    charA.SetBoolAt(CHAR_LEN - 1, true); //-
    charA.SetBoolAt(2,            true);
    charA.SetBoolAt(0,            true);

    mantB.SetBoolAt(MANT_LEN - 1, true); // 1100000000 100101 -> 1000000000 100100
    charB.SetBoolAt(CHAR_LEN - 1, true); //-
    charB.SetBoolAt(2,            true);

    bool ok;
    CBitBlock A = MakeBitblockFromMantAndChar(mantA.AsInt(), charA.AsInt(), ok);
    Q_ASSERT(ok);

    CBitBlock B = MakeBitblockFromMantAndChar(mantB.AsInt(), charB.AsInt(), ok);
    Q_ASSERT(ok);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

CBitBlock CFaddTestVector::RightErrorPart(unsigned int testIndex) const {
    return RightOutputPart(testIndex, 0);
}

CBitBlock CFaddTestVector::RightResultPart(unsigned int testIndex) const {
    return RightOutputPart(testIndex, 1);
}

CBitBlock CFaddTestVector::ResultReturn(const CBitBlock &r, unsigned int partIndex) {
    if (partIndex == 0)
        return CBitBlock(DIMENSION,  0); //код ошибки = 0
    return r;
}

CBitBlock CFaddTestVector::ErrorReturn(unsigned int errorCode, unsigned int partIndex) {
    if (partIndex == 0)
        return CBitBlock(DIMENSION,  errorCode);
    return CBitBlock(DIMENSION, 0);
}

CBitBlock CFaddTestVector::MakeResultFromInternals(unsigned int m, unsigned int c) {
    CBitBlock mr(MANT_LEN, m>>1);
    CBitBlock cr(CHAR_LEN, c);

    CBitBlock format(DIMENSION);
    format.CopyFrom(cr, 0);
    format.CopyFrom(mr, CHAR_LEN);

    return format;
}

unsigned int CFaddTestVector::InternalMantFrom(unsigned int m) {
    return (m & (~(1 << MANT_LEN))) | ((m << 1) & (1 << MANT_LEN)); //модифицированный ДК
}

unsigned int CFaddTestVector::InternalMantShr(unsigned int m, unsigned int count) {
    if (count > MANT_LEN)
        count = MANT_LEN;

    unsigned int mask = (1 << (MANT_LEN + 1)) - (1 << (MANT_LEN + 1 - count));

    if (IsNegativeInternalMant(m))
        return (m >> count) | mask;

    return (m >> count) & (~mask);
}

bool CFaddTestVector::IsNormalizedInternalMant(unsigned int m) {
    unsigned int signs = (m >> (MANT_LEN - 1)) & 0x3;
    return (signs == 0x1) || (signs == 0x2);
}

bool CFaddTestVector::IsPositiveInternalCharOverflow(unsigned int c) {
    return ((c >> CHAR_LEN) & 0x3) == 1;
}

bool CFaddTestVector::IsNegativeInternalMant(unsigned int m) {
    return ((m >> MANT_LEN) & 1) != 0;
}

bool CFaddTestVector::IsNegativeInternalChar(unsigned int c) {
    return ((c >> (CHAR_LEN + 1)) & 1) != 0;
}

