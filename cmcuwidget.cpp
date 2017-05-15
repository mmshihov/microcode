#include "cmcuwidget.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>
#include <QHeaderView>
#include <QLabel>

#include "cromtablemodel.h"
#include "cromeditordelegate.h"

#include "csignalvalue.h"
#include "cmanual.h"
#include "cmilitwostateselect.h"
#include "cmilifourstateselect.h"
#include "cmooretwostateselect.h"
#include "cmoorefourstateselect.h"

void CMcuWidgetEngineController::DoUpdateMemoryView() {
    if (mView->McuType() == Engine()->CurrentMcuType())
        mView->UpdateMemoryView(Engine());
}

void CMcuWidgetEngineController::DoUpdateLogicView() {
    if (mView->McuType() == Engine()->CurrentMcuType())
        mView->UpdateLogicView(Engine());
}

void CMcuWidgetEngineController::DoUpdateHintsView() {
    if (mView->McuType() == Engine()->CurrentMcuType())
        mView->UpdateHintsView(Engine());
}

void CMcuWidgetEngineController::DoUpdateModeView() {
    if (mView->McuType() == Engine()->CurrentMcuType())
        mView->UpdateModeView(Engine());
}

void CMcuWidgetEngineController::DoUpdateMcuTypeView() {
    UpdateHintsView();
}


// ------------------------------------------------------

CMcuWidget::CMcuWidget(CEngineModel::TMcuType mcuType,
                       CEngineModel *engine,
                       QWidget *parent)
    : QWidget(parent)
    , mMcuType(mcuType)
    , mEngineController(this)
{
    mMcuController = 0;
    mInputValues   = 0;
    mOutputValues  = 0;

    mGroupDim         = (mcuType == CEngineModel::MANUAL_MCU) ? 1 : engine->GroupDim();
    mControlInputDim  = engine->McuControlInputDim();
    mControlOutputDim = engine->McuControlOutputDim();

    engine->AppendController(&mEngineController); //connects engine to controller

    CreateUi(engine);
    mEngineController.UpdateHintsView();
}

void CMcuWidget::UpdateMemoryView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == McuType());
    Q_ASSERT(mMcuController != 0);

    mMcuController->UpdateMemory(engine);
    UpdateSignalValues(engine);

    UpdateRomSelection(engine);
}

void CMcuWidget::UpdateLogicView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == McuType());
    Q_ASSERT(mMcuController != 0);

    mMcuController->UpdateLogic(engine);
    UpdateSignalValues(engine);
}

void CMcuWidget::UpdateHintsView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == McuType());
    Q_ASSERT(mMcuController != 0);

    mMcuController->UpdateHints(engine);
}

void CMcuWidget::UpdateModeView(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == McuType());


    mRomTableView->setEnabled((! engine->IsExecutionMode())
                              || (engine->CurrentMcuType() == CEngineModel::MANUAL_MCU));
}

void CMcuWidget::CreateUi(const CEngineModel *model) {
    Q_ASSERT(model != 0);

    QWidget *inputWidget    = CreateInputWidget();
    QWidget *romLabelWidget = CreateRomLabelWidget();
    QWidget *romWidget      = CreateRomWidget(model);
    QWidget *mcuWidget      = CreateMcuWidget();
    QWidget *outputWidget   = CreateOutputWidget();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    QSplitter   *splitter = new QSplitter();
    splitter->setOrientation(Qt::Vertical);

    splitter->addWidget(romWidget);
    splitter->addWidget(mcuWidget);

    layout->addWidget(inputWidget);
    layout->addWidget(romLabelWidget);
    layout->addWidget(splitter);
    layout->addWidget(outputWidget);

    setLayout(layout);

    setFixedSize(WIDGET_WIDTH, WIDGET_HEIGHT);
}

QWidget *CMcuWidget::CreateIoGroup(
        unsigned int groupIndex,
        unsigned int groupDim,
        CSignalValue **signalValues,
        const QString &hint) {
    if (groupDim == 1) {
        CSignalValue *signalValue = new CSignalValue();
        signalValue->SetSignalHint(QString("%1%2").arg(hint).arg(groupIndex)); //y1,...,p2
        signalValues[groupIndex] = signalValue;
        return signalValue;
    } else {
        QHBoxLayout *layout = new QHBoxLayout();
        layout->setDirection(QBoxLayout::RightToLeft);
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);

        for (unsigned int signalOffset=0; signalOffset<groupDim; ++signalOffset) {
            CSignalValue *signalValue = new CSignalValue();
            unsigned int signalIndex = groupIndex * groupDim + signalOffset;

            signalValues[signalIndex] = signalValue;

            if (signalIndex < ControlInputDim()) {
                signalValue->SetSignalHint(QString("%1%2").arg(hint).arg(signalIndex));
            } else {
                signalValue->SetSignalHint("--");
            }
            layout->addWidget(signalValue);
        }

        QGroupBox *box = new QGroupBox(QString("g%1").arg(groupIndex));
        box->setLayout(layout);
        box->adjustSize();

        return box;
    }
}

