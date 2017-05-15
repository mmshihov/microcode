#include <stdlib.h>
#include "cdcmctestvector.h"
#include "cdcmcinputdialog.h"


CDcmcTestVector::CDcmcTestVector()
    : CTestVector(/*inputCount      =*/2,
                  /*outputCount     =*/2,
                  /*dimension       =*/8,
                  /*autoTestCount   =*/4,
                  /*inputUi         =*/ new CDcmcDebugInputSource()) {}

void CDcmcTestVector::DoInitAutoTests() {
    CreateTest_PP(0);
    CreateTest_PN(1);
    CreateTest_NP(2);
    CreateTest_NN(3);
}

CBitBlock CDcmcTestVector::DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const {
    CBitBlock A = InputPart(testIndex, 0);
    CBitBlock B = InputPart(testIndex, 1);

    CBitBlock result(MakeResult(A, B));

    return result.BitsAt(Dimension()*(partIndex + 1) - 1, Dimension()*partIndex);
}

void CDcmcTestVector::CreateTest_PN(unsigned int testIndex) {
    unsigned int dcA =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       ;
    unsigned int dcB =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       | (1 << (Dimension() - 1))
                       ;

    CBitBlock A(Dimension(), dcA);
    CBitBlock B(Dimension(), dcB);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CDcmcTestVector::CreateTest_NP(unsigned int testIndex) {
    unsigned int dcA =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       | (1 << (Dimension() - 1))
                       ;
    unsigned int dcB =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       ;

    CBitBlock A(Dimension(), dcA);
    CBitBlock B(Dimension(), dcB);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CDcmcTestVector::CreateTest_PP(unsigned int testIndex) {
    unsigned int dcA =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       ;
    unsigned int dcB =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       ;

    CBitBlock A(Dimension(), dcA);
    CBitBlock B(Dimension(), dcB);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CDcmcTestVector::CreateTest_NN(unsigned int testIndex) {
    unsigned int dcA =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       | (1 << (Dimension() - 1))
                       ;
    unsigned int dcB =   (rand() & ((1 << (Dimension() - 2)) - 1))
                       | (1 << (Dimension() - 1))
                       ;

    CBitBlock A(Dimension(), dcA);
    CBitBlock B(Dimension(), dcB);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

CBitBlock CDcmcTestVector::MakeResult(const CBitBlock &A, const CBitBlock &B) const {
    unsigned int dcA  = A.AsInt();
    unsigned int dcB  = B.AsInt();
    unsigned int mask = (1 << Dimension()) - 1;
    unsigned int sign = (1 << (Dimension() - 1));

    unsigned int psm = (dcA & mask) * (dcB & mask);
    if ((dcA & sign) != 0) {
        psm += (((~dcB) + 1) & mask) << Dimension();
    }
    if ((dcB & sign) != 0) {
        psm += (((~dcA) + 1) & mask) << Dimension();
    }

    return CBitBlock(2*Dimension(), psm);
}
