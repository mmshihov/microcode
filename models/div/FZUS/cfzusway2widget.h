#ifndef CFZUSWAY2WIDGET_H
#define CFZUSWAY2WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CFzusWay2Widget;
}


class QLabel;
class CFzusWay2Widget;


class CFzusWay2EngineController : public CEngineController {
public:
    CFzusWay2EngineController(CFzusWay2Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CFzusWay2Widget *mView;
};


class CFzusWay2Widget : public QWidget {
    Q_OBJECT

public:
    explicit CFzusWay2Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CFzusWay2Widget();

    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CFzusWay2Widget *ui;

    CFzusWay2EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CFZUSWAY2WIDGET_H
