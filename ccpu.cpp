#include <stdlib.h>
#include "ccpu.h"
#include "cengineerror.h"


CCpu::CCpu(SharedPtr<CTestVector> testVector)
    : CFunctionalUnit(testVector->Dimension(), 0, IN_COUNT, OUT_COUNT)
    , mDataOutCount(0)
    , mDataOutput(testVector->Dimension())
    , mControlOutput(OUT_COUNT)
    , mTestVector(testVector)
{ }

void CCpu::Halt() {
    ShiftToHalt();
}

bool CCpu::IsSuccessfulStartDebug() {
    mMode = DEBUG;

    SetStartTest();
    ShiftToReadyWait();

    return mTestVector->IsSuccessfulInitDebugTest();
}

void CCpu::StartAutoTests() {
    mMode = AUTOTEST;

    SetStartTest();
    ShiftToReadyWait();

    mTestVector->InitAutoTests();
}

unsigned int CCpu::TestCount() const {
    if (IsDebugMode())
        return 1;

    return mTestVector->AutoTestCount();
}

//0: ожидание сигнала "ГОТОВ" от операционной части
//1: случайная задержка (если за это время сигнал "ГОТОВ" уходит, то выдается ошибка)
//2: выдача сигнала "ОПЕРАНДЫ НА ШИНЕ"
//3: выдача операндов (попутная их генерация)
//4: ожидание сигнала "РЕЗУЛЬТАТ ГОТОВ"
//5: от 0 до 5 тактов задержки
//6: выдача сигнала "ШИНА ТВОЯ"
//7: чтение результатов и сверка (самостоятельное получение резльтата по сгенерированным операндам)
void CCpu::DoShiftState() {
    switch (mState) {
    case READY_WAIT:    HandleReadyWait();      break;
    case TASK_DELAY:    HandleTaskDelay();      break;
    case TASK:          HandleTask();           break;
    case OUT_OPERANDS:  HandleOutOperands();    break;
    case RESULT_WAIT:   HandleResultWait();     break; //максимальное количество тактов ожидания?
    case BUS_DELAY:     HandleBusDelay();       break;
    case BUS:           HandleBus();            break;
    case IN_RESULTS:    HandleInputResults();   break;
    case HALT:          HandleHalt();           break;
    default:
        Q_ASSERT(false); break;
    }
}

unsigned int CCpu::DoGetRandomDelay() const {
    return (rand() % DEFAULT_MAX_DELAY);
}

bool CCpu::IsAllTestsOk() const {
    for (unsigned int step = 0; step < TestCount(); ++step) {
        if (!IsTestOK(step))
            return false;
    }
    return true;
}

void CCpu::HandleReadyWait() {
    Q_ASSERT(mState == READY_WAIT);

    if (IsDataInput()) {
        SetBusConflictError();
        return;
    }

    if (ControlInput().IsSetAt(READY_IN)) {
        mDelay = GetRandomDelay();
        ShiftToTaskDelay();
        if (mDelay == 0)
            ShiftToTask();
    }
}

void CCpu::HandleTaskDelay() {
    Q_ASSERT(mState == TASK_DELAY);

    if (IsDataInput()) {
        SetBusConflictError();
        return;
    }

    if (mDelay == 0) {
        ShiftToTask();
        return;
    }

    if (ControlInput().IsSetAt(RESULT_IN)) {
        SetBusProtocolError(CErrorState::BUS_RESULT);
        return;
    }
    if (ControlInput().IsClearAt(READY_IN)) {
        SetBusProtocolError(CErrorState::BUS_READY);
        return;
    }

    --mDelay;

    if (mDelay == 0)
        ShiftToTask();
}

void CCpu::HandleTask() {
    Q_ASSERT(mState == TASK);

    if (IsDataInput()) {
        SetBusConflictError();
        return;
    }
    if (ControlInput().IsSetAt(RESULT_IN)) {
        SetBusProtocolError(CErrorState::BUS_RESULT);
        return;
    }
    if (ControlInput().IsClearAt(READY_IN)) {
        SetBusProtocolError(CErrorState::BUS_READY);
        return;
    }

    ShiftToOutOperands(0);
}

void CCpu::HandleOutOperands() {
    Q_ASSERT(mState == OUT_OPERANDS);

    if (ControlInput().IsSetAt(READY_IN)) {
        SetBusProtocolError(CErrorState::BUS_READY);
        return;
    }
    if (ControlInput().IsSetAt(RESULT_IN)) {
        SetBusProtocolError(CErrorState::BUS_RESULT);
        return;
    }

    if (mInputTestPart >= mTestVector->InputPartCount()) {
        if (ControlInput().IsSetAt(RESULT_IN)) {
            ShiftToBus();
            return;
        }
        ShiftToResultWait();
        return;
    }
    ShiftToOutOperands(mInputTestPart);
}

