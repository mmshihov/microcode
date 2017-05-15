#ifndef CDCMCWAY4WIDGET_H
#define CDCMCWAY4WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcmcWay4Widget;
}


class QLabel;
class CDcmcWay4Widget;


class CDcmcWay4EngineController : public CEngineController {
public:
    CDcmcWay4EngineController(CDcmcWay4Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcmcWay4Widget *mView;
};


class CDcmcWay4Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcmcWay4Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcmcWay4Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcmcWay4Widget *ui;

    CDcmcWay4EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}
};

#endif // CDCMCWAY4WIDGET_H
