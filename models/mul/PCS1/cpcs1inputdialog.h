#ifndef CPCS1INPUTDIALOG_H
#define CPCS1INPUTDIALOG_H

#include <QDialog>

#include "../../../ctestvector.h"

namespace Ui {
class CPcs1InputDialog;
}

class CPcs1InputDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit CPcs1InputDialog(QWidget *parent = 0);
    ~CPcs1InputDialog();
    
    unsigned int ADirectCode() const;
    unsigned int BDirectCode() const;

private slots:
    void on_mInputButton_clicked();
    void on_mCancelButton_clicked();
    void on_mASignEdit_textChanged(const QString &arg1);
    void on_mBSignEdit_textChanged(const QString &arg1);
    void on_mAModuloEdit_textChanged(const QString &arg1);
    void on_mBModuloEdit_textChanged(const QString &arg1);


private:
    Ui::CPcs1InputDialog *ui;

    void InitInputValidators();
    bool IsValidInput();

    void UpdateResult();
    void OutRightResult(unsigned int code);
    void OutBadResult();

    static void ParseInput(const QString& signString, const QString& moduloString,
                           unsigned int& signValue, unsigned int& moduloValue,
                           int& value,
                           bool *ok);
    unsigned int ResultDirectCode(bool *ok) const;

    static unsigned int MakeOperandDirectCode(unsigned int sign, unsigned int modulo);
    static unsigned int MakeResoultDirectCode(unsigned int sign, unsigned int modulo);
};

class CPcs1DebugInputSource : public CDebugInputSource {
public:
    CPcs1DebugInputSource() : mInputDialog(0) {}
    virtual ~CPcs1DebugInputSource();
protected:
    virtual bool DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector);
private:
    CPcs1InputDialog *mInputDialog;

    CPcs1InputDialog *InputDialog() const;

    void InitTest(CTestVector *testVector);
};

#endif // CPCS1INPUTDIALOG_H
