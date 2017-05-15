#ifndef CPC2DCINPUTDIALOG_H
#define CPC2DCINPUTDIALOG_H

#include <QDialog>

#include "../../../ctestvector.h"

namespace Ui {
class CPc2DcInputDialog;
}

class CPc2DcInputDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit CPc2DcInputDialog(QWidget *parent = 0);
    ~CPc2DcInputDialog();
    
    unsigned int ADirectCode() const;

private slots:
    void on_mInputButton_clicked();
    void on_mCancelButton_clicked();
    void on_mASignEdit_textChanged(const QString &arg1);
    void on_mAModuloEdit_textChanged(const QString &arg1);

private:
    Ui::CPc2DcInputDialog *ui;

    void InitInputValidators();
    bool IsValidInput() const;

    void UpdateResult();
    void OutRightResult(unsigned int code);
    void OutBadResult();

    unsigned int ResultCode(bool *ok) const;

    static unsigned int MakeOperandDirectCode(unsigned int sign, unsigned int modulo);
    static unsigned int MakeTwosCode(unsigned int sign, unsigned int modulo);
};


class CPc2DcDebugInputSource : public CDebugInputSource {
public:
    CPc2DcDebugInputSource() : mInputDialog(0) {}
    virtual ~CPc2DcDebugInputSource();
protected:
    virtual bool DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector);
private:
    CPc2DcInputDialog *mInputDialog;

    CPc2DcInputDialog *InputDialog() const;

    void InitTest(CTestVector *testVector);
};

#endif // CPC2DCINPUTDIALOG_H
