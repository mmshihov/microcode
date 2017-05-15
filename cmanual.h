#ifndef CMANUAL_H
#define CMANUAL_H

#include <QWidget>
#include "cmcu.h"

namespace Ui {
class CManual;
}

class CEngineModel;
class CManual;

class CManualMcuController : public CMcuController {
public:
    CManualMcuController(CManual *view):CMcuController() {mView = view;}

protected:
    virtual void DoUpdateLogicView(const CEngineModel* engine);
    virtual void DoUpdateMemoryView(const CEngineModel* engine);
    virtual void DoUpdateHintsView(const CEngineModel* engine);

private:
    CManual *mView;
};

class CManual : public QWidget {
    Q_OBJECT
    
public:
    explicit CManual(QWidget *parent = 0);
    ~CManual();

    CMcuController *McuController() {return &mMcuController;}

    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHintsView(const CEngineModel* engine);

private:
    Ui::CManual          *ui;
    CManualMcuController  mMcuController;

    void UpdateRG(const CEngineModel* engine);
    void UpdateY(const CEngineModel* engine);
};

#endif // CMANUAL_H
