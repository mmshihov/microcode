#ifndef CPC2DCALU1_H
#define CPC2DCALU1_H

#include "../../../calu.h"
#include "../../../celectronicunits.h"

class CPc2DcAlu1 : public CAlu {
public:
    static const int Y_RG1_WR  = 0;
    static const int Y_XR1_NOT = 1;
    static const int Y_CT1_WR  = 2;
    static const int Y_CT1_INC = 3;
    static const int Y_BD1_OUT = 4;

    static const int Y_COUNT   = 5;

    static const int P_RG1_7   = 0;

    static const int P_COUNT   = 1;

    CPc2DcAlu1();
    virtual const CRegister*    Register(unsigned int index) const;
    virtual const CCounter*     Counter(unsigned int index) const;
    virtual const CXor*         Xor(unsigned int index) const;
    virtual       CBitBlock     BusMaker(unsigned int index) const;

protected:
    virtual CBitBlock DoDataOutput() const;
    virtual CBitBlock DoControlOutput() const;

    virtual unsigned int DoDataOutCount() const;

    virtual void DoShiftState();
    virtual void DoSpreadInput();

    virtual void DoReset();

    virtual CFunctionalUnit* DoClone() const {return new CPc2DcAlu1(*this);}

private:
    CRegister    mRg1;
    CXor         mXor1;
    CCounter     mCt1;

    CBitBlock BusOut1() const;

    void ClearAllControls();
    unsigned int Ct1Controls() const;
    unsigned int Rg1Controls() const;

    void CheckErrors();

    void ResetCt1();
    void ResetRg1();
};

#endif // CPC2DCALU1_H
