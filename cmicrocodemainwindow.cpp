#include "cmicrocodemainwindow.h"
#include "ui_cmicrocodemainwindow.h"

#include <QGridLayout>

#include <QMessageBox>
#include <QFileDialog>

#include <QSettings>

#include <QCloseEvent>

#include "cengine.h"
#include "ccpu.h"
#include "cromtablemodel.h"
#include "cromeditordelegate.h"
#include "cindividualtask.h"
#include "cindividualtaskcreationdialog.h"
#include "ccheckindividualtaskdialog.h"
#include "ctextout.h"

#include "version_number.h"

#include <stdlib.h>
#include <time.h>


CEngineShifter::CEngineShifter(unsigned int engineIndex,
                               CMicrocodeMainWindow *window,
                               QObject *parent)
    : QObject(parent)
    , mView(window)
    , mEngineIndex(engineIndex) {}

void CEngineShifter::Shift() {
    mView->ShiftToEngine(mEngineIndex);
}


CMicrocodeMainWindow::CMicrocodeMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMicrocodeMainWindow)
{
    ui->setupUi(this);

    InitRNG();

    mCurrentEngine = 0;
    SetState(READY_STATE);

    CreateInitialActions();

    CreateInitialMenuBar();
    CreateInitialToolBar();

    UpdateActions();
    UpdateWindowTitle();
}

CMicrocodeMainWindow::~CMicrocodeMainWindow() {
    delete ui;
}

void CMicrocodeMainWindow::ShiftToEngine(unsigned int index) {
    if (mCurrentEngine != 0 && mCurrentEngine->IsProgramExecution()) {
        if (QMessageBox::question(
                        this,
                        tr("Are you sure?"),
                        tr("Your program is executing now!\n"
                           "Do you want to break it, and switch to another task?"
                           ),
                        QMessageBox::Yes | QMessageBox::No
                    ) == QMessageBox::No) {
            return;
        } else {
            mCurrentEngine->SetExternalBreakRequest();
            return;
        }
    }

    HideAllEngineViews();
    mCurrentEngine = 0;
    if ((int)index < mEngineMvcItems.count()) {
        mEngineMvcItems[index].EngineView()->show();

        mCurrentEngineIndex = index;
        mCurrentEngine = mEngineMvcItems[mCurrentEngineIndex].EngineModel();

        mCurrentEngine->UpdateModeViews();
        mCurrentEngine->UpdateMcuTypeViews();

        mCurrentEngine->UpdateMemoryViews();
        mCurrentEngine->UpdateLogicViews();

        UpdateActions();
        UpdateWindowTitle();
    }
}

void CMicrocodeMainWindow::InitRNG() {
    srand(time(0));
}

void CMicrocodeMainWindow::CreateInitialActions() {
    CreateFileActions();
    CreateActionActions();
    CreateHelpActions();
}

void CMicrocodeMainWindow::CreateInitialMenuBar() {
    menuBar()->addMenu(CreateFileMenu());
    menuBar()->addMenu(CreateTaskMenu());
    menuBar()->addMenu(CreateActionsMenu());
    menuBar()->addMenu(CreateHelpMenu());
}

void CMicrocodeMainWindow::CreateInitialToolBar() {
    ui->mainToolBar->addAction(mOpenVariantAction);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(mExecuteAction);
    ui->mainToolBar->addAction(mStopCpuAction);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(mPrevAction);
    ui->mainToolBar->addAction(mNextAction);
}

void CMicrocodeMainWindow::CreateFileActions() {
    CreateOpenVariantAction();
    CreateCheckVariantAction();
    CreateCreateVariantsAction();

    CreatePc2DcLoadAction();
    CreatePcs1LoadAction();
    CreateDcmcLoadAction();
    CreateDcacLoadAction();
    CreateFzusLoadAction();
    CreateFaddLoadAction();

    CreateQuitAction();
}

void CMicrocodeMainWindow::CreateActionActions() {
    CreateProgrammingModeAction();
    CreateDebugModeAction();
    CreateAutotestModeAction();

    CreateManualControlAction();
    CreateMiliControlAction();
    CreateMooreControlAction();

    CreateStopCpuAction();
    CreateExecuteAction();

    CreateNextAction();
    CreatePrevAction();
}

