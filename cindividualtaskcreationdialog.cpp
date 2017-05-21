#include "cindividualtaskcreationdialog.h"
#include "ui_cindividualtaskcreationdialog.h"

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

}

void CIndividualTaskCreationDialog::on_mTaskFolderButton_clicked() {

}

void CIndividualTaskCreationDialog::on_mGenerateButton_2_clicked() {

}

void CIndividualTaskCreationDialog::on_mGenerateButton_clicked() {

}
