#include "cenginewidget.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSplitter>

void CEngineWidgetEngineController::DoUpdateModeView() {
    mView->UpdateModeView();
}

void CEngineWidgetEngineController::DoUpdateMcuTypeView() {
    mView->UpdateMcuTypeView();
}

void CEngineWidgetEngineController::DoCheckUserBreak() {
    qApp->processEvents();
}


//-----------------------------------------------------------

CEngineWidget::CEngineWidget(CEngineModel *engine,
                             QWidget *alu,
                             QWidget *hints,
                             QWidget *manualMcu,
                             QWidget *miliMcu,
                             QWidget *mooreMcu,
                             QWidget *parent)
    : QWidget(parent)
    , mEngineController(this)
    , mAlu(alu)
    , mHints(hints)
    , mManualMcu(manualMcu)
    , mMiliMcu(miliMcu)
    , mMooreMcu(mooreMcu)
{
    engine->AppendController(&mEngineController);

    CreateUi();

    UpdateModeView();
    UpdateMcuTypeView();
    ShowAlu();
}

void CEngineWidget::UpdateModeView() {
    if (Engine()->CurrentMode() == CEngineModel::AUTO_TEST_MODE) {
        HideAlu();
    } else {
        ShowAlu();
    }
}

void CEngineWidget::UpdateMcuTypeView() {
    ShowMcu(Engine()->CurrentMcuType());
}

void CEngineWidget::CreateUi() {
    QVBoxLayout *mainLayout = CreateVerticalLayout();
    QHBoxLayout *aluMcuLayout = CreateHorizontalLayout();

    QGridLayout *mcuLayout = CreateGridLayout();
    mcuLayout->addWidget(mManualMcu, 0, 0);
    mcuLayout->addWidget(mMiliMcu,   0, 1);
    mcuLayout->addWidget(mMooreMcu,  0, 2);

    HideAllMcus();

    QGridLayout *aluLayout = CreateGridLayout();
    mFakeAlu = new QWidget();
    mFakeAlu->setFixedSize(mAlu->width(), mAlu->height());

    aluLayout->addWidget(mAlu,     0, 0);
    aluLayout->addWidget(mFakeAlu, 0, 1);

    mFakeAlu->hide();

    aluMcuLayout->addLayout(aluLayout);
    aluMcuLayout->addLayout(mcuLayout);

    mainLayout->addLayout(aluMcuLayout);
    mainLayout->addWidget(mHints);

    setLayout(mainLayout);
}

void CEngineWidget::ShowMcu(CEngineModel::TMcuType mcuType) {
    HideAllMcus();

    switch (mcuType) {
    case CEngineModel::MANUAL_MCU:  mManualMcu->show(); break;
    case CEngineModel::MILI_MCU:    mMiliMcu->show();   break;
    case CEngineModel::MOORE_MCU:   mMooreMcu->show();  break;
    default:
        mManualMcu->show();
    }
}

void CEngineWidget::HideAlu() {
    mAlu->hide();
    mFakeAlu->show();
}

void CEngineWidget::ShowAlu() {
    mFakeAlu->hide();
    mAlu->show();
}

QVBoxLayout *CEngineWidget::CreateVerticalLayout() {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    return layout;
}

QHBoxLayout *CEngineWidget::CreateHorizontalLayout() {
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    return layout;
}

QGridLayout *CEngineWidget::CreateGridLayout() {
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0,0,0,0);
    return layout;
}

QSplitter *CEngineWidget::CreateHorizontalSplitter() {
    QSplitter *splitter = new QSplitter();
    splitter->setOrientation(Qt::Horizontal);
    return splitter;
}

void CEngineWidget::HideAllMcus() {
    mManualMcu->hide();
    mMiliMcu->hide();
    mMooreMcu->hide();
}
