#ifndef CFADDINPUTDIALOG_H
#define CFADDINPUTDIALOG_H

#include <QDialog>

#include "../../../ctestvector.h"

namespace Ui {
class CFaddInputDialog;
}

class CFaddInputDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit CFaddInputDialog(QWidget *parent = 0);
    ~CFaddInputDialog();

    CBitBlock A() const;
    CBitBlock B() const;

private slots:
    void on_mInputButton_clicked();
    void on_mCancelButton_clicked();
    void on_mAmantEdit_textChanged(const QString &arg1);
    void on_mBmantEdit_textChanged(const QString &arg1);
    void on_mAcharEdit_textChanged(const QString &arg1);
    void on_mBcharEdit_textChanged(const QString &arg1);

private:
    Ui::CFaddInputDialog *ui;

    void InitInputValidators();

    bool IsValidInput();
    static CBitBlock GetFromStrings(const QString& mantString, const QString& charString, bool& ok);

    void UpdateResult();
    void UpdateResultHint(const QString& error, const QString& result);
    static QString FormatDouble(double value);
};

class CFaddDebugInputSource : public CDebugInputSource {
public:
    CFaddDebugInputSource() : mInputDialog(0) {}
    virtual ~CFaddDebugInputSource();
protected:
    virtual bool DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector);
private:
    CFaddInputDialog *mInputDialog;

    CFaddInputDialog *InputDialog() const;

    void InitTest(CTestVector *testVector);
};

#endif // CFADDINPUTDIALOG_H
