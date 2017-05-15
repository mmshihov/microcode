#ifndef CFZUSINPUTDIALOG_H
#define CFZUSINPUTDIALOG_H

#include <QDialog>

#include "../../../ctestvector.h"

namespace Ui {
class CFzusInputDialog;
}

class CFzusInputDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit CFzusInputDialog(QWidget *parent = 0);
    ~CFzusInputDialog();

    unsigned int ACode() const;
    unsigned int BCode() const;

private slots:
    void on_mInputButton_clicked();
    void on_mCancelButton_clicked();
    void on_mAModuloEdit_textChanged(const QString &arg1);
    void on_mBModuloEdit_textChanged(const QString &arg1);

private:
    Ui::CFzusInputDialog *ui;

    void InitInputValidators();

    void UpdateResult();
    void OutRightResult(unsigned int code);
    void OutBadResult();

    bool IsValidInput() const;

    static void ParseString(const QString& valueStr, unsigned int& value, bool *ok);
    unsigned int ResultCode(bool *ok) const;

    static unsigned int MakeResoultCode(unsigned int a, unsigned int b);
};


class CFzusDebugInputSource : public CDebugInputSource {
public:
    CFzusDebugInputSource() : mInputDialog(0) {}
    virtual ~CFzusDebugInputSource();
protected:
    virtual bool DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector);
private:
    CFzusInputDialog *mInputDialog;

    CFzusInputDialog *InputDialog() const;

    void InitTest(CTestVector *testVector);
};

#endif // CFZUSINPUTDIALOG_H
