#ifndef CELECTRONICUNITS_H
#define CELECTRONICUNITS_H

#include "cbitblock.h"


class CElectronicUnit {
public:
    CElectronicUnit(unsigned int controls):mControls(controls) {}

    bool IsConflictedControls() const {return DoIsConflictedControls();}

    void ClearAllControls() {mControls = 0;}
    void SetAllControls()   {mControls = ~0;}

    void SetMaskedControls(unsigned int mask) {mControls |= mask;}
    void ClearMaskedControls(unsigned int mask) {mControls &= ~mask;}

    unsigned int Controls() const {return mControls;}

protected:
    bool IsControlSet(unsigned int mask) const {return (mask & mControls) == mask;}

    virtual bool DoIsConflictedControls() const = 0;

private:
    unsigned int mControls;
};


class CRegister : public CElectronicUnit {
public:

    CRegister(unsigned int dim) : CElectronicUnit(0),mDim(dim),mInput(dim),mOutput(dim) {}

    static const unsigned int WR  = 0x01;
    static const unsigned int RST = 0x02;
    static const unsigned int SHR = 0x04;
    static const unsigned int SHL = 0x08;
    static const unsigned int LV  = 0x10;
    static const unsigned int RV  = 0x20;

    unsigned int Dim() const {return mDim;}

    void SetInput(const CBitBlock &bits) {mInput.CopyFrom(bits);}

    CBitBlock Output() const {return mOutput;}

    void ShiftState();

protected:
    virtual bool DoIsConflictedControls() const;

private:

    unsigned int mDim;

    CBitBlock mInput;
    CBitBlock mOutput;
};


class CCounter: public CElectronicUnit {
public:

    CCounter(unsigned int dim) : CElectronicUnit(0),mDim(dim),mInput(dim),mOutput(dim) {}

    static const unsigned int WR  = 0x01;
    static const unsigned int RST = 0x02;
    static const unsigned int INC = 0x04;
    static const unsigned int DEC = 0x08;

    unsigned int Dim() const {return mDim;}

    void SetInput(const CBitBlock &bits) {mInput.CopyFrom(bits);}
    CBitBlock Output() const {return mOutput;}

    void ShiftState();
protected:
    virtual bool DoIsConflictedControls() const;

private:
    unsigned int mDim;

    CBitBlock mInput;
    CBitBlock mOutput;
};


class CMultiplexor {
public:
    CMultiplexor(unsigned int dataDim, unsigned int controlDim);
    CMultiplexor(const CMultiplexor& copy);

    virtual ~CMultiplexor() {Destroy();}

    unsigned int InputDim() const {return mInputDim;}
    unsigned int IndexDim() const {return mIndexDim;}

    void SetInput(const CBitBlock& index, const CBitBlock& input) {mInputs[index.AsInt() & IndexMask()]->CopyFrom(input);}
    void SetInput(unsigned int index, const CBitBlock& input) {mInputs[index & IndexMask()]->CopyFrom(input);}

    CBitBlock Input(unsigned int index) const {return *mInputs[index & IndexMask()];}

    void SetInputIndex(unsigned int index) {mInputIndex = index;}
    unsigned int InputIndex() const {return mInputIndex & IndexMask();}

    CBitBlock Output() const {return *(mInputs[InputIndex()]);}

private:
    unsigned int mInputIndex;

    unsigned int mInputDim;
    unsigned int mIndexDim;

    CBitBlock **mInputs;

    unsigned int IndexPower() const {return (1 << mIndexDim);}
    unsigned int IndexMask() const {return (IndexPower() - 1);}

    void Destroy();
};


class CSummator {
public:
    CSummator(unsigned int dim);

    void SetLeftInput(const CBitBlock& left) {mLeftInput.CopyFrom(left);}
    void SetRightInput(const CBitBlock& right) {mRightInput.CopyFrom(right);}

    void SetC(bool value) {mIsC = value;}

    CBitBlock Output() const;
    bool IsP() const;
private:
    unsigned int    mDim;
    bool            mIsC;
    CBitBlock       mLeftInput,
                    mRightInput;

    bool IsC() const {return mIsC;}
};


class CXor {
public:
    CXor(unsigned int dim):mDim(dim),mInput(dim) {mIsInvert = false;}

    void SetInput(const CBitBlock& input) {mInput.CopyFrom(input);}
    void SetInvert(bool value) {mIsInvert = value;}

    CBitBlock Output() const;
private:
    unsigned int mDim;
    CBitBlock mInput;
    bool mIsInvert;
};


class CRom {
public:
    struct Address { unsigned int row, col; };

    CRom(unsigned int rowCount, unsigned int colCount, unsigned int colDims[]);
    ~CRom() {Destroy();}

    void ProgramCell(const Address& address, const CBitBlock& value);
    bool IsValidAddress(const Address& address) const;
    CBitBlock Cell(const Address& address);
    CBitBlock Cell(unsigned int row, unsigned int col);

    unsigned int ColDim(unsigned int colIndex) const;
    unsigned int ColCount() const {return mColCount;}
    unsigned int RowCount() const {return mRowCount;}

    bool IsProgrammable() const {return mIsProgrammable;}
    void SetProgrammable(bool val) {mIsProgrammable = val;}

private:
    unsigned int  mRowCount;
    unsigned int  mColCount;
    unsigned int *mColDims;
    bool          mIsProgrammable;

    CBitBlock  ***mMatrix;

    void Destroy();
};

#endif // CELECTRONICUNITS_H
