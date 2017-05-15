#ifndef CFUNCTIONALUNIT_H
#define CFUNCTIONALUNIT_H

#include"cbitblock.h"
#include"cengineerror.h"
#include<list>

class CRegister;
class CTrgger;
class CCounter;
class CMultiplexor;
class CSummator;
class CXor;
class CRom;

class CFunctionalUnit {
public:
    CFunctionalUnit(unsigned int dataDim, unsigned int addressDim, unsigned int controlInputDim, unsigned int controlOutputDim);
    virtual ~CFunctionalUnit() {}

    unsigned int DataDim() const {return mDataDim;}
    unsigned int AddressDim() const {return mAddressDim;}
    unsigned int ControlInputDim() const {return mControlInputDim;}
    unsigned int ControlOutputDim() const {return mControlOutputDim;}

    void Reset() {DoReset();}

    bool IsDataOut() const {return (DataOutCount() > 0);}

    unsigned int DataOutCount() const {return DoDataOutCount();}
    bool IsAddressOutput() const {return DoIsAddressOutput();}

    CBitBlock ControlInput() const {return mControlInput;}
    CBitBlock ControlOutput() const {return DoControlOutput();}
    CBitBlock DataOutput() const {return DoDataOutput();}
    CBitBlock AddressOutput() const {return DoAddressOutput();}

    void SetDataInput(const CBitBlock& bitblock) {mDataInput.CopyFrom(bitblock); SetIsDataInput(true);}
    void OffDataInput() {SetIsDataInput(false);}
    void SetAddressInput(const CBitBlock& bitblock) {mAddressInput.CopyFrom(bitblock);SetIsAddressInput(true);}
    void OffAddressInput() {SetIsAddressInput(false);}
    void SetControlInput(const CBitBlock& bitblock) {mControlInput.CopyFrom(bitblock);}

    void ShiftState();
    void SpreadInput();

    CFunctionalUnit* Clone() const {return DoClone();}

    virtual const CRegister* Register(unsigned int /*index*/) const {return 0;}
    virtual       CBitBlock  BusMaker(unsigned int /*index*/) const {return CBitBlock();}
    virtual bool             Trigger(unsigned int /*index*/) const {return 0;}
    virtual const CCounter*  Counter(unsigned int /*index*/) const {return 0;}
    virtual const CMultiplexor* Multiplexor(unsigned int /*index*/) const {return 0;}
    virtual const CSummator*    Summator(unsigned int /*index*/) const {return 0;}
    virtual const CXor* Xor(unsigned int /*index*/) const {return 0;}
    virtual const CRom* Rom(unsigned int /*index*/) const {return 0;}
    virtual bool        Logic(unsigned int /*index*/) const {return false;}

    bool IsError() const {return mErrorState.IsError();}
    void OffError() {mErrorState.OffError();}
    const CErrorState &ErrorState() const {return mErrorState;}

protected:
    CErrorState mErrorState;

    virtual CBitBlock DoDataOutput() const {return CBitBlock();}
    virtual CBitBlock DoAddressOutput() const {return CBitBlock();}
    virtual CBitBlock DoControlOutput() const = 0;

    virtual unsigned int DoDataOutCount() const {return 0;}
    virtual bool DoIsAddressOutput() const {return false;}

    virtual void DoShiftState() = 0;
    virtual void DoSpreadInput() = 0;

    virtual void DoReset() = 0;

    virtual CFunctionalUnit* DoClone() const = 0;


    bool IsDataInput() const {return mIsDataInput;}
    CBitBlock DataInput() const {return mDataInput;}

    bool IsAddressInput() const {return mIsAddressInput;}
    CBitBlock AddressInput() const {return mAddressInput;}

private:
    unsigned int    mDataDim,
                    mAddressDim,
                    mControlInputDim,
                    mControlOutputDim;

    CBitBlock       mDataInput,
                    mAddressInput,
                    mControlInput;

    bool            mIsDataInput,
                    mIsAddressInput;

    void SetIsDataInput(bool isDataInput);
    void SetIsAddressInput(bool isAddressInput);
};


#endif // CFUNCTIONALUNIT_H
