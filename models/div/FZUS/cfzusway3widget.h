#ifndef CFZUSWAY3WIDGET_H
#define CFZUSWAY3WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CFzusWay3Widget;
}


class QLabel;
class CFzusWay3Widget;


class CFzusWay3EngineController : public CEngineController {
public:
    CFzusWay3EngineController(CFzusWay3Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CFzusWay3Widget *mView;
};


class CFzusWay3Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CFzusWay3Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CFzusWay3Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CFzusWay3Widget *ui;

    CFzusWay3EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CFZUSWAY3WIDGET_H
