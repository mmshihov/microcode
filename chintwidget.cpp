#include "chintwidget.h"

#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>


void CHintWidgetEngineController::DoUpdateHintsView() {mView->UpdateHints();}

CHintWidget::CHintWidget(CEngineModel *model, QWidget* parent)
        : QWidget(parent)
        , mEngineController(this) {
    model->AppendController(&mEngineController); //inits mEngineController...

    CreateUi();
}

void CHintWidget::UpdateHints() {
    unsigned int inDim = ControlInputDim();
    for (unsigned int i=0; i<inDim; ++i) {
        mMcuControlInputs[i]->setText(
                    QString("p%1: %2")
                        .arg(i)
                        .arg(Engine()->HintForLogicalPIndex(i)));
        mMcuControlInputs[i]->adjustSize();
    }

    unsigned int outDim = ControlOutputDim();
    for (unsigned int i=0; i<outDim; ++i) {
        mMcuControlOutputs[i]->setText(
                    QString("y%1: %2")
                        .arg(i)
                        .arg(Engine()->HintForLogicalYIndex(i)));
        mMcuControlOutputs[i]->adjustSize();
    }
}

void CHintWidget::CreateUi() {
    CreateLabels();
    UpdateHints();
    LayoutLabels();
}

void CHintWidget::CreateLabels() {
    unsigned int inDim = ControlInputDim();
    mMcuControlInputs = new QLabel*[inDim];
    for (unsigned int i=0; i<inDim; ++i) {
        mMcuControlInputs[i] = new QLabel();
    }

    unsigned int outDim = ControlOutputDim();
    mMcuControlOutputs = new QLabel*[outDim];
    for (unsigned int i=0; i<outDim; ++i) {
        mMcuControlOutputs[i] = new QLabel();
    }
}

void CHintWidget::LayoutLabels() {
    QHBoxLayout *mainLayout = new QHBoxLayout();

    QVBoxLayout *layout = CreateVerticalLayout();

    unsigned int dim = ControlInputDim();
    int          height = 0;
    for (unsigned int i=0; i<dim; ++i) {
        if ((height + mMcuControlInputs[i]->height()
             + mainLayout->contentsMargins().top()
             + mainLayout->contentsMargins().bottom()
             + layout->contentsMargins().top()
             + layout->contentsMargins().bottom()) > WIDGET_HEIGHT) {
            layout->addStretch(WIDGET_HEIGHT);
            mainLayout->addLayout(layout);

            layout = CreateVerticalLayout();
            height = 0;
        }
        layout->addWidget(mMcuControlInputs[i]);
        height += mMcuControlInputs[i]->height()
                + layout->contentsMargins().top()
                + layout->contentsMargins().bottom();
    }
    layout->addStretch(WIDGET_HEIGHT);
    mainLayout->addLayout(layout);

    layout = CreateVerticalLayout();
    dim    = ControlOutputDim();
    height = 0;
    for (unsigned int i=0; i<dim; ++i) {
        if ((height + mMcuControlOutputs[i]->height()
             + mainLayout->contentsMargins().top()
             + mainLayout->contentsMargins().bottom()
             + layout->contentsMargins().top()
             + layout->contentsMargins().bottom()) > WIDGET_HEIGHT) {
            layout->addStretch(WIDGET_HEIGHT);
            mainLayout->addLayout(layout);

            layout = CreateVerticalLayout();
            height = 0;
        }
        layout->addWidget(mMcuControlOutputs[i]);
        height +=
                mMcuControlOutputs[i]->height()
                + layout->contentsMargins().top()
                + layout->contentsMargins().bottom();
    }
    layout->addStretch(WIDGET_HEIGHT);
    mainLayout->addLayout(layout);

    setLayout(mainLayout);
    setFixedSize(WIDGET_WIDTH, WIDGET_HEIGHT);
}

QVBoxLayout *CHintWidget::CreateVerticalLayout() const {
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(5,5,5,5);
    return layout;
}


