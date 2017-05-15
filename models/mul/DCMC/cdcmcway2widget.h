#ifndef CDCMCWAY2WIDGET_H
#define CDCMCWAY2WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcmcWay2Widget;
}


class QLabel;
class CDcmcWay2Widget;


class CDcmcWay2EngineController : public CEngineController {
public:
    CDcmcWay2EngineController(CDcmcWay2Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcmcWay2Widget *mView;
};


class CDcmcWay2Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcmcWay2Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcmcWay2Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcmcWay2Widget *ui;

    CDcmcWay2EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CDCMCWAY2WIDGET_H
