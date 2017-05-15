#include "cfunctionalunit.h"


CFunctionalUnit::CFunctionalUnit(unsigned int dataDim, unsigned int addressDim, unsigned int controlInputDim, unsigned int controlOutputDim) :
    mDataDim(dataDim),
    mAddressDim(dataDim),
    mControlInputDim(controlInputDim),
    mControlOutputDim(controlOutputDim),
    mDataInput(dataDim),
    mAddressInput(addressDim),
    mControlInput(controlInputDim)
{}

void CFunctionalUnit::ShiftState() {
    if (!IsError()) {
        DoShiftState();
        SetIsDataInput(false);
        SetIsAddressInput(false);
    }
}

void CFunctionalUnit::SpreadInput() {
    if (!IsError())
        DoSpreadInput();
}

void CFunctionalUnit::SetIsDataInput(bool isDataInput) {
    mIsDataInput = isDataInput;
    if (!mIsDataInput)
        mDataInput.ClearAll();
}

void CFunctionalUnit::SetIsAddressInput(bool isAddressInput) {
     mIsAddressInput = isAddressInput;
     if (!mIsAddressInput)
         mAddressInput.ClearAll();
}
