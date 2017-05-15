#ifndef CPCS1WAY4WIDGET_H
#define CPCS1WAY4WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CPcs1Way4Widget;
}

class QLabel;
class CPcs1Way4Widget;

class CPcs1Way4EngineController : public CEngineController {
public:
    CPcs1Way4EngineController(CPcs1Way4Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CPcs1Way4Widget *mView;
};

class CPcs1Way4Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CPcs1Way4Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CPcs1Way4Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CPcs1Way4Widget *ui;

    CPcs1Way4EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CPCS1WAY4WIDGET_H
