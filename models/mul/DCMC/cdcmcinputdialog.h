#ifndef CDCMCINPUTDIALOG_H
#define CDCMCINPUTDIALOG_H

#include <QDialog>

#include "../../../ctestvector.h"

namespace Ui {
class CDcmcInputDialog;
}

class CDcmcInputDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit CDcmcInputDialog(QWidget *parent = 0);
    ~CDcmcInputDialog();
    
    unsigned int ACode() const;
    unsigned int BCode() const;

private slots:
    void on_mInputButton_clicked();
    void on_mCancelButton_clicked();
    void on_mAModuloEdit_textChanged(const QString &arg1);
    void on_mBModuloEdit_textChanged(const QString &arg1);

private:
    Ui::CDcmcInputDialog *ui;

    void InitInputValidators();

    void UpdateResult();
    void OutRightResult(unsigned int code);
    void OutBadResult();

    bool IsValidInput() const;

    static void ParseString(const QString& str, unsigned int& code, int& value, bool *ok);
    unsigned int ResultCode(bool *ok) const;

    static unsigned int MakeResoultCode(unsigned int a, unsigned int b);
};

class CDcmcDebugInputSource : public CDebugInputSource {
public:
    CDcmcDebugInputSource() : mInputDialog(0) {}
    virtual ~CDcmcDebugInputSource();

protected:
    virtual bool DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector);

private:
    CDcmcInputDialog *mInputDialog;

    CDcmcInputDialog *InputDialog() const;

    void InitTest(CTestVector *testVector);
};

#endif // CDCMCINPUTDIALOG_H
