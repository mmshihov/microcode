#include "ctextout.h"

#include <QLabel>
#include <QMessageBox>

#include "cengine.h"
#include "cengineerror.h"
#include "calu.h"
#include "ccpu.h"
#include "celectronicunits.h"

CTextOut::CTextOut(QObject *parent) :  QObject(parent) { }

QString CTextOut::FormatDec(unsigned int value) {
    return QString("%1").arg(value);
}

QString CTextOut::FormatHex(const CBitBlock &block) {
    return FormatHex(block.AsInt(), block.Size());
}

QString CTextOut::FormatHex(unsigned int value, unsigned int binValueDim) {
    unsigned int hexValueDim = (binValueDim + 3) / 4;
    return QString("0x%1").arg(value, hexValueDim, 16, QLatin1Char('0'));
}

QString CTextOut::FormatHex(const CBitBlock &block, unsigned int binValueDim) {
    return FormatHex(block.AsInt(), binValueDim);
}

QString CTextOut::FormatBin(const CBitBlock &block) {
    return FormatBin(block.AsInt(), block.Size());
}

QString CTextOut::FormatBin(const CBitBlock &block, unsigned int binValueDim) {
    return FormatBin(block.AsInt(), binValueDim);
}

QString CTextOut::FormatBin(unsigned int value, unsigned int binValueDim) {
    return QString("%1").arg(value, binValueDim, 2, QLatin1Char('0'));
}

QString CTextOut::FormatBin2n(const CBitBlock &block) {
    return FormatBin2n(block.AsInt(), block.Size());
}

QString CTextOut::FormatBin2n(const CBitBlock &block, unsigned int binValueDim) {
    return FormatBin2n(block.AsInt(), binValueDim);
}

QString CTextOut::FormatBin2n(unsigned int value, unsigned int binValueDim) {
    unsigned int lDim = binValueDim >> 1;
    unsigned int rDim = binValueDim - lDim;

    unsigned int lMask = (1 << lDim) - 1;
    unsigned int rMask = (1 << rDim) - 1;

    return QString("%1 %2")
            .arg((value >> lDim) & rMask, rDim, 2, QLatin1Char('0'))
            .arg(value & lMask, lDim, 2, QLatin1Char('0'))
            ;
}

QString CTextOut::ZStateBin(unsigned int binValueDim) {
    return QString(binValueDim, 'z');
}

QString CTextOut::UnknownBin(unsigned int binValueDim) {
    return QString(binValueDim, '*');
}

QString CTextOut::UnknownHex(unsigned int binValueDim) {
    return QString("0x%1").arg(QString(Bin2HexDim(binValueDim), '*'));
}

QString CTextOut::UnknownBin2n(unsigned int binValueDim) {
    unsigned int lDim = binValueDim >> 1;
    unsigned int rDim = binValueDim - lDim;

    return QString("%1 %2")
            .arg(QString(rDim, '*'))
            .arg(QString(lDim, '*'))
            ;
}

void CTextOut::UpdateEngineBus(QLabel *label, const CEngineModel *engine) {
    unsigned int outCount = engine->DataOutsCount();
    if (outCount == 0) {
        label->setText(CTextOut::ZStateBin(engine->DataDim()));
    } else if (outCount == 1) {
        label->setText(CTextOut::FormatBin(engine->DataBusValue(), engine->DataDim()));
    } else {
        label->setText(CTextOut::UnknownBin(engine->DataDim()));
    }
}

void CTextOut::UpdateAluCounterVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CCounter *counter = engine->CurrentAlu()->Counter(index);
    if (counter != 0) {
        label->setText(FormatBin(counter->Output()));
        return;
    }
    label->setText("?");
}

void CTextOut::UpdateAluRegisterVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CRegister *r = engine->CurrentAlu()->Register(index);
    if (r != 0) {
        label->setText(FormatBin(r->Output()));
        return;
    }
    label->setText(UnknownBin(engine->DataDim()));
}

void CTextOut::UpdateAluRegister2nVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CRegister *r = engine->CurrentAlu()->Register(index);
    if (r != 0) {
        label->setText(CTextOut::FormatBin2n(r->Output()));
        return;
    }
    label->setText(CTextOut::UnknownBin(engine->DataDim()));
}

void CTextOut::UpdateAluTriggerVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    bool value = engine->CurrentAlu()->Trigger(index);
    if (value) {
        label->setText("1");
        return;
    }
    label->setText("0");
}

void CTextOut::UpdateAluPVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    bool value = engine->CurrentAlu()->ControlOutput().IsSetAt(index);
    if (value) {
        label->setText("1");
        return;
    }
    label->setText("0");
}

