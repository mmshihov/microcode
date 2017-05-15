#include <stdlib.h>
#include "cpc2dctestvector.h"
#include "cpc2dcinputdialog.h"

CPc2DcTestVector::CPc2DcTestVector()
    : CTestVector(/*inputCount      =*/1,
                  /*outputCount     =*/1,
                  /*dimension       =*/8,
                  /*autoTestCount   =*/2,
                  /*inputUi         =*/new CPc2DcDebugInputSource()
                  ) {}

void CPc2DcTestVector::DoInitAutoTests() {
    CreateTest_P(0);
    CreateTest_N(1);
}

CBitBlock CPc2DcTestVector::DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const {
    if (partIndex < OutputPartCount())
        return MakeResult(InputPart(testIndex, partIndex));
    return CBitBlock();
}

void CPc2DcTestVector::CreateTest_P(unsigned int testIndex) {
    unsigned int pcA = (rand() & ((1 << (Dimension() - 2)) - 1));

    CBitBlock A(Dimension(), pcA);

    ProgramInputPart(testIndex, 0, A);

    MakeWrongOutputPartsForTest(testIndex);
}

void CPc2DcTestVector::CreateTest_N(unsigned int testIndex) {
    unsigned int pcA = (rand() & ((1 << (Dimension() - 2)) - 1));

    if (pcA == 0)
        pcA = 0x55;

    pcA |= (1 << (Dimension() - 1));

    CBitBlock A(Dimension(), pcA);

    ProgramInputPart(testIndex, 0, A);

    MakeWrongOutputPartsForTest(testIndex);
}

CBitBlock CPc2DcTestVector::MakeResult(const CBitBlock &A) const {
    unsigned int pcA  = A.AsInt();
    unsigned int sign = (1 << (Dimension() - 1));

    unsigned int dcA = pcA;
    if ((pcA & sign) != 0) {
        dcA = ((~pcA) + 1) | sign;
    }

    return CBitBlock(Dimension(), dcA);
}
