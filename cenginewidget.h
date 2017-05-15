#ifndef CENGINEWIDGET_H
#define CENGINEWIDGET_H

#include <QWidget>
#include "cengine.h"

class CEngineWidget;

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class CEngineWidgetEngineController : public CEngineController {
public:
    CEngineWidgetEngineController(CEngineWidget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView() {}
    virtual void DoUpdateLogicView() {}
    virtual void DoUpdateHintsView() {}
    virtual void DoUpdateModeView();
    virtual void DoUpdateMcuTypeView();
    virtual void DoCheckUserBreak();

private:
    CEngineWidget *mView;
};

class CEngineWidget : public QWidget {
    Q_OBJECT
public:
    explicit CEngineWidget(CEngineModel *engine,
                           QWidget *alu,
                           QWidget *hints,
                           QWidget *manualMcu,
                           QWidget *miliMcu,
                           QWidget *mooreMcu,
                           QWidget *parent = 0);
    
    void UpdateModeView();
    void UpdateMcuTypeView();
private:
    CEngineWidgetEngineController mEngineController;

    QWidget *mAlu;
    QWidget *mFakeAlu;
    QWidget *mHints;
    QWidget *mManualMcu;
    QWidget *mMiliMcu;
    QWidget *mMooreMcu;

    void ShowAlu();
    void HideAlu();

    void ShowMcu(CEngineModel::TMcuType mcuType);

    const CEngineModel *Engine() const {return mEngineController.Engine();}

    void CreateUi();

    static QVBoxLayout *CreateVerticalLayout();
    static QHBoxLayout *CreateHorizontalLayout();
    static QGridLayout *CreateGridLayout();

    void HideAllMcus();
signals:
    
public slots:

};

#endif // CENGINEWIDGET_H
