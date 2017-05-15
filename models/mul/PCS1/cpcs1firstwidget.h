#ifndef CPCS1FIRSTWIDGET_H
#define CPCS1FIRSTWIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CPcs1FirstWidget;
}

class QLabel;
class CPcs1FirstWidget;

class CPcs1FirstEngineController : public CEngineController {
public:
    CPcs1FirstEngineController(CPcs1FirstWidget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CPcs1FirstWidget *mView;
};

class CPcs1FirstWidget : public QWidget {
    Q_OBJECT
    
public:
    explicit CPcs1FirstWidget(CEngineModel* engine, QWidget *parent = 0);
    ~CPcs1FirstWidget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CPcs1FirstWidget *ui;

    CPcs1FirstEngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CPCS1FIRSTWIDGET_H