void CCpu::HandleResultWait() {
    Q_ASSERT(mState == RESULT_WAIT);

    if (IsDataInput()) {
        SetBusConflictError();
        return;
    }
    if (ControlInput().IsSetAt(READY_IN)) {
        SetBusProtocolError(CErrorState::BUS_READY);
        return;
    }

    if (ControlInput().IsSetAt(RESULT_IN)) {
        mDelay = GetRandomDelay();
        if (mDelay == 0) {
            ShiftToBus();
            return;
        }
        ShiftToBusDelay();
        return;
    }
    ShiftToResultWait();
}

void CCpu::HandleBusDelay() {
    Q_ASSERT(mState == BUS_DELAY);

    if (IsDataInput()) {
        SetBusConflictError();
        return;
    }

    if (mDelay == 0) {
        ShiftToBus();
        return;
    }

    if (ControlInput().IsSetAt(READY_IN)) {
        SetBusProtocolError(CErrorState::BUS_READY);
        return;
    }
    if (ControlInput().IsClearAt(RESULT_IN)) {
        SetBusProtocolError(CErrorState::BUS_RESULT);
        return;
    }

    --mDelay;

    if (mDelay <= 0)
        ShiftToBus();
}

void CCpu::HandleBus() {
    Q_ASSERT(mState == BUS);

    if (IsDataInput()) {
        SetBusConflictError();
        return;
    }
    if (ControlInput().IsSetAt(READY_IN)) {
        SetBusProtocolError(CErrorState::BUS_READY);
        return;
    }
    if (ControlInput().IsClearAt(RESULT_IN)) {
        SetBusProtocolError(CErrorState::BUS_RESULT);
        return;
    }

    ShiftToInputResults(0);
}

void CCpu::HandleInputResults() {
    Q_ASSERT(mState == IN_RESULTS);
    Q_ASSERT(mResultPart < mTestVector->OutputPartCount());

    if (ControlInput().IsSetAt(RESULT_IN)) {
        SetBusProtocolError(CErrorState::BUS_RESULT);
        return;
    }

    if (!IsDataInput()) {
        SetBusProtocolError(CErrorState::READ_EMPTY_BUS);
        return;
    }

    mTestVector->SetOutputPart(TestIndex(), mResultPart, DataInput());
    mResultPart++;
    if (mResultPart >= mTestVector->OutputPartCount()) {
        NextTest();
        if (TestIndex() >= TestCount()) {
            ShiftToHalt();
            return;
        }

        if (ControlInput().IsSetAt(READY_IN)) {
            ShiftToTask();
            return;
        }

        ShiftToReadyWait();
        return;
    }

    if (ControlInput().IsSetAt(READY_IN)) {
        SetBusProtocolError(CErrorState::BUS_READY);
        return;
    }

    ShiftToInputResults(mResultPart);
}

void CCpu::HandleHalt() {
    mState = HALT;

    DisableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::ShiftToReadyWait() {
    mState = READY_WAIT;

    DisableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::ShiftToTaskDelay() {
    mState = TASK_DELAY;

    DisableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::ShiftToTask() {
    mState = TASK;

    DisableDataOutput();
    mControlOutput.ClearAll();
    mControlOutput.SetAt(TASK_OUT);
}

void CCpu::ShiftToOutOperands(unsigned int part) {
    mState = OUT_OPERANDS;

    mInputTestPart = part;
    mDataOutput = mTestVector->InputPart(mTestIndex, mInputTestPart);
    mInputTestPart++;

    EnableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::ShiftToResultWait() {
    mState = RESULT_WAIT;

    DisableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::ShiftToBusDelay() {
    mState = BUS_DELAY;

    DisableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::ShiftToBus() {
    mState = BUS;

    DisableDataOutput();
    mControlOutput.ClearAll();
    mControlOutput.SetAt(BUS_OUT);
}

void CCpu::ShiftToInputResults(unsigned int part) {
    Q_ASSERT(part < mTestVector->OutputPartCount());

    mState = IN_RESULTS;

    mResultPart = part;
    DisableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::ShiftToHalt() {
    mState = HALT;

    DisableDataOutput();
    mControlOutput.ClearAll();
}

void CCpu::SetBusProtocolError(CErrorState::TReason reason) {
    mErrorState.SetError(CErrorState::CPU_SOURCE, reason);
    ShiftToHalt();
}

void CCpu::SetBusConflictError() {
    mErrorState.SetError(CErrorState::CPU_SOURCE, CErrorState::SIGNAL_INTERFERENCE);
    ShiftToHalt();
}

