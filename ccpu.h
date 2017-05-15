#ifndef CCPU_H
#define CCPU_H

#include <QString>
#include "cfunctionalunit.h"
#include "ctestvector.h"
#include "sharedptr.h"

class CCpu : public CFunctionalUnit {
public:
    static const unsigned int READY_IN  = 0;
    static const unsigned int RESULT_IN = 1;
    static const unsigned int IN_COUNT  = 2;

    static const unsigned int TASK_OUT  = 0;
    static const unsigned int BUS_OUT   = 1;
    static const unsigned int OUT_COUNT = 2;

    CCpu(SharedPtr<CTestVector> testVector);

    void Halt();
    bool IsSuccessfulStartDebug();
    void StartAutoTests();

    bool IsHaltState() const {return (mState == HALT);}

    unsigned int TestCount() const;
    bool IsAllTestsOk() const;
    bool IsTestOK(unsigned int testIndex) const {return mTestVector->IsTestOk(testIndex);}

    CCpu *Clone() const {return (CCpu *)DoClone();}

    SharedPtr<CTestVector> TestVector() const {return mTestVector;}

protected:
    virtual CBitBlock DoDataOutput() const {return mDataOutput;}
    virtual CBitBlock DoAddressOutput() const {return mDataOutput;}
    virtual CBitBlock DoControlOutput() const {return mControlOutput;}

    virtual unsigned int DoDataOutCount() const {return mDataOutCount;}
    virtual bool DoIsAddressOutput() const {return false;}

    virtual void DoShiftState();
    virtual void DoSpreadInput() {/*DO NOTHING*/}

    virtual void DoReset() {ShiftToHalt();}

    virtual CFunctionalUnit* DoClone() const {return new CCpu(*this);}

    virtual unsigned int DoGetRandomDelay() const;

private:
    enum TMode  {DEBUG, AUTOTEST};
    enum TState {READY_WAIT, TASK_DELAY, TASK, OUT_OPERANDS, RESULT_WAIT, BUS_DELAY, BUS, IN_RESULTS, HALT};

    static const int DEFAULT_MAX_DELAY = 5;

    unsigned int mTestIndex; //0,1,2,3,...
    unsigned int mDelay;

    unsigned int mInputTestPart;
    unsigned int mResultPart;

    TMode        mMode;
    TState       mState;

    unsigned int mDataOutCount;
    CBitBlock    mDataOutput;
    CBitBlock    mControlOutput;

    SharedPtr<CTestVector> mTestVector;

    unsigned int TestIndex() const {return mTestIndex;}
    void SetStartTest() {mTestIndex = 0;}
    void NextTest() {++mTestIndex;}

    bool IsDebugMode() const {return (mMode == DEBUG);}
    bool IsReadyIn() const {return ControlInput().IsSetAt(READY_IN);}
    bool IsResultIn() const {return ControlInput().IsSetAt(RESULT_IN);}

    void HandleReadyWait();
    void HandleTaskDelay();
    void HandleTask();
    void HandleOutOperands();
    void HandleResultWait();
    void HandleBusDelay();
    void HandleBus();
    void HandleInputResults();
    void HandleHalt();

    void ShiftToReadyWait();
    void ShiftToTaskDelay();
    void ShiftToTask();
    void ShiftToOutOperands(unsigned int part);
    void ShiftToResultWait();
    void ShiftToBusDelay();
    void ShiftToBus();
    void ShiftToInputResults(unsigned int part);
    void ShiftToHalt();

    unsigned int GetRandomDelay() const {return DoGetRandomDelay();}

    void DisableDataOutput() {mDataOutCount = 0; mDataOutput.ClearAll();}
    void EnableDataOutput() {mDataOutCount = 1;}

    void SetBusProtocolError(CErrorState::TReason reason);
    void SetBusConflictError();
};

#endif // CCPU_H