void CTextOut::UpdateAluG2Val(QLabel *label, const CEngineModel *engine,
                              unsigned int index1, unsigned int index2) {
    bool value1 = engine->CurrentAlu()->ControlOutput().IsSetAt(index1);
    bool value2 = engine->CurrentAlu()->ControlOutput().IsSetAt(index2);
    if (value1) {
        if (value2) {
            label->setText("11");
        } else {
            label->setText("10");
        }
        return;
    } else {
        if (value2) {
            label->setText("01");
        } else {
            label->setText("00");
        }
        return;
    }
    label->setText("0");
}

void CTextOut::UpdateAluYVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    bool value = engine->CurrentAlu()->ControlInput().IsSetAt(index);
    if (value) {
        label->setText("1");
        return;
    }
    label->setText("0");
}

void CTextOut::UpdateAluY2Val(QLabel *label, const CEngineModel *engine, unsigned int index1, unsigned int index0) {
    unsigned int value =
            2*(engine->CurrentAlu()->ControlInput().IsSetAt(index1) ? 1 : 0)
            + (engine->CurrentAlu()->ControlInput().IsSetAt(index0) ? 1 : 0)
            ;
    label->setText(CTextOut::FormatBin(value, 2));
}

void CTextOut::UpdateAluLogicVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    bool value = engine->CurrentAlu()->Logic(index);
    if (value) {
        label->setText("1");
        return;
    }
    label->setText("0");
}

void CTextOut::UpdateAluSmVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CSummator *s = engine->CurrentAlu()->Summator(index);
    if (s != 0) {
        label->setText(CTextOut::FormatBin(s->Output()));
        return;
    }
    label->setText(CTextOut::UnknownBin(engine->DataDim()));
}

void CTextOut::UpdateAluSm2nVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CSummator *s = engine->CurrentAlu()->Summator(index);
    if (s != 0) {
        label->setText(CTextOut::FormatBin2n(s->Output()));
        return;
    }
    label->setText(CTextOut::UnknownBin2n(engine->DataDim()));
}

void CTextOut::UpdateAluSmPVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CSummator *s = engine->CurrentAlu()->Summator(index);
    if (s != 0) {
        label->setText(CTextOut::FormatBin(s->IsP() ? 1 : 0, 1));
        return;
    }
    label->setText(CTextOut::UnknownBin(1));
}

void CTextOut::UpdateAluMsVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CMultiplexor *ms = engine->CurrentAlu()->Multiplexor(index);
    if (ms != 0) {
        label->setText(CTextOut::FormatBin(ms->Output()));
        return;
    }
    label->setText(CTextOut::UnknownBin(engine->DataDim()));
}

void CTextOut::UpdateAluMsHexVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CMultiplexor *ms = engine->CurrentAlu()->Multiplexor(index);
    if (ms != 0) {
        label->setText(CTextOut::FormatHex(ms->Output()));
        return;
    }
    label->setText(CTextOut::UnknownHex(engine->DataDim()));
}

void CTextOut::UpdateAluMs2nVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CMultiplexor *ms = engine->CurrentAlu()->Multiplexor(index);
    if (ms != 0) {
        label->setText(CTextOut::FormatBin2n(ms->Output()));
        return;
    }
    label->setText(CTextOut::UnknownBin2n(engine->DataDim()));
}

void CTextOut::UpdateAluXorVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CXor *xorItem = engine->CurrentAlu()->Xor(index);
    if (xorItem != 0) {
        label->setText(CTextOut::FormatBin(xorItem->Output()));
        return;
    }
    label->setText(CTextOut::UnknownBin(engine->DataDim()));
}

void CTextOut::UpdateAluXor2nVal(QLabel *label, const CEngineModel *engine, unsigned int index) {
    const CXor *xorItem = engine->CurrentAlu()->Xor(index);
    if (xorItem != 0) {
        label->setText(CTextOut::FormatBin2n(xorItem->Output()));
        return;
    }
    label->setText(CTextOut::UnknownBin2n(engine->DataDim()));
}

void CTextOut::UpdateAluBusDriverVal(QLabel *label, const CEngineModel *engine, unsigned int bdIndex, unsigned int bdOutIndex) {
    bool value = engine->CurrentAlu()->ControlInput().IsSetAt(bdOutIndex);
    if (value) {
        CBitBlock value = engine->CurrentAlu()->BusMaker(bdIndex);
        if (!value.IsEmpty()) {
            label->setText(FormatBin(value));
            return;
        }
    }
    label->setText("");
}

