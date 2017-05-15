#include "cengineerror.h"

#include <QMessageBox>


void CErrorState::SetSignalRacingError() {
    if (IsError())
        return;

    mSource = ENGINE_SOURCE;
    mSourceItemIndex = 0;
    mReason = SIGNAL_INTERFERENCE;
}

void CErrorState::SetError(TSource source, TReason reason) {
    if (IsError())
        return;

    mSource = source;
    mSourceItemIndex = 0;
    mReason = reason;
}

void CErrorState::SetSignalInterferenceError() {
    if (IsError())
        return;

    mSource = ENGINE_SOURCE;
    mSourceItemIndex = 0;
    mReason = SIGNAL_INTERFERENCE;
}

void CErrorState::SetMuxControlError(CErrorState::TSource source, unsigned int index) {
    if (IsError())
        return;

    mSource = source;
    mSourceItemIndex = index;
    mReason = MUX_CONTROL;
}


void CErrorState::SetRegisterControlError(CErrorState::TSource source, unsigned int index) {
    if (IsError())
        return;

    mSource = source;
    mSourceItemIndex = index;
    mReason = REGISTER_CONTROL;
}

void CErrorState::SetCounterControlError(CErrorState::TSource source, unsigned int index) {
    if (IsError())
        return;

    mSource = source;
    mSourceItemIndex = index;
    mReason = COUNTER_CONTROL;
}

