#ifndef CCHECKINDIVIDUALTASKDIALOG_H
#define CCHECKINDIVIDUALTASKDIALOG_H

#include <QDialog>

namespace Ui {
class CCheckIndividualTaskDialog;
}

class CCheckIndividualTaskDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CCheckIndividualTaskDialog(QWidget *parent = 0);
    ~CCheckIndividualTaskDialog();
    
private slots:
    void on_mCancelButton_clicked();

    void on_mCheckButton_clicked();

private:
    Ui::CCheckIndividualTaskDialog *ui;
};

#endif // CCHECKINDIVIDUALTASKDIALOG_H