void CMicrocodeMainWindow::CreateHelpActions() {
    CreateAboutAction();
    CreateRuLanguageAction();
    CreateEnLanguageAction();
}

void CMicrocodeMainWindow::UpdateActions() {
    UpdateFileActions();
    UpdateTaskActions();
    UpdateActionActions();
}

void CMicrocodeMainWindow::UpdateFileActions() {
    bool isEngineAndExecution =  (mCurrentEngine != 0) &&  mCurrentEngine->IsExecutionMode();

    mOpenVariantAction->setEnabled(!isEngineAndExecution);

    mCheckVariantAction->setEnabled(CIndividualTask::Instance()->IsLoaded());
    mTaskLoaderMenu->setEnabled(mCurrentEngine == 0);
}

void CMicrocodeMainWindow::UpdateTaskActions() {
    bool isEnabled = (mCurrentEngine != 0)
                  && (mCurrentEngine->CurrentMode() != CEngineModel::AUTO_TEST_MODE);
    mTaskMenu->setEnabled(isEnabled);
}

void CMicrocodeMainWindow::UpdateActionActions() {
    bool isEngine = (mCurrentEngine != 0);
    bool isEngineAndExecution =  (mCurrentEngine != 0) &&  mCurrentEngine->IsExecutionMode();
    bool isEngineAndProgramming =  (mCurrentEngine != 0) && mCurrentEngine->IsProgrammingMode();
    bool isEngineAndStepByStepExecution =  (mCurrentEngine != 0)
                                        &&  mCurrentEngine->IsExecutionMode()
                                        && !mCurrentEngine->IsProgramExecution();

    mActionsMenu->setEnabled(isEngine);

    mActionsModeMenu->setEnabled(isEngineAndProgramming);
    mProgrammingModeAction->setEnabled(isEngineAndProgramming);
    mDebugModeAction->setEnabled(isEngineAndProgramming);
    mAutotestModeAction->setEnabled(isEngineAndProgramming);

    mActionsMcuMenu->setEnabled(isEngineAndProgramming);
    mManualControlAction->setEnabled(isEngineAndProgramming);
    mMiliControlAction->setEnabled(isEngineAndProgramming);
    mMooreControlAction->setEnabled(isEngineAndProgramming);

    mStopCpuAction->setEnabled(isEngineAndExecution);
    mExecuteAction->setEnabled(isEngineAndStepByStepExecution);

    mPrevAction->setEnabled((mCurrentEngine != 0) && (mCurrentEngine->IsPastTicks()));
    mNextAction->setEnabled((mCurrentEngine != 0) && (mCurrentEngine->IsFutureTicks()));
}

void CMicrocodeMainWindow::CreateEngineLayout() {
    QGridLayout *layout = CreateGridLayout();
    for (int i=0; i<mEngineMvcItems.count(); ++i) {
        layout->addWidget(mEngineMvcItems[i].EngineView(), 0, i);
    }

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    HideAllEngineViews();

    setCentralWidget(widget);
}

void CMicrocodeMainWindow::CreateActionsForEngines() {
    for (int i=0; i<mEngineMvcItems.count(); ++i) {
        QAction *shiftAction = new QAction(mEngineMvcItems[i].Name(), this);
        connect(shiftAction,
                SIGNAL(triggered()),
                new CEngineShifter(i, this, this),
                SLOT(Shift()));

        mTaskMenu->addAction(shiftAction);
    }
}

void CMicrocodeMainWindow::HideAllEngineViews() {
    for (int i=0; i<mEngineMvcItems.count(); ++i)
        mEngineMvcItems[i].EngineView()->hide();
}

QGridLayout *CMicrocodeMainWindow::CreateGridLayout() {
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0,0,0,0);
    return layout;
}

