#ifndef CDCACWAY4WIDGET_H
#define CDCACWAY4WIDGET_H

#include <QWidget>

#include "../../../cengine.h"

namespace Ui {
class CDcacWay4Widget;
}


class QLabel;
class CDcacWay4Widget;


class CDcacWay4EngineController : public CEngineController {
public:
    CDcacWay4EngineController(CDcacWay4Widget *view) : CEngineController() {mView = view;}

protected:
    virtual void DoUpdateMemoryView();
    virtual void DoUpdateLogicView();
    virtual void DoUpdateHintsView();
    virtual void DoUpdateModeView() {}
    virtual void DoUpdateMcuTypeView() {}

private:
    CDcacWay4Widget *mView;
};


class CDcacWay4Widget : public QWidget {
    Q_OBJECT
    
public:
    explicit CDcacWay4Widget(CEngineModel* engine, QWidget *parent = 0);
    ~CDcacWay4Widget();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHints(const CEngineModel* engine);

private:
    Ui::CDcacWay4Widget *ui;

    CDcacWay4EngineController mController;

    const CEngineModel *Engine() const {return mController.Engine();}

};

#endif // CDCACWAY4WIDGET_H
