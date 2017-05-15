#ifndef CTEXTOUT_H
#define CTEXTOUT_H

#include <QObject>
#include "cbitblock.h"


class QLabel;
class CEngineModel;
class CErrorState;

class CTextOut : public QObject {
    Q_OBJECT
public:
    explicit CTextOut(QObject *parent = 0);
    
    static QString FormatDec(unsigned int value);

    static unsigned int Bin2HexDim(unsigned int binDim) {return (binDim + 3) / 4;}

    static QString FormatHex(const CBitBlock& block);
    static QString FormatHex(const CBitBlock& block, unsigned int binValueDim);
    static QString FormatHex(unsigned int value, unsigned int binValueDim);

    static QString FormatBin(const CBitBlock& block);
    static QString FormatBin(const CBitBlock& block, unsigned int binValueDim);
    static QString FormatBin(unsigned int value, unsigned int binValueDim);

    static QString FormatBin2n(const CBitBlock& block);
    static QString FormatBin2n(const CBitBlock& block, unsigned int binValueDim);
    static QString FormatBin2n(unsigned int value, unsigned int binValueDim);

    static QString ZStateBin(unsigned int binValueDim);

    static QString UnknownBin(unsigned int binValueDim);
    static QString UnknownHex(unsigned int binValueDim);
    static QString UnknownBin2n(unsigned int binValueDim);

    static void UpdateEngineBus(QLabel *label, const CEngineModel *engine);
    static void UpdateAluCounterVal(QLabel *label,  const CEngineModel *engine, unsigned int index);
    static void UpdateAluRegisterVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluRegister2nVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluTriggerVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluPVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluG2Val(QLabel *label, const CEngineModel *engine, unsigned int index1, unsigned int index2);
    static void UpdateAluYVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluY2Val(QLabel *label, const CEngineModel *engine, unsigned int index1, unsigned int index0);
    static void UpdateAluLogicVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluSmVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluSm2nVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluSmPVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluMsVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluMsHexVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluMs2nVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluXorVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluXor2nVal(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluBusDriverVal(QLabel *label, const CEngineModel *engine, unsigned int index, unsigned int bdOutIndex);
    static void UpdateAluBusDriverHexVal(QLabel *label, const CEngineModel *engine, unsigned int index, unsigned int bdOutIndex);

    static void UpdateAluPhysicalYHint(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluPhysicalY2Hint(QLabel *label, const CEngineModel *engine, unsigned int index1, unsigned int index0);
    static void UpdateAluPhysicalPHint(QLabel *label, const CEngineModel *engine, unsigned int index);
    static void UpdateAluPhysicalG2Hint(QLabel *label, const CEngineModel *engine, unsigned int index1, unsigned int index2);

    static void ShowErrorMessage(QWidget *parent, const CErrorState &error);

private:
    static QString ErrorSourceText(const CErrorState &error);

    static void SignalRacingErrorMessage(QWidget *parent, const CErrorState &error);
    static void SignalInterferenceErrorMessage(QWidget *parent, const CErrorState &error);
    static void RegisterControlErrorMessage(QWidget *parent, const CErrorState &error);
    static void MuxControlErrorMessage(QWidget *parent, const CErrorState &error);
    static void CounterControlErrorMessage(QWidget *parent, const CErrorState &error);
    static void BusResultErrorMessage(QWidget *parent, const CErrorState &error);
    static void BusReadyErrorMessage(QWidget *parent, const CErrorState &error);
    static void ReadEmptyBusErrorMessage(QWidget *parent, const CErrorState &error);
    static void GeneralErrorMessage(QWidget *parent);

signals:
    
public slots:
    
};

#endif // CTEXTOUT_H