void CTextOut::UpdateAluBusDriverHexVal(QLabel *label, const CEngineModel *engine, unsigned int bdIndex, unsigned int bdOutIndex) {
    bool value = engine->CurrentAlu()->ControlInput().IsSetAt(bdOutIndex);
    if (value) {
        CBitBlock value = engine->CurrentAlu()->BusMaker(bdIndex);
        if (!value.IsEmpty()) {
            label->setText(FormatHex(value));
            return;
        }
    }
    label->setText("");
}

void CTextOut::UpdateAluPhysicalYHint(QLabel *label, const CEngineModel *engine, unsigned int index) {
    label->setText(QString("(y%1)").arg(engine->P2LMcuOutputIndex(index + CCpu::IN_COUNT)));
}

void CTextOut::UpdateAluPhysicalY2Hint(QLabel *label, const CEngineModel *engine, unsigned int index1, unsigned int index0) {
    label->setText(QString("(y%1,y%2)")
                   .arg(engine->P2LMcuOutputIndex(index1 + CCpu::IN_COUNT))
                   .arg(engine->P2LMcuOutputIndex(index0 + CCpu::IN_COUNT)));
}

void CTextOut::UpdateAluPhysicalPHint(QLabel *label, const CEngineModel *engine, unsigned int index) {
    label->setText(QString("(p%1)").arg(engine->P2LMcuInputIndex(index + CCpu::OUT_COUNT)));
}

void CTextOut::UpdateAluPhysicalG2Hint(QLabel *label, const CEngineModel *engine,
                                       unsigned int index1, unsigned int index2) {
    label->setText(QString("(p%1,p%2)")
                   .arg(engine->P2LMcuInputIndex(index1 + CCpu::OUT_COUNT))
                   .arg(engine->P2LMcuInputIndex(index2 + CCpu::OUT_COUNT)));
}

void CTextOut::ShowErrorMessage(QWidget *parent, const CErrorState &error) {
    switch (error.Reason()) {
    case CErrorState::SIGNAL_RACING:         SignalRacingErrorMessage(parent, error);       break;
    case CErrorState::SIGNAL_INTERFERENCE:   SignalInterferenceErrorMessage(parent, error); break;
    case CErrorState::REGISTER_CONTROL:      RegisterControlErrorMessage(parent, error);    break;
    case CErrorState::MUX_CONTROL:           MuxControlErrorMessage(parent, error);         break;
    case CErrorState::COUNTER_CONTROL:       CounterControlErrorMessage(parent, error);     break;
    case CErrorState::BUS_RESULT:            BusResultErrorMessage(parent, error);          break;
    case CErrorState::BUS_READY:             BusReadyErrorMessage(parent, error);           break;
    case CErrorState::READ_EMPTY_BUS:        ReadEmptyBusErrorMessage(parent, error);       break;
    default:
        GeneralErrorMessage(parent);
    }
}

QString CTextOut::ErrorSourceText(const CErrorState &error) {
    switch (error.Source()) {
    case CErrorState::CPU_SOURCE: return tr("CPU error");
    case CErrorState::MCU_SOURCE: return tr("MCU error");
    case CErrorState::ALU_SOURCE: return tr("ALU error");
    case CErrorState::ENGINE_SOURCE:
    default:
        return tr("General error");
    }
}

void CTextOut::SignalRacingErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent, ErrorSourceText(error), tr("Is signal racing!"));
}

void CTextOut::SignalInterferenceErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent, ErrorSourceText(error), tr("Data bus conflict!"));
}

void CTextOut::RegisterControlErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent,
                         ErrorSourceText(error),
                         QString(tr("Rg%1 control error!"))
                         .arg(error.SourceItemIndex()));
}

void CTextOut::MuxControlErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent,
                         ErrorSourceText(error),
                         QString(tr("Ms%1 control error!"))
                         .arg(error.SourceItemIndex()));
}

void CTextOut::CounterControlErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent,
                         ErrorSourceText(error),
                         QString(tr("Ct%1 control error!"))
                         .arg(error.SourceItemIndex()));
}

void CTextOut::BusResultErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent,
                         ErrorSourceText(error),
                         tr("'RESULT' signal error!"));
}

void CTextOut::BusReadyErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent,
                         ErrorSourceText(error),
                         tr("'READY' signal error!"));
}

void CTextOut::ReadEmptyBusErrorMessage(QWidget *parent, const CErrorState &error) {
    QMessageBox::warning(parent,
                         ErrorSourceText(error),
                         tr("Read empty D-bus!"));
}

void CTextOut::GeneralErrorMessage(QWidget *parent) {
    QMessageBox::warning(parent,
                         tr("Error"),
                         tr("Is unknown error occured..."));
}
