#ifndef CMILITWOSTATESELECT_H
#define CMILITWOSTATESELECT_H

#include <QWidget>
#include "cmcu.h"

namespace Ui {
class CMiliTwoStateSelect;
}

class CEngineModel;
class CMiliTwoStateSelect;

class CMili2McuController : public CMcuController {
public:
    CMili2McuController(CMiliTwoStateSelect *view):CMcuController() {mView = view;}

protected:
    virtual void DoUpdateLogicView(const CEngineModel* engine);
    virtual void DoUpdateMemoryView(const CEngineModel* engine);
    virtual void DoUpdateHintsView(const CEngineModel* engine);

private:
    CMiliTwoStateSelect  *mView;
};

class CMiliTwoStateSelect : public QWidget
{
    Q_OBJECT
    
public:
    explicit CMiliTwoStateSelect(QWidget *parent = 0);
    ~CMiliTwoStateSelect();

    void UpdateMemoryView(const CEngineModel* engine);
    void UpdateLogicView(const CEngineModel* engine);
    void UpdateHintsView(const CEngineModel* engine);

    CMcuController *McuController() {return &mMcuController;}

private:
    Ui::CMiliTwoStateSelect *ui;
    CMili2McuController      mMcuController;

    void UpdateRG(const CEngineModel* engine);

    void UpdateMS1(const CEngineModel* engine);
    void UpdateMS2(const CEngineModel* engine);

    void UpdateY(const CEngineModel* engine);
};

#endif // CMILITWOSTATESELECT_H
