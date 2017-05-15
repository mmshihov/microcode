#include "cfzusinputdialog.h"
#include "ui_cfzusinputdialog.h"

#include <QMessageBox>

CFzusInputDialog::CFzusInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CFzusInputDialog)
{
    ui->setupUi(this);
    InitInputValidators();
}

CFzusInputDialog::~CFzusInputDialog() {
    delete ui;
}

unsigned int CFzusInputDialog::ACode() const {
    bool ok;
    int result = ui->mAModuloEdit->text().toInt(&ok, 2);

    if (ok)
        return result;

    return 0;
}

unsigned int CFzusInputDialog::BCode() const {
    bool ok;
    int result = ui->mBModuloEdit->text().toInt(&ok, 2);

    if (ok)
        return result;

    return 0;
}

void CFzusInputDialog::on_mInputButton_clicked() {
    if (IsValidInput()) {
        accept();
    } else {
        QMessageBox::warning(this,
                                 tr("Unsigned integers input error"),
                                 tr("Check divider (B) is not zero!"
                                    ));
    }
}

void CFzusInputDialog::on_mCancelButton_clicked() {reject();}

void CFzusInputDialog::on_mAModuloEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CFzusInputDialog::on_mBModuloEdit_textChanged(const QString &/*arg1*/) {
    UpdateResult();
}

void CFzusInputDialog::InitInputValidators() {
    QRegExp moduloRx(QString("[01]{8}"));
    QValidator *moduloValidator = new QRegExpValidator(moduloRx);

    ui->mAModuloEdit->setValidator(moduloValidator);
    ui->mBModuloEdit->setValidator(moduloValidator);
}

void CFzusInputDialog::UpdateResult() {
    bool         aok,   bok;
    unsigned int a,     b;

    ParseString(ui->mAModuloEdit->text(), a, &aok);
    ParseString(ui->mBModuloEdit->text(), b, &bok);

    if (aok && bok && (b != 0)) {
        unsigned int value = MakeResoultCode(a, b);

        ui->mAValueText->setText(QString("%1").arg(a));
        ui->mBValueText->setText(QString("%1").arg(b));

        ui->mADivBText->setText(QString("(%1 rem %2)")
                                    .arg(a/b)
                                    .arg(a%b));
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

        ui->mADivBText->setText("?");

        OutBadResult();
    }
}

void CFzusInputDialog::OutRightResult(unsigned int code) {
    ui->mResultText->setText(QString("A:B=(%1 rem %2)")
                             .arg((code >> 8) & 0xFF, 8, 2, QLatin1Char('0'))
                             .arg(code & 0xFF, 8, 2, QLatin1Char('0')));
}

void CFzusInputDialog::OutBadResult() {
    ui->mResultText->setText(tr("Bad operands... B==0?"));
}

bool CFzusInputDialog::IsValidInput() const {
    return (BCode() != 0);
}

void CFzusInputDialog::ParseString(const QString& valueStr, unsigned int& value, bool *ok) {
    value = (unsigned int)valueStr.toInt(ok, 2);
}

unsigned int CFzusInputDialog::ResultCode(bool *rok) const {
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

unsigned int CFzusInputDialog::MakeResoultCode(unsigned int a, unsigned int b) {
    Q_ASSERT(b != 0);

    unsigned int q = a / b;
    unsigned int r = a % b;

    unsigned int dimension = 8;
    unsigned int mask = (1 << dimension) - 1;


    return ((q & mask) << dimension) | (r & mask);
}


//-----------------------------------------------------------------------

CFzusDebugInputSource::~CFzusDebugInputSource() {
    if (mInputDialog != 0)
        delete mInputDialog;
}

bool CFzusDebugInputSource::DoIsSuccessfulQueryAndInitDebugTest(CTestVector *testVector) {
    if (InputDialog()->exec() == QDialog::Accepted) {
        InitTest(testVector);

        return true;
    }
    return false;
}

CFzusInputDialog *CFzusDebugInputSource::InputDialog() const {
    if (mInputDialog != 0)
        return mInputDialog;

    return const_cast<CFzusDebugInputSource*>(this)->mInputDialog = new CFzusInputDialog();
}

void CFzusDebugInputSource::InitTest(CTestVector *testVector) {
    CBitBlock A(8, InputDialog()->ACode());
    CBitBlock B(8, InputDialog()->BCode());

    testVector->ProgramInputPart(0, 0, A);
    testVector->ProgramInputPart(0, 1, B);

    testVector->MakeWrongOutputPartsForTest(0);
}

