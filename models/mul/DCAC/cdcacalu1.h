#ifndef CDCACALU1_H
#define CDCACALU1_H

#include "../../../calu.h"
#include "../../../celectronicunits.h"

class CDcacAlu1 : public CAlu {
public:
    static const int Y_RG1_WR        = 0;
    static const int Y_RG1_SHR       = 1;
    static const int Y_RG2_WR        = 2;
    static const int Y_SM1_C_RG2_NOT = 3;
    static const int Y_CT1_WR        = 4;
    static const int Y_CT1_INC       = 5;
    static const int Y_RG3_RST       = 6;
    static const int Y_RG3_WR        = 7;
    static const int Y_RG3_RG4_SHR   = 8;
    static const int Y_BD1_OUT       = 9;
    static const int Y_BD2_OUT       = 10;

    static const int Y_COUNT         = 11;

    static const int P_RG1_0   = 0;
    static const int P_RG1_1   = 1;
    static const int P_CT1_3   = 2;

    static const int P_COUNT   = 3;

    CDcacAlu1();

    virtual const CRegister* Register(unsigned int index) const;
    virtual const CCounter*  Counter(unsigned int index) const;
    virtual const CSummator* Summator(unsigned int index) const;
    virtual const CXor*      Xor(unsigned int index) const;
    virtual       CBitBlock  BusMaker(unsigned int index) const;

protected:
    virtual CBitBlock DoDataOutput() const;
    virtual CBitBlock DoControlOutput() const;

    virtual unsigned int DoDataOutCount() const;

    virtual void DoShiftState();
    virtual void DoSpreadInput();

    virtual void DoReset();

    virtual CFunctionalUnit* DoClone() const {return new CDcacAlu1(*this);}

private:
    CRegister    mRg1,mRg2,mRg3,mRg4;
    CCounter     mCt1;
    CXor         mXor1;
    CSummator    mSm1;

    CBitBlock BusOut1() const;
    CBitBlock BusOut2() const;

    void ClearAllControls();
    unsigned int Ct1Controls() const;
    unsigned int Rg1Controls() const;
    unsigned int Rg2Controls() const;
    unsigned int Rg3Controls() const;
    unsigned int Rg4Controls() const;

    void CheckErrors();

    void ResetCt1();
    void ResetRg1();
    void ResetRg2();
    void ResetRg3();
    void ResetRg4();
};

#endif // CDCACALU1_H
