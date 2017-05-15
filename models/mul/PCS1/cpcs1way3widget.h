#ifndef CPCS1WAY3WIDGET_H
#define CPCS1WAY3WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CPcs1Way3Widget;
}


class QLabel;
class CPcs1Way3Widget;


class CPcs1Way3EngineController : public CEngineController {
public:
    CPcs1Way3EngineController(CPcs1Way3Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CPcs1Way3Widget *mView;
};


class CPcs1Way3Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CPcs1Way3Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CPcs1Way3Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CPcs1Way3Widget *ui;

    CPcs1Way3EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CPCS1WAY3WIDGET_H
