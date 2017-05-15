#include <stdlib.h>
#include "cpcs1testvector.h"
#include "cpcs1inputdialog.h"

CPcs1TestVector::CPcs1TestVector()
    : CTestVector(/*inputCount      =*/2,
                  /*outputCount     =*/2,
                  /*dimension       =*/8,
                  /*autoTestCount   =*/3,
                  /*inputUi         =*/new CPcs1DebugInputSource()) {}

void CPcs1TestVector::DoInitAutoTests() {
    CreateTest_NZNA_NZPB(0);
    CreateTest_NZNA_NZNB(1);
    CreateTest_NZNA_ZB(2);
}

CBitBlock CPcs1TestVector::DoRightOutputPart(unsigned int testIndex, unsigned int partIndex) const {
    CBitBlock A = InputPart(testIndex, 0);
    CBitBlock B = InputPart(testIndex, 1);

    CBitBlock result(MakeResult(A, B));

    return result.BitsAt(Dimension()*(partIndex + 1) - 1, Dimension()*partIndex);
}

void CPcs1TestVector::CreateTest_NZNA_NZNB(unsigned int testIndex) {
    unsigned int AModulo = rand() & ((1 << (Dimension() - 1)) - 1);
    unsigned int BModulo = rand() & ((1 << (Dimension() - 1)) - 1);

    if (AModulo == 0)
        AModulo = 0x55; //magic

    if (BModulo == 0)
        AModulo = 0x66; //magic

    CBitBlock A(Dimension(), AModulo);
    CBitBlock B(Dimension(), BModulo);

    A.SetAt(Dimension() - 1);
    B.SetAt(Dimension() - 1);

    A.SetAt(Dimension() - 2); //иногда пропускают старший бит
    B.SetAt(Dimension() - 2);

    A.SetAt(0); //иногда пропускают старший бит
    B.SetAt(0);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CPcs1TestVector::CreateTest_NZNA_ZB(unsigned int testIndex) {
    unsigned int AModulo = rand() & ((1 << (Dimension() - 1)) - 1);
    unsigned int BModulo = 0;

    if (AModulo == 0)
        AModulo = 0x55; //magic

    CBitBlock A(Dimension(), AModulo);
    CBitBlock B(Dimension(), BModulo);

    A.SetAt(Dimension() - 1);

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

void CPcs1TestVector::CreateTest_NZNA_NZPB(unsigned int testIndex) {
    unsigned int AModulo = rand() & ((1 << (Dimension() - 1)) - 1);
    unsigned int BModulo = rand() & ((1 << (Dimension() - 1)) - 1);

    if (AModulo == 0)
        AModulo = 0x55; //magic

    if (BModulo == 0)
        AModulo = 0x66; //magic

    CBitBlock A(Dimension(), AModulo);
    CBitBlock B(Dimension(), BModulo); //NZPB

    A.SetAt(Dimension() - 1); //NZNA

    ProgramInputPart(testIndex, 0, A);
    ProgramInputPart(testIndex, 1, B);

    MakeWrongOutputPartsForTest(testIndex);
}

CBitBlock CPcs1TestVector::MakeResult(const CBitBlock &A, const CBitBlock &B) const {
    //modulo
    unsigned int resultModulo = A.BitsAt(Dimension() - 2, 0).AsInt() * B.BitsAt(Dimension() - 2, 0).AsInt();

    CBitBlock result(2*Dimension(), resultModulo);
    //sign
    result.SetBoolAt(2*Dimension() - 1,
                     (A.IsSetAt(Dimension() - 1) != B.IsSetAt(Dimension() - 1))
                        && (resultModulo != 0));
    return result;
}
