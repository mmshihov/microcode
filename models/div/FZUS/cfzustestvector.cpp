#include <stdlib.h>
#include "cfzustestvector.h"
#include "cfzusinputdialog.h"

CFzusTestVector::CFzusTestVector()
    : CTestVector(/*inputCount      =*/2,
                  /*outputCount     =*/2,
                  /*dimension       =*/8,
                  /*autoTestCount   =*/3,
                  /*inputUi         =*/new CFzusDebugInputSource()) {}

void CFzusTestVector::DoInitAutoTests() {
    CreateTest_1Q1R(0);
    CreateTest_0Q1R(1);
    CreateTest_1Q0R(2);
}

CBitBlock CFzusTestVector::DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const {
    CBitBlock A = InputPart(testIndex, 0);
    CBitBlock B = InputPart(testIndex, 1);

    CBitBlock result(MakeResult(A, B));

    return result.BitsAt(Dimension()*(partIndex + 1) - 1, Dimension()*partIndex);
}

void CFzusTestVector::CreateTest_0Q1R(unsigned int testIndex) {
    unsigned int mask = (1 << (Dimension()/2)) - 1;

    unsigned int B = rand() & mask;
    unsigned int q = 0;
    unsigned int r = rand() & mask;

    if (B < 2)
        B = 3;

    if (B <= r)
        r = B - 1;

    unsigned int A = q*B + r;

    CBitBlock aBlock(Dimension(), A);
    CBitBlock bBlock(Dimension(), B);

    ProgramInputPart(testIndex, 0, aBlock);
    ProgramInputPart(testIndex, 1, bBlock);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFzusTestVector::CreateTest_1Q0R(unsigned int testIndex) {
    unsigned int mask = (1 << (Dimension()/2)) - 1;

    unsigned int B = rand() & mask;
    unsigned int q = rand() & mask;
    unsigned int r = 0;

    if (B == 0)
        B = 3;

    if (q == 0)
        q = 3;

    unsigned int A = q*B + r;

    CBitBlock aBlock(Dimension(), A);
    CBitBlock bBlock(Dimension(), B);

    ProgramInputPart(testIndex, 0, aBlock);
    ProgramInputPart(testIndex, 1, bBlock);

    MakeWrongOutputPartsForTest(testIndex);
}

void CFzusTestVector::CreateTest_1Q1R(unsigned int testIndex) {
    unsigned int mask = (1 << (Dimension()/2)) - 1;

    unsigned int B = rand() & mask;
    unsigned int q = rand() & mask;
    unsigned int r = rand() & mask;

    if (B < 2)
        B = 3;

    if (B <= r)
        r = B - 1;

    if (q == 0)
        q = 3;

    unsigned int A = q*B + r;

    CBitBlock aBlock(Dimension(), A);
    CBitBlock bBlock(Dimension(), B);

    ProgramInputPart(testIndex, 0, aBlock);
    ProgramInputPart(testIndex, 1, bBlock);

    MakeWrongOutputPartsForTest(testIndex);
}

CBitBlock CFzusTestVector::MakeResult(const CBitBlock &aBlock, const CBitBlock &bBlock) const {
    unsigned int mask = (1 << Dimension()) - 1;

    unsigned int A = aBlock.AsInt() & mask;
    unsigned int B = bBlock.AsInt() & mask;


    if (B == 0)
        return CBitBlock(2*Dimension(), (mask << Dimension()) | mask);

    unsigned int q = A / B;
    unsigned int r = A % B;

    return CBitBlock(2*Dimension(), (r << Dimension()) | q);
}
