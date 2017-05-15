#ifndef CDCACWAY1WIDGET_H
#define CDCACWAY1WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcacWay1Widget;
}


class QLabel;
class CDcacWay1Widget;


class CDcacWay1EngineController : public CEngineController {
public:
    CDcacWay1EngineController(CDcacWay1Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcacWay1Widget *mView;
};


class CDcacWay1Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcacWay1Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcacWay1Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcacWay1Widget *ui;

    CDcacWay1EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CDCACWAY1WIDGET_H
