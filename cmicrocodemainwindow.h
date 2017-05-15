#ifndef CMICROCODEMAINWINDOW_H
#define CMICROCODEMAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "cenginefactory.h"


namespace Ui {
class CMicrocodeMainWindow;
}


class CMicrocodeMainWindow;
class QGridLayout;
class QMenu;

class CEngineShifter : public QObject {
    Q_OBJECT

public:
    CEngineShifter(unsigned int engineIndex,
                   CMicrocodeMainWindow *window,
                   QObject *parent);

private:
    CMicrocodeMainWindow *mView;
    unsigned int mEngineIndex;

public slots:
    void Shift();
};


class CMicrocodeMainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    enum TState {READY_STATE, STUDY_STATE};

    explicit CMicrocodeMainWindow(QWidget *parent = 0);
    ~CMicrocodeMainWindow();
    
    void ShiftToEngine(unsigned int index);

private:
    Ui::CMicrocodeMainWindow *ui;

    TState                  mState;
    CEngineModel           *mCurrentEngine;
    QVector<CEngineMvcItem> mEngineMvcItems;

    QMenu                  *mTaskMenu;
    QMenu                  *mTaskLoaderMenu;
    QMenu                  *mActionsMenu;
    QMenu                  *mActionsModeMenu;
    QMenu                  *mActionsMcuMenu;

    QAction                *mOpenWorkAction;
    QAction                *mPc2DcLoadAction;
    QAction                *mPcs1LoadAction;
    QAction                *mDcmcLoadAction;
    QAction                *mDcacLoadAction;
    QAction                *mFzusLoadAction;
    QAction                *mFaddLoadAction;
    QAction                *mQuitAction;

    QAction                *mProgrammingModeAction;
    QAction                *mDebugModeAction;
    QAction                *mAutotestModeAction;

    QAction                *mManualControlAction;
    QAction                *mMiliControlAction;
    QAction                *mMooreControlAction;

    QAction                *mStopCpuAction;
    QAction                *mExecuteAction;
    QAction                *mPrevAction;
    QAction                *mNextAction;

    QAction                *mAboutAction;
    QAction                *mEnLanguageAction;
    QAction                *mRuLanguageAction;

    void SetState(TState state) {mState = state;}

    void InitRNG();

    void CreateInitialActions();
    void CreateInitialMenuBar();
    void CreateInitialToolBar();

    void CreateFileActions();
    void CreateActionActions();
    void CreateHelpActions();

    void UpdateActions();
    void UpdateFileActions();
    void UpdateTaskActions();
    void UpdateActionActions();

    void CreateEngineLayout();
    void CreateActionsForEngines();

    void HideAllEngineViews();

    static QGridLayout *CreateGridLayout();

    void CreateOpenWorkAction();
    void CreatePc2DcLoadAction();
    void CreatePcs1LoadAction();
    void CreateDcmcLoadAction();
    void CreateDcacLoadAction();
    void CreateFzusLoadAction();
    void CreateFaddLoadAction();
    void CreateQuitAction();

    void CreateProgrammingModeAction();
    void CreateDebugModeAction();
    void CreateAutotestModeAction();

    void CreateManualControlAction();
    void CreateMiliControlAction();
    void CreateMooreControlAction();

    void CreateStopCpuAction();
    void CreateExecuteAction();
    void CreatePrevAction();
    void CreateNextAction();

    void CreateAboutAction();
    void CreateEnLanguageAction();
    void CreateRuLanguageAction();

    QMenu *CreateFileMenu();
    QMenu *CreateTaskMenu();
    QMenu *CreateActionsMenu();
    QMenu *CreateTaskLoaderMenu();
    QMenu *CreateHelpMenu();

    void HandleSuccessfulTesting();
    void HandleExecutionError();
    void HandleFailedTest();
    void HandleUserBreak();

    QString ErrorDescriptionStringForTest(unsigned i) const;

    void IntegrateMvc();
protected:
    virtual void closeEvent(QCloseEvent *event);

signals:
public slots:
    void OpenWorkSlot();
    void LoadPc2DcSlot();
    void LoadPcs1Slot();
    void LoadDcmcSlot();
    void LoadDcacSlot();
    void LoadFzusSlot();
    void LoadFaddSlot();
    void QuitSlot();

    void ProgrammingModeSlot();
    void DebugModeSlot();
    void AutotestModeSlot();

    void ManualControlSlot();
    void MiliControlSlot();
    void MooreControlSlot();

    void StopCpuSlot();
    void ExecuteSlot();
    void PrevSlot();
    void NextSlot();

    void AboutSlot();
    void EnLanguageSlot();
    void RuLanguageSlot();
};

#endif // CMICROCODEMAINWINDOW_H