void CMicrocodeMainWindow::CreateOpenVariantAction() {
    QAction *action = new QAction(QIcon(":/common/open.png"), tr("&Open individual variant..."), this);
    action->setShortcut(QKeySequence::Open);
    QString text(tr("Load individual variant from file..."));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(OpenVariantSlot()));

    mOpenVariantAction = action;
}

void CMicrocodeMainWindow::CreateCheckVariantAction() {
    QAction *action = new QAction(QIcon(":/common/check.png"), tr("&Check individual variant..."), this);
    QString text(tr("Check individual vatiant..."));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(CheckVariantSlot()));

    mCheckVariantAction = action;
}

void CMicrocodeMainWindow::CreateCreateVariantsAction() {
    QAction *action = new QAction(QIcon(":/common/save.png"), tr("C&reate individual variants..."), this);
    action->setShortcut(QKeySequence::Save);
    QString text(tr("Create individual variants..."));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(CreateVariantsSlot()));

    mCreateVariantsAction = action;
}

void CMicrocodeMainWindow::CreatePc2DcLoadAction() {
    QAction *action = new QAction(tr("Introduction task (feel free)"), this);
    QString text(tr("Transform Direct code into Two's compliment"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(LoadPc2DcSlot()));

    mPc2DcLoadAction = action;
}

void CMicrocodeMainWindow::CreatePcs1LoadAction() {
    QAction *action = new QAction(tr("Direct code multiplication"), this);
    QString text(tr("Learn 4 ways of number multiplication (Direct code)"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(LoadPcs1Slot()));

    mPcs1LoadAction = action;
}

void CMicrocodeMainWindow::CreateDcmcLoadAction() {
    QAction *action = new QAction(tr("Two's compliment multiplication (manual correction)"), this);
    QString text(tr("Learn 4 ways of integer multiplication (Two's compliment, manual correction)"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(LoadDcmcSlot()));

    mDcmcLoadAction = action;
}

void CMicrocodeMainWindow::CreateDcacLoadAction() {
    QAction *action = new QAction(tr("Two's compliment multiplication (autocorrection)"), this);
    QString text(tr("Learn 4 ways of integer multiplication (Two's compliment, manual autocorrection)"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(LoadDcacSlot()));

    mDcacLoadAction = action;
}

void CMicrocodeMainWindow::CreateFzusLoadAction() {
    QAction *action = new QAction(tr("Unsigned division A:B = q rem r"), this);
    QString text(tr("Learn 2 ways of unsigned integer division"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(LoadFzusSlot()));

    mFzusLoadAction = action;
}

void CMicrocodeMainWindow::CreateFaddLoadAction() {
    QAction *action = new QAction(tr("Floating point: addition"), this);
    QString text(tr("Learn addition in floating point format"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(LoadFaddSlot()));

    mFaddLoadAction = action;
}

void CMicrocodeMainWindow::CreateQuitAction() {
    QAction *action = new QAction(tr("&Exit"), this);
    action->setShortcut(QKeySequence::Quit);
    QString text(tr("Exit program"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(QuitSlot()));

    mQuitAction = action;
}

void CMicrocodeMainWindow::CreateProgrammingModeAction() {
    QAction *action = new QAction(QIcon(":/common/programming.png"), tr("&Programming"), this);
    QString text(tr("Stop debug/autotest and start programming"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(ProgrammingModeSlot()));

    mProgrammingModeAction = action;
}

void CMicrocodeMainWindow::CreateDebugModeAction() {
    QAction *action = new QAction(QIcon(":/common/debug.png"), tr("&Debug"), this);
    QString text(tr("Run CPU and start debugging"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(DebugModeSlot()));

    mDebugModeAction = action;
}

void CMicrocodeMainWindow::CreateAutotestModeAction() {
    QAction *action = new QAction(QIcon(":/common/autotest.png"), tr("&Autotest"), this);
    QString text(tr("Run CPU and start autotests"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(AutotestModeSlot()));

    mAutotestModeAction = action;
}

void CMicrocodeMainWindow::CreateManualControlAction() {
    QAction *action = new QAction(tr("M&anual"), this);
    QString text(tr("Manual control"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(ManualControlSlot()));

    mManualControlAction = action;
}

void CMicrocodeMainWindow::CreateMiliControlAction() {
    QAction *action = new QAction(tr("M&ili"), this);
    QString text(tr("Select Mili automate as MCU"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(MiliControlSlot()));

    mMiliControlAction = action;
}

void CMicrocodeMainWindow::CreateMooreControlAction() {
    QAction *action = new QAction(tr("M&oore"), this);
    QString text(tr("Select Moore automate as MCU"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(MooreControlSlot()));

    mMooreControlAction = action;
}

void CMicrocodeMainWindow::CreateStopCpuAction() {
    QAction *action = new QAction(QIcon(":/common/break.png"), tr("&Stop CPU"), this);
    action->setShortcut(QKeySequence(tr("F2")));
    QString text(tr("Stop (F2) CPU, break debug/autotest and start programming"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(StopCpuSlot()));

    mStopCpuAction = action;
}

void CMicrocodeMainWindow::CreateExecuteAction() {
    QAction *action = new QAction(QIcon(":/common/execute.png"), tr("&Execute"), this);
    action->setShortcut(QKeySequence("F10"));
    QString text(tr("Execute (F10) debug step or autotests"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(ExecuteSlot()));

    mExecuteAction = action;
}

void CMicrocodeMainWindow::CreatePrevAction() {
    QAction *action = new QAction(QIcon(":/common/prev.png"), tr("Undo action"), this);
    QString text(tr("To previous step"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(PrevSlot()));

    mPrevAction = action;
}

void CMicrocodeMainWindow::CreateNextAction() {
    QAction *action = new QAction(QIcon(":/common/next.png"), tr("Redo action"), this);
    QString text(tr("To next step"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(NextSlot()));

    mNextAction = action;
}

void CMicrocodeMainWindow::CreateAboutAction() {
    QAction *action = new QAction(tr("&About program..."), this);
    QString text(tr("Show program info"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(AboutSlot()));

    mAboutAction = action;
}

void CMicrocodeMainWindow::CreateEnLanguageAction() {
    QAction *action = new QAction(tr("&English"), this);
    QString text(tr("Switch laguage to English"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(EnLanguageSlot()));

    mEnLanguageAction = action;
}

void CMicrocodeMainWindow::CreateRuLanguageAction() {
    QAction *action = new QAction(tr("&Русский"), this);
    QString text(tr("Переключить язык на Русский"));
    action->setToolTip(text);
    action->setStatusTip(text);
    connect(action, SIGNAL(triggered()), SLOT(RuLanguageSlot()));

    mRuLanguageAction = action;
}

QMenu *CMicrocodeMainWindow::CreateFileMenu() {
    QMenu *menu = new QMenu(tr("&File"));

    menu->addAction(mOpenVariantAction);
    menu->addSeparator();
    menu->addAction(mCheckVariantAction);
    menu->addAction(mCreateVariantsAction);
    menu->addSeparator();
    menu->addMenu(CreateTaskLoaderMenu());
    menu->addSeparator();
    menu->addAction(mQuitAction);

    return menu;
}

QMenu *CMicrocodeMainWindow::CreateTaskMenu() {
    QMenu *menu = new QMenu(tr("&Tasks"));
    return mTaskMenu = menu;
}

QMenu *CMicrocodeMainWindow::CreateActionsMenu() {
    QMenu *menu = new QMenu(tr("&Actions"));

    mActionsModeMenu = new QMenu(tr("&Mode"));
    mActionsModeMenu->addAction(mProgrammingModeAction);
    mActionsModeMenu->addAction(mDebugModeAction);
    mActionsModeMenu->addAction(mAutotestModeAction);
    menu->addMenu(mActionsModeMenu);

    menu->addSeparator();
    mActionsMcuMenu = new QMenu(tr("M&CU"));
    mActionsMcuMenu->addAction(mManualControlAction);
    mActionsMcuMenu->addAction(mMiliControlAction);
    mActionsMcuMenu->addAction(mMooreControlAction);
    menu->addMenu(mActionsMcuMenu);

    menu->addSeparator();
    menu->addAction(mExecuteAction);
    menu->addAction(mStopCpuAction);

    menu->addSeparator();
    menu->addAction(mPrevAction);
    menu->addAction(mNextAction);

    return mActionsMenu = menu;
}

QMenu *CMicrocodeMainWindow::CreateTaskLoaderMenu() {
    QMenu *menu = new QMenu(tr("&Load Tasks"));

    menu->addAction(mPc2DcLoadAction);
    menu->addSeparator();

    menu->addAction(mPcs1LoadAction);
    menu->addAction(mDcmcLoadAction);
    menu->addAction(mDcacLoadAction);
    menu->addSeparator();

    menu->addAction(mFzusLoadAction);
    menu->addSeparator();

    menu->addAction(mFaddLoadAction);

    return mTaskLoaderMenu = menu;
}

QMenu *CMicrocodeMainWindow::CreateHelpMenu() {
    QMenu *menu = new QMenu(tr("&Help"));

    menu->addAction(mAboutAction);
    menu->addSeparator();
    menu->addAction(mRuLanguageAction);
    menu->addAction(mEnLanguageAction);

    return menu;
}

void CMicrocodeMainWindow::HandleSuccessfulTesting() {
    switch (mCurrentEngine->CurrentMode()) {
    case CEngineModel::DEBUG_MODE:
        QMessageBox::information(
                    this,
                    tr("DEBUG congratulations!"),
                    tr("DEBUG test successfully passed!\n\n"
                       "P.S. Now you in 'Programming' mode."));
        break;
    case CEngineModel::AUTO_TEST_MODE:
    default:
        QMessageBox::information(
                    this,
                    tr("AUTOTESTS congratulations!"),
                    tr("All AUTOTESTS successfully passed!\n\n"
                       "P.S. Now you in 'Programming' mode."));
    }
}

void CMicrocodeMainWindow::HandleExecutionError() {
    CTextOut::ShowErrorMessage(this, mCurrentEngine->ErrorState());
}

void CMicrocodeMainWindow::HandleFailedTest() {
    const CCpu *cpu = mCurrentEngine->CurrentCpu();

    for (unsigned int i=0; i<cpu->TestCount(); ++i) {
        if (!cpu->IsTestOK(i)) {
            QMessageBox::warning(
                        this,
                        tr("Autotest failed!"),
                        ErrorDescriptionStringForTest(i));
            return;
        }
    }
}

void CMicrocodeMainWindow::HandleUserBreak() {
    QMessageBox::information(
                this,
                tr("User break"),
                tr("Engine execution breaked by user\n\n"
                   "P.S. Now you in 'Programming' mode."));
}

QString CMicrocodeMainWindow::ErrorDescriptionStringForTest(unsigned testIndex) const {
    SharedPtr<CTestVector> vector = mCurrentEngine->CurrentCpu()->TestVector();

    QString inputString(tr("The INPUT:"));
    inputString += QString("(%1").arg(CTextOut::FormatBin(vector->InputPart(testIndex, 0)));
    for (unsigned int i = 1; i<vector->InputPartCount(); ++i) {
        inputString += QString(",%1").arg(CTextOut::FormatBin(vector->InputPart(testIndex, i)));
    }
    inputString += ")\n";

    QString rightOutputString(tr("Right OUTPUT:"));
    rightOutputString += QString("(%1").arg(CTextOut::FormatBin(vector->RightOutputPart(testIndex, 0)));
    for (unsigned int i = 1; i<vector->InputPartCount(); ++i) {
        rightOutputString += QString(",%1").arg(CTextOut::FormatBin(vector->RightOutputPart(testIndex, i)));
    }
    rightOutputString += ")\n";

    QString yourOutputString(tr("Your OUTPUT:"));
    yourOutputString += QString("(%1").arg(CTextOut::FormatBin(vector->OutputPart(testIndex, 0)));
    for (unsigned int i = 1; i<vector->InputPartCount(); ++i) {
        yourOutputString += QString(",%1").arg(CTextOut::FormatBin(vector->OutputPart(testIndex, i)));
    }
    yourOutputString += ")\n";

    return QString("%1%2%3").arg(inputString).arg(rightOutputString).arg(yourOutputString);
}

void CMicrocodeMainWindow::IntegrateMvc() {
    CreateEngineLayout();
    CreateActionsForEngines();

    IndividualiseTasks();
    ShiftToEngine(0);

    UpdateActions();
}

void CMicrocodeMainWindow::IndividualiseTasks() {
    if (!CIndividualTask::Instance()->IsLoaded())
        return;

    for (int i=0; i<mEngineMvcItems.count(); ++i) {
        CIndividualTask::Instance()->InitSignalPermutation(
                mEngineMvcItems[i].EngineModel()->McuOutputSwap());
        mEngineMvcItems[i].EngineModel()->UpdateHintsViews();
    }
}

void CMicrocodeMainWindow::UpdateWindowTitle() {
    if ((mCurrentEngine == 0) || ((int)mCurrentEngineIndex >= mEngineMvcItems.count())) {
        if (CIndividualTask::Instance()->IsLoaded()) {
            setWindowTitle(QString("Microcode " MICROCODE_VERSION " --- %1")
                    .arg(CIndividualTask::Instance()->StudentId())
                    );
        } else {
            setWindowTitle("Microcode " MICROCODE_VERSION);
        }
        return;
    }

    setWindowTitle(QString("Microcode " MICROCODE_VERSION " (%1) --- %2")
                       .arg(mEngineMvcItems[mCurrentEngineIndex].Name())
                       .arg(CIndividualTask::Instance()->StudentId())
                       );
}

void CMicrocodeMainWindow::closeEvent(QCloseEvent *event) {
    event->ignore();
    if (QMessageBox::question(
                this,
                tr("Are you sure?"),
                tr("You loose all microcode after exit!\n"
                   "We not save it, because is MICROcode.\n"
                   "Are you wrote your microcode down on paper?"
                   ),
                QMessageBox::Yes | QMessageBox::No)
            == QMessageBox::Yes) {
        event->accept();
    }
}

void CMicrocodeMainWindow::OpenVariantSlot() {
    QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Open individual variant JSON file"),
                    QString(),
                    tr("JSON individual variant (*.json);;JSON individual variant in text (*.txt)"));
    if (fileName.isNull())
        return;

    CIndividualTask::Instance()->LoadFromFile(fileName);

    if (!CIndividualTask::Instance()->IsLoaded()) {
        QMessageBox::warning(this, tr("Error of variant loading!"), tr("Check your variant file, please!"));
        return;
    }

    UpdateActions();
    UpdateWindowTitle();

    IndividualiseTasks();
}

void CMicrocodeMainWindow::CheckVariantSlot() {
    if (mCheckTaskDialog.isEmpty())
        mCheckTaskDialog = SharedPtr<CCheckIndividualTaskDialog>(new CCheckIndividualTaskDialog());

    mCheckTaskDialog->exec();
}

void CMicrocodeMainWindow::CreateVariantsSlot() {
    if (mCreateTasksDialog.isEmpty())
        mCreateTasksDialog = SharedPtr<CIndividualTaskCreationDialog>(new CIndividualTaskCreationDialog());

    mCreateTasksDialog->exec();
}

void CMicrocodeMainWindow::LoadPc2DcSlot() {
    mEngineMvcItems.append(CEngineFactory::Pc2Dc_Way1());
    IntegrateMvc();
}

void CMicrocodeMainWindow::LoadPcs1Slot() {
    mEngineMvcItems.append(CEngineFactory::Pcs1_Way1());
    mEngineMvcItems.append(CEngineFactory::Pcs1_Way2());
    mEngineMvcItems.append(CEngineFactory::Pcs1_Way3());
    mEngineMvcItems.append(CEngineFactory::Pcs1_Way4());
    IntegrateMvc();
}

void CMicrocodeMainWindow::LoadDcmcSlot() {
    mEngineMvcItems.append(CEngineFactory::Dcmc_Way1());
    mEngineMvcItems.append(CEngineFactory::Dcmc_Way2());
    mEngineMvcItems.append(CEngineFactory::Dcmc_Way3());
    mEngineMvcItems.append(CEngineFactory::Dcmc_Way4());
    IntegrateMvc();
}

void CMicrocodeMainWindow::LoadDcacSlot() {
    mEngineMvcItems.append(CEngineFactory::Dcac_Way1());
    mEngineMvcItems.append(CEngineFactory::Dcac_Way2());
    mEngineMvcItems.append(CEngineFactory::Dcac_Way3());
    mEngineMvcItems.append(CEngineFactory::Dcac_Way4());
    IntegrateMvc();
}

void CMicrocodeMainWindow::LoadFzusSlot() {
    mEngineMvcItems.append(CEngineFactory::Fzus_Way2());
    mEngineMvcItems.append(CEngineFactory::Fzus_Way3());
    mEngineMvcItems.append(CEngineFactory::Fzus_Way1());
    IntegrateMvc();
}

void CMicrocodeMainWindow::LoadFaddSlot() {
    mEngineMvcItems.append(CEngineFactory::Fadd_Way1());
    IntegrateMvc();
}

void CMicrocodeMainWindow::QuitSlot() {close();}

void CMicrocodeMainWindow::ProgrammingModeSlot() {
    mCurrentEngine->SetCurrentMode(CEngineModel::PROGRAMMING_MODE);
    UpdateActions();
}

void CMicrocodeMainWindow::DebugModeSlot() {
    mCurrentEngine->SetCurrentMode(CEngineModel::DEBUG_MODE);
    UpdateActions();
}

void CMicrocodeMainWindow::AutotestModeSlot() {
    mCurrentEngine->SetCurrentMode(CEngineModel::AUTO_TEST_MODE);
    UpdateActions();
}

void CMicrocodeMainWindow::ManualControlSlot() {
    mCurrentEngine->SetCurrentMcuType(CEngineModel::MANUAL_MCU);
}

void CMicrocodeMainWindow::MiliControlSlot() {
    mCurrentEngine->SetCurrentMcuType(CEngineModel::MILI_MCU);
}

void CMicrocodeMainWindow::MooreControlSlot() {
    mCurrentEngine->SetCurrentMcuType(CEngineModel::MOORE_MCU);
}

void CMicrocodeMainWindow::StopCpuSlot() {
    if (mCurrentEngine->IsProgramExecution()) {
        mCurrentEngine->SetExternalBreakRequest();
    } else
        ProgrammingModeSlot();
}

void CMicrocodeMainWindow::ExecuteSlot() {
    Q_ASSERT(!mCurrentEngine->IsCpuInHaltState());

    mCurrentEngine->Execute();

    if (mCurrentEngine->IsCpuInHaltState()) {
        if (mCurrentEngine->IsError()) {
            HandleExecutionError();
        } else if (mCurrentEngine->IsExternalBreak()) {
            HandleUserBreak();
        } else if (mCurrentEngine->CurrentCpu()->IsAllTestsOk()) {
            HandleSuccessfulTesting();
        } else {
            HandleFailedTest();
        }

        ProgrammingModeSlot();
        return;
    }

    UpdateActions();
}

void CMicrocodeMainWindow::PrevSlot() {
    mCurrentEngine->GoPast();
    UpdateActions();
}

void CMicrocodeMainWindow::NextSlot() {
    mCurrentEngine->GoFuture();
    UpdateActions();
}

void CMicrocodeMainWindow::AboutSlot() {
    QMessageBox::information(
                this,
                tr("About"),
                QString("Microcode " MICROCODE_VERSION "\n%1")
                    .arg(tr(
                        " Microprogramming trainer.\n"
                        " First rock in 2016,\n"
                        " author: M.M.Shihov (e-mail: 'm.m.shihov@gmail.com')")));
}

void CMicrocodeMainWindow::EnLanguageSlot() {
    QSettings settings;
    settings.setValue("ui/language", "en_US");
}

void CMicrocodeMainWindow::RuLanguageSlot() {
    QSettings settings;
    settings.setValue("ui/language", "ru_RU");
}
