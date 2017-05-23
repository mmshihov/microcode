#include "cindividualtaskcreationdialog.h"
#include "ui_cindividualtaskcreationdialog.h"

#include <QFileDialog>
#include <QMessageBox>

#include "cindividualtask.h"


CIndividualTaskCreationDialog::CIndividualTaskCreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CIndividualTaskCreationDialog)
{
    ui->setupUi(this);
}

CIndividualTaskCreationDialog::~CIndividualTaskCreationDialog() {
    delete ui;
}

void CIndividualTaskCreationDialog::on_mOpenRecipientsFileButton_clicked() {
    ui->mRecipientsFilePathEdit->setText(QString());

    QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Open recipient list file"),
                    QString(),
                    tr("JSON recipient list (*.json);;JSON recipient list in text (*.txt)"));
    if (fileName.isNull())
        return;

    ui->mRecipientsFilePathEdit->setText(fileName);
}

void CIndividualTaskCreationDialog::on_mTaskFolderButton_clicked() {
    ui->mTaskFolderPathEdit->setText(QString());

    QString dirName = QFileDialog::getExistingDirectory(
                    this,
                    tr("Select individual variants directory"));
    if (dirName.isNull())
        return;

    ui->mTaskFolderPathEdit->setText(dirName);
}

void CIndividualTaskCreationDialog::on_mGenerateButton_clicked() {
    if (ui->mRecipientsFilePathEdit->text().isNull()
            || ui->mTaskFolderPathEdit->text().isNull()) {

        QMessageBox::information(this,
                                 tr("Incomplete input"),
                                 tr("Recipient list and variant folder is necessary!"));
        return;
    }

    CIndividualTask::EStatus genStatus;
    QString message;

    CIndividualTask::Instance()->GenerateTasks(ui->mRecipientsFilePathEdit->text(),
                                   ui->mTaskFolderPathEdit->text(),
                                   ui->mSecretEdit->text(),
                                   genStatus,
                                   message);

    if (genStatus != CIndividualTask::OK) {
        QMessageBox::information(this,
                                 tr("Variants generation error"),
                                 message);
        reject();
        return;
    }

    accept();
}

void CIndividualTaskCreationDialog::on_mCancelButton_clicked() { reject(); }
