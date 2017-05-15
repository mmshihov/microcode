#ifndef CPCS1WAY2WIDGET_H
#define CPCS1WAY2WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CPcs1Way2Widget;
}

class QLabel;
class CPcs1Way2Widget;


class CPcs1Way2EngineController : public CEngineController {
public:
    CPcs1Way2EngineController(CPcs1Way2Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CPcs1Way2Widget *mView;
};

class CPcs1Way2Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CPcs1Way2Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CPcs1Way2Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CPcs1Way2Widget *ui;

    CPcs1Way2EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CPCS1WAY2WIDGET_H
