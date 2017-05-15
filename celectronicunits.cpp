#include <QtGlobal>
#include "celectronicunits.h"
#include "cengineerror.h"


bool CRegister::DoIsConflictedControls() const {
    return
            (IsControlSet(WR)  && (IsControlSet(RST) || IsControlSet(SHL) || IsControlSet(SHR)))
        ||  (IsControlSet(RST) && (IsControlSet(SHL) || IsControlSet(SHR)))
        ||  (IsControlSet(SHL) && (IsControlSet(SHR)))
        ;
}


void CRegister::ShiftState() {
    if (IsControlSet(WR)) {
        mOutput = mInput;
        return;
    }

    if (IsControlSet(SHL)) {
        mOutput.Shl(IsControlSet(RV));
        return;
    }

    if (IsControlSet(SHR)) {
        mOutput.Shr(IsControlSet(LV));
        return;
    }

    if (IsControlSet(RST)) {
        mOutput.ClearAll();
        return;
    }
}

//-----------------------------counter---------------------------------
void CCounter::ShiftState() {
    if (IsControlSet(WR)) {
        mOutput = mInput;
        return;
    }

    if (IsControlSet(INC)) {
        mOutput.Inc();
        return;
    }

    if (IsControlSet(DEC)) {
        mOutput.Dec();
        return;
    }

    if (IsControlSet(RST)) {
        mOutput.ClearAll();
        return;
    }
}

bool CCounter::DoIsConflictedControls() const {
    return
            (IsControlSet(WR)  && (IsControlSet(RST) || IsControlSet(INC) || IsControlSet(DEC)))
        ||  (IsControlSet(RST) && (IsControlSet(INC) || IsControlSet(DEC)))
        ||  (IsControlSet(INC) && (IsControlSet(DEC)))
        ;
}

//--------------------------multiplexor------------------------------------------
CMultiplexor::CMultiplexor(unsigned int inputDim, unsigned int indexDim) {
    SetInputIndex(0);

    mInputDim = inputDim;
    mIndexDim = indexDim;

    mInputs = new CBitBlock*[IndexPower()];
    for (unsigned int i = 0; i < IndexPower(); ++i) {
        mInputs[i] = new CBitBlock(InputDim());
    }
}

CMultiplexor::CMultiplexor(const CMultiplexor &copy) {
    SetInputIndex(copy.InputIndex());

    mInputDim = copy.mInputDim;
    mIndexDim = copy.mIndexDim;
    mInputs = new CBitBlock*[IndexPower()];
    for (unsigned int i = 0; i < IndexPower(); ++i) {
        mInputs[i] = new CBitBlock(*(copy.mInputs[i]));
    }
}

void CMultiplexor::Destroy() {
    for (unsigned int i = 0; i < IndexPower(); ++i) {
        delete mInputs[i];
    }
    delete[] mInputs;
    mInputs = 0;
}

//------------------------------summator----------------------------------
CSummator::CSummator(unsigned int dim)
    : mDim(dim)
    , mLeftInput(dim)
    , mRightInput(dim)
{}

CBitBlock CSummator::Output() const {
    CBitBlock a(mLeftInput);

    a += mRightInput;
    if (IsC())
        a.Inc();

    return a;
}

bool CSummator::IsP() const {
    CBitBlock a(mDim + 1);
    a.CopyFrom(mLeftInput);

    CBitBlock b(mDim + 1);
    b.CopyFrom(mRightInput);

    a += b;
    if (IsC())
        a.Inc();

    return a.IsSetAt(mDim);
}

//---------------------------xor-----------------------------------------
CBitBlock CXor::Output() const {
    if (mIsInvert)
        return ~mInput;
    return mInput;
}

//----------------------------rom---------------------------------------
CRom::CRom(unsigned int rowCount, unsigned int colCount, unsigned int colDims[]) {
    mRowCount = rowCount;
    mColCount = colCount;

    mColDims = new unsigned int [colCount];
    for (unsigned int j=0; j<colCount; ++j) {
        mColDims[j] = colDims[j];
    }

    mMatrix = new CBitBlock**[rowCount];
    for (unsigned int i=0; i<rowCount; ++i) {
        mMatrix[i] = new CBitBlock*[colCount];
        for (unsigned int j=0; j<colCount; ++j) {
            mMatrix[i][j] = new CBitBlock(mColDims[j]);
        }
    }
}

void CRom::ProgramCell(const CRom::Address &address, const CBitBlock &value) {
    if ((address.col >= mColCount) || (address.row >= mRowCount))
        return;

    (mMatrix[address.row][address.col])->CopyFrom(value);
}

bool CRom::IsValidAddress(const CRom::Address &address) const {
    return (address.col < mColCount) && (address.row < mRowCount);
}

CBitBlock CRom::Cell(const CRom::Address &address) {
    Q_ASSERT(IsValidAddress(address));

    if (!IsValidAddress(address))
        return CBitBlock();

    return *(mMatrix[address.row][address.col]);
}

CBitBlock CRom::Cell(unsigned int row, unsigned int col) {
    Address a;
    a.col = col;
    a.row = row;
    return Cell(a);
}

unsigned int CRom::ColDim(unsigned int colIndex) const {
    if (colIndex < ColCount())
        return mColDims[colIndex];
    return 0;
}

void CRom::Destroy() {
    for (unsigned int i=0; i<mRowCount; ++i) {
        for (unsigned int j=0; j<mColCount; ++j) {
            delete mMatrix[i][j];
            mMatrix[i][j] = 0;
        }
        delete[] mMatrix[i];
        mMatrix[i] = 0;
    }
    delete[] mMatrix;
    mMatrix = 0;

    for (unsigned int j=0; j<mColCount; ++j) {
        mColDims[j] = 0;
    }
    delete[] mColDims;
    mColDims = 0;

    mRowCount = 0;
    mColCount = 0;
}
