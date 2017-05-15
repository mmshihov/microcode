#include "cdcmcinputdialog.h"
#include "ui_cdcmcinputdialog.h"

#include <QMessageBox>

CDcmcInputDialog::CDcmcInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDcmcInputDialog)
{
    ui->setupUi(this);
    InitInputValidators();
}

CDcmcInputDialog::~CDcmcInputDialog() {
    delete ui;
}

unsigned int CDcmcInputDialog::ACode() const {
    bool ok;
    return ui->mAModuloEdit->text().toInt(&ok, 2);
}

unsigned int CDcmcInputDialog::BCode() const {
    bool ok;
    return ui->mBModuloEdit->text().toInt(&ok, 2);
}

void CDcmcInputDialog::on_mInputButton_clicked() {
    if (IsValidInput()) {
        accept();
    } else {
        QMessageBox::warning(this,
                                 tr("Two's complement code error"),
                                 tr("Type 8 bits in each code field, please."
                                    ));
    }
}

void CDcmcInputDialog::on_mCancelButton_clicked() {reject();}

void CDcmcInputDialog::on_mAModuloEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CDcmcInputDialog::on_mBModuloEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CDcmcInputDialog::InitInputValidators() {
    QRegExp moduloRx(QString("[01]{8}"));
    QValidator *moduloValidator = new QRegExpValidator(moduloRx);

    ui->mAModuloEdit->setValidator(moduloValidator);
    ui->mBModuloEdit->setValidator(moduloValidator);
}

void CDcmcInputDialog::UpdateResult() {
    bool         aok,   bok;
    int          a,     b;
    unsigned int acode, bcode;


    ParseString(ui->mAModuloEdit->text(), acode, a, &aok);
    ParseString(ui->mBModuloEdit->text(), bcode, b, &bok);

    if (aok && bok) {
        unsigned int value = MakeResoultCode(acode, bcode);

        ui->mAValueText->setText(QString("%1").arg(a));
        ui->mBValueText->setText(QString("%1").arg(b));

        ui->mABValueText->setText(QString("%1").arg(a*b));

        OutRightResult(value);
    } else {
        if (aok)
            ui->mAValueText->setText(QString("%1").arg(a));
        else
            ui->mAValueText->setText("?");

        if (bok)
            ui->mBValueText->setText(QString("%1").arg(b));
        else
            ui->mBValueText->setText("?");

        ui->mABValueText->setText("?");

        OutBadResult();
    }
}

void CDcmcInputDialog::OutRightResult(unsigned int code) {
    ui->mResultText->setText(QString("A*B=(%1 %2)")
                             .arg((code >> 8) & 0xFF, 8, 2, QLatin1Char('0'))
                             .arg(code & 0xFF, 8, 2, QLatin1Char('0')));
}

void CDcmcInputDialog::OutBadResult() {
    ui->mResultText->setText(tr("Bad operands... Type 8 bits!"));
}

bool CDcmcInputDialog::IsValidInput() const {
    return    (ui->mAModuloEdit->text().length() == 8)
           && (ui->mBModuloEdit->text().length() == 8)
            ;
}

void CDcmcInputDialog::ParseString(const QString &str, unsigned int& code, int& value, bool *ok) {
    int dimension = 8;

    *ok = false;
    code = 0;
    value = 0;

    if (str.length() != dimension)
        return;

    code = str.toInt(ok, 2);
    if (!*ok)
        return;

    unsigned int mask = (1 << dimension) - 1;
    unsigned int sign = (1 << (dimension - 1));

    if ((code & sign) == 0) {
        value = (int)code;
    } else {
        value = -((~code + 1) & mask);
    }
}

unsigned int CDcmcInputDialog::ResultCode(bool *rok) const {
    bool ok = IsValidInput();

    *rok = false;
    if (!ok)
        return 0;

    int a = ui->mAModuloEdit->text().toInt(&ok, 2);
    if (!ok)
        return 0;

    int b = ui->mBModuloEdit->text().toInt(&ok, 2);
    if (!ok)
        return 0;

    *rok = true;
    return MakeResoultCode(a,b);
}

unsigned int CDcmcInputDialog::MakeResoultCode(unsigned int a, unsigned int b) {
    unsigned int dimension = 8;
    unsigned int mask = (1 << dimension) - 1;
    unsigned int sign = (1 << (dimension - 1));

    unsigned int psm = (a & mask) * (b & mask);
    if ((a & sign) != 0) {
        psm += (((~b) + 1) & mask) << dimension;
    }
    if ((b & sign) != 0) {
        psm += (((~a) + 1) & mask) << dimension;
    }

    return psm & ((mask << dimension) | mask);
}


//-----------------------------------------------------------------------

CDcmcDebugInputSource::~CDcmcDebugInputSource() {
    if (mInputDialog != 0)
        delete mInputDialog;
}

bool CDcmcDebugInputSource::DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector) {
    if (InputDialog()->exec() == QDialog::Accepted) {
        InitTest(testVector);

        return true;
    }
    return false;
}

CDcmcInputDialog *CDcmcDebugInputSource::InputDialog() const {
    if (mInputDialog != 0)
        return mInputDialog;

    return const_cast<CDcmcDebugInputSource*>(this)->mInputDialog = new CDcmcInputDialog();
}

void CDcmcDebugInputSource::InitTest(CTestVector *testVector) {
    CBitBlock A(8, InputDialog()->ACode());
    CBitBlock B(8, InputDialog()->BCode());

    testVector->ProgramInputPart(0, 0, A);
    testVector->ProgramInputPart(0, 1, B);

    testVector->MakeWrongOutputPartsForTest(0);
}

