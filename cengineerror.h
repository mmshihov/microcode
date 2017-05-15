#ifndef CENGINEERROR_H
#define CENGINEERROR_H

class QWidget;


class CErrorState {
public:
    enum TSource {CPU_SOURCE, MCU_SOURCE, ALU_SOURCE, ENGINE_SOURCE};
    enum TReason {    SIGNAL_RACING
                    , SIGNAL_INTERFERENCE
                    , REGISTER_CONTROL
                    , MUX_CONTROL
                    , COUNTER_CONTROL
                    , BUS_RESULT
                    , BUS_READY
                    , READ_EMPTY_BUS
                    , NO_ERROR
                 };

    bool IsError() const {return mReason != NO_ERROR;}
    void OffError() {mReason = NO_ERROR;}

    TSource Source() const {return mSource;}
    unsigned int SourceItemIndex() const {return mSourceItemIndex;}
    TReason Reason() const {return mReason;}

    void SetSignalRacingError();
    void SetError(TSource source, TReason reason);
    void SetSignalInterferenceError();
    void SetMuxControlError(TSource source, unsigned int index);
    void SetRegisterControlError(TSource source, unsigned int index);
    void SetCounterControlError(TSource source, unsigned int index);

private:
    TSource      mSource;
    unsigned int mSourceItemIndex;
    TReason      mReason;
};

#endif // CENGINEERROR_H
