#include "ccheckindividualtaskdialog.h"
#include "ui_ccheckindividualtaskdialog.h"

#include <QMessageBox>
#include "cindividualtask.h"

CCheckIndividualTaskDialog::CCheckIndividualTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCheckIndividualTaskDialog)
{
    ui->setupUi(this);
}

CCheckIndividualTaskDialog::~CCheckIndividualTaskDialog() {
    delete ui;
}

void CCheckIndividualTaskDialog::on_mCancelButton_clicked() {
    reject();
}

void CCheckIndividualTaskDialog::on_mCheckButton_clicked() {
    if (!CIndividualTask::Instance()->IsLoaded()) {
        QMessageBox::warning(this, tr("Check error"), tr("No individual variant was loaded!"));
        reject();
        return;
    }

    if (!CIndividualTask::Instance()->IsIntegrityValid(ui->mSecretEdit->text())) {
        QMessageBox::warning(this, tr("Corruption error"), tr("Individual variant was corrupted!"));
        reject();
        return;
    }

    QMessageBox::information(this,
                             tr("OK"),
                             QString("%1\n   %2")
                             .arg(tr("Individual variant correct for:"))
                             .arg(CIndividualTask::Instance()->StudentId()));
    accept();
}
