#ifndef CFADDWAY1WIDGET_H
#define CFADDWAY1WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CFaddWay1Widget;
}


class QLabel;
class CFaddWay1Widget;


class CFaddWay1EngineController : public CEngineController {
public:
    CFaddWay1EngineController(CFaddWay1Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CFaddWay1Widget *mView;
};


class CFaddWay1Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CFaddWay1Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CFaddWay1Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CFaddWay1Widget *ui;

    CFaddWay1EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CFADDWAY1WIDGET_H
