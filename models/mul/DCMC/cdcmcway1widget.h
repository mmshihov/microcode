#ifndef CDCMCWAY1WIDGET_H
#define CDCMCWAY1WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcmcWay1Widget;
}


class QLabel;
class CDcmcWay1Widget;


class CDcmcWay1EngineController : public CEngineController {
public:
    CDcmcWay1EngineController(CDcmcWay1Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcmcWay1Widget *mView;
};

class CDcmcWay1Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcmcWay1Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcmcWay1Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcmcWay1Widget *ui;

    CDcmcWay1EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CDCMCWAY1WIDGET_H