QWidget *CMcuWidget::CreateIoWidget(unsigned int groupDim, unsigned int valuesDim, CSignalValue **&signalValues, const QString &hint) {
    QLayout *layout = 0;
    unsigned int groupCount = (valuesDim + groupDim - 1) / groupDim;
    unsigned int valuesCount = groupCount * groupDim;

    signalValues = new CSignalValue*[valuesCount];
    for (unsigned int i=0; i<valuesCount; ++i)
        signalValues[i] = 0;

    QWidget *box = CreateIoGroup(0, groupDim, signalValues, hint);

    int itemWidth = box->width();
    int myWidth  = itemWidth;
    int myHeight = box->height();
    int myHeightDelta = box->height();
    unsigned int colCount = (unsigned int) WIDGET_WIDTH / itemWidth;

    if (groupCount <= colCount) {
        unsigned int i = 0;
        QHBoxLayout *rowLayout = new QHBoxLayout();
        rowLayout->setSpacing(0);
        rowLayout->setContentsMargins(0,0,0,0);
        rowLayout->setDirection(QBoxLayout::RightToLeft);
        while (1) {
            rowLayout->addWidget(box);
            i++;
            if (i >= groupCount)
                break;
            myWidth += itemWidth;
            box = CreateIoGroup(i, groupDim, signalValues, hint);
        }
        if (myWidth < WIDGET_WIDTH)
            rowLayout->addSpacing(WIDGET_WIDTH - myWidth);
        layout = rowLayout;
    } else {
        unsigned int i = 0, j = 0;

        QVBoxLayout *colLayout = new QVBoxLayout();
        colLayout->setSpacing(0);
        colLayout->setContentsMargins(0,0,0,0);
        colLayout->setDirection(QBoxLayout::BottomToTop);

        QHBoxLayout *rowLayout = new QHBoxLayout();
        rowLayout->setSpacing(0);
        rowLayout->setContentsMargins(0,0,0,0);
        rowLayout->setDirection(QBoxLayout::RightToLeft);
        while (1) {
            rowLayout->addWidget(box);

            i++;
            j++;

            if (i >= groupCount) {
                if (myWidth < WIDGET_WIDTH)
                    rowLayout->addSpacing(WIDGET_WIDTH - myWidth);

                QWidget *widget = new QWidget();
                widget->setLayout(rowLayout);
                widget->adjustSize();
                colLayout->addWidget(widget);
                break;
            }

            if (j >= colCount) {
                if (myWidth < WIDGET_WIDTH)
                    rowLayout->addSpacing(WIDGET_WIDTH - myWidth);

                QWidget *widget = new QWidget();
                widget->setLayout(rowLayout);

                colLayout->addWidget(widget);

                j = 0;

                myWidth = 0;
                myHeight += myHeightDelta;

                rowLayout = new QHBoxLayout();
                rowLayout->setSpacing(0);
                rowLayout->setContentsMargins(0,0,0,0);
                rowLayout->setDirection(QBoxLayout::RightToLeft);
            }

            myWidth += itemWidth;

            box = CreateIoGroup(i, groupDim, signalValues, hint);
        }
        layout = colLayout;
    }

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    widget->setContentsMargins(0,0,0,0);
    widget->setFixedSize(WIDGET_WIDTH, myHeight);

    return widget;
}

QWidget *CMcuWidget::CreateInputWidget() {
    return CreateIoWidget(GroupDim(), ControlInputDim(), mInputValues, "p");
}

QWidget *CMcuWidget::CreateOutputWidget() {
    return CreateIoWidget(1, ControlOutputDim(), mOutputValues, "y");
}

QWidget *CMcuWidget::CreateRomLabelWidget() {
    switch (McuType()) {
    case CEngineModel::MANUAL_MCU:
        return new QLabel(tr("Microcommands ROM:"));
    case CEngineModel::MILI_MCU:
    case CEngineModel::MOORE_MCU:
        return new QLabel(tr("Microprogram ROM:"));
    }
    return new QLabel(tr("ROM:"));
}

