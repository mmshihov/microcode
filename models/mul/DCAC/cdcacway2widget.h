#ifndef CDCACWAY2WIDGET_H
#define CDCACWAY2WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcacWay2Widget;
}


class QLabel;
class CDcacWay2Widget;


class CDcacWay2EngineController : public CEngineController {
public:
    CDcacWay2EngineController(CDcacWay2Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcacWay2Widget *mView;
};


class CDcacWay2Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcacWay2Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcacWay2Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcacWay2Widget *ui;

    CDcacWay2EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CDCACWAY2WIDGET_H
