#ifndef CMOORETWOSTATESELECT_H
#define CMOORETWOSTATESELECT_H

#include <QWidget>
#include "cmcu.h"


namespace Ui {
class CMooreTwoStateSelect;
}

class CEngineModel;
class CMooreTwoStateSelect;

class CMoore2McuController : public CMcuController {
public:
    CMoore2McuController(CMooreTwoStateSelect *view):CMcuController() {mView = view;}

protected:
    virtual void DoUpdateLogicView(const CEngineModel* engine);
    virtual void DoUpdateMemoryView(const CEngineModel* engine);
    virtual void DoUpdateHintsView(const CEngineModel* engine);

private:
    CMooreTwoStateSelect *mView;
};


class CMooreTwoStateSelect : public QWidget
{
    Q_OBJECT
    
public:
    explicit CMooreTwoStateSelect(QWidget *parent = 0);
    ~CMooreTwoStateSelect();
    
    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHintsView(const CEngineModel* engine);

    CMcuController *McuController() {return &mMcuController;}

private:
    Ui::CMooreTwoStateSelect *ui;
    CMoore2McuController     mMcuController;

    void UpdateRG(const CEngineModel* engine);

    void UpdateMS1(const CEngineModel* engine);
    void UpdateMS2(const CEngineModel* engine);

    void UpdateY(const CEngineModel* engine);
};

#endif // CMOORETWOSTATESELECT_H