QWidget *CMcuWidget::CreateRomWidget(const CEngineModel *model) {
    mRomModel     = 0;
    mRomTableView = new QTableView();

    switch(McuType()) {
    case CEngineModel::MANUAL_MCU:
        mRomModel = new CManualRomTableModel(model->ManualProgramRom());
        break;
    case CEngineModel::MILI_MCU:
        mRomModel = new CMiliRomTableModel(model->MiliProgramRom(), model->GroupDim());
        break;
    case CEngineModel::MOORE_MCU:
        mRomModel = new CMooreRomTableModel(model->MooreProgramRom(), model->GroupDim());
        break;
    default:
        Q_ASSERT(false);
        return 0;
    }

    mRomTableView->setItemDelegate(new CRomEditorDelegate());
    mRomTableView->setModel(mRomModel);
    mRomTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mRomTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i=0; i<mRomModel->columnCount(); ++i)
        mRomTableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);

    //TODO подключать только в ручном режиме...
    ConnectSignalsToRomTable();

    return mRomTableView;
}

QWidget *CMcuWidget::CreateMcuWidget() {
    switch(McuType()) {
    case CEngineModel::MANUAL_MCU: return CreateManualMcu();
    case CEngineModel::MILI_MCU:   return CreateMiliMcu();
    case CEngineModel::MOORE_MCU:  return CreateMooreMcu();
    default:
        Q_ASSERT(false);
        return 0;
    }
}

QWidget *CMcuWidget::CreateManualMcu() {
    Q_ASSERT(McuType() == CEngineModel::MANUAL_MCU);

    CManual *mcu = new CManual();
    mMcuController = mcu->McuController();
    return mcu;
}

QWidget *CMcuWidget::CreateMiliMcu() {
    Q_ASSERT(McuType() == CEngineModel::MILI_MCU);

    if (GroupDim() == 1) {
        CMiliTwoStateSelect *mcu = new CMiliTwoStateSelect();
        mMcuController = mcu->McuController();
        return mcu;
    } else if (GroupDim() == 2) {
        CMiliFourStateSelect *mcu = new CMiliFourStateSelect();
        mMcuController = mcu->McuController();
        return mcu;
    } else
        return 0;
}

QWidget *CMcuWidget::CreateMooreMcu() {
    Q_ASSERT(McuType() == CEngineModel::MOORE_MCU);

    if (GroupDim() == 1) {
        CMooreTwoStateSelect *mcu = new CMooreTwoStateSelect();
        mMcuController = mcu->McuController();
        return mcu;
    } else if (GroupDim() == 2) {
        CMooreFourStateSelect *mcu = new CMooreFourStateSelect();
        mMcuController = mcu->McuController();
        return mcu;
    } else
        return 0;
}

void CMcuWidget::UpdateSignalValues(const CEngineModel *engine) {
    const CMcu *mcu = engine->CurrentMcu();

    CBitBlock input(mcu->ControlInput());
    for (unsigned int ii=0; ii<ControlInputDim(); ++ii) {
        Q_ASSERT(mInputValues[ii] != 0);
        mInputValues[ii]->SetSignalValue(input.IsSetAt(ii));
    }

    CBitBlock output(mcu->ControlOutput());
    for (unsigned int oi=0; oi<ControlOutputDim(); ++oi) {
        Q_ASSERT(mOutputValues[oi] != 0);
        mOutputValues[oi]->SetSignalValue(output.IsSetAt(oi));
    }
}

void CMcuWidget::UpdateRomSelection(const CEngineModel *engine) {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == McuType());
    Q_ASSERT(mMcuController != 0);

    if (IsAutomaticExecution(engine)) {
        mRomTableView->selectRow(engine->CurrentMcu()->RomAddress());
    }
}

bool CMcuWidget::IsAutomaticExecution(const CEngineModel *engine) const {
    Q_ASSERT(engine != 0);
    Q_ASSERT(engine->CurrentMcuType() == McuType());
    Q_ASSERT(mMcuController != 0);

    return engine->IsExecutionMode()
           && (   (McuType() == CEngineModel::MILI_MCU)
               || (McuType() == CEngineModel::MOORE_MCU))
            ;
}

void CMcuWidget::ConnectSignalsToRomTable() {
    connect(mRomTableView->selectionModel(),
            SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)),
            this,
            SLOT(UpdateCurrentRomAddressSlot(const QModelIndex&, const QModelIndex&)));

    connect(mRomTableView->model(),
            SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
            this,
            SLOT(UpdateCurrentRomAddressSlot(const QModelIndex&, const QModelIndex&)));
}

void CMcuWidget::UpdateCurrentRomAddressSlot(const QModelIndex &currIndex, const QModelIndex &/*prevIndex*/) {
    if (currIndex.isValid() && !IsAutomaticExecution(mEngineController.Engine())) {
        unsigned int address = (unsigned int)currIndex.row();
        mEngineController.SetMcuRomAddress(address);
    }
}

