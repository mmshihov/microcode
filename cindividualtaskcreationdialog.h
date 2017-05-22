#ifndef CINDIVIDUALTASKCREATIONDIALOG_H
#define CINDIVIDUALTASKCREATIONDIALOG_H

#include <QDialog>

namespace Ui {
class CIndividualTaskCreationDialog;
}

class CIndividualTaskCreationDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit CIndividualTaskCreationDialog(QWidget *parent = 0);
    ~CIndividualTaskCreationDialog();
    
private slots:
    void on_mOpenRecipientsFileButton_clicked();
    void on_mTaskFolderButton_clicked();
    void on_mGenerateButton_clicked();

    void on_mCancelButton_clicked();

private:
    Ui::CIndividualTaskCreationDialog *ui;
};

#endif // CINDIVIDUALTASKCREATIONDIALOG_H
