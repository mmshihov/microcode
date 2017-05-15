#ifndef CMOOREFOURSTATESELECT_H
#define CMOOREFOURSTATESELECT_H

#include <QWidget>
#include "cmcu.h"

namespace Ui {
class CMooreFourStateSelect;
}

class CEngineModel;
class CMooreFourStateSelect;

class CMoore4McuController : public CMcuController {
public:
    CMoore4McuController(CMooreFourStateSelect *view):CMcuController() {mView = view;}

protected:
    virtual void DoUpdateLogicView(const CEngineModel* engine);
    virtual void DoUpdateMemoryView(const CEngineModel* engine);
    virtual void DoUpdateHintsView(const CEngineModel* engine);

private:
    CMooreFourStateSelect *mView;
};

class CMooreFourStateSelect : public QWidget {
    Q_OBJECT
    
public:
    explicit CMooreFourStateSelect(QWidget *parent = 0);
    ~CMooreFourStateSelect();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHintsView(const CEngineModel* engine);

    CMcuController *McuController() {return &mMcuController;}

private:
    Ui::CMooreFourStateSelect *ui;
    CMoore4McuController       mMcuController;

    void UpdateRG(const CEngineModel* engine);

    void UpdateMS1(const CEngineModel* engine);
    void UpdateMS2(const CEngineModel* engine);

    void UpdateY(const CEngineModel* engine);
};

#endif // CMOOREFOURSTATESELECT_H
