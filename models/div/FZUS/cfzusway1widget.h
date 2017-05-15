#ifndef CFZUSWAY1WIDGET_H
#define CFZUSWAY1WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CFzusWay1Widget;
}


class QLabel;
class CFzusWay1Widget;


class CFzusWay1EngineController : public CEngineController {
public:
    CFzusWay1EngineController(CFzusWay1Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CFzusWay1Widget *mView;
};


class CFzusWay1Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CFzusWay1Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CFzusWay1Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CFzusWay1Widget *ui;

    CFzusWay1EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CFZUSWAY1WIDGET_H
