#include "csignalvaluegroup.h"
#include "csignalvalue.h"

#include <QHBoxLayout>

CSignalValueGroup::CSignalValueGroup(const QString& groupHint,
                                     const QString& signalHint,
                                     unsigned int index,
                                     unsigned int dim,
                                     unsigned int unusedCount,
                                     QWidget *parent) :
    QGroupBox(parent)
{
    Q_ASSERT(dim > unusedCount);

    mIndex = index;

    mDim = dim;
    mUnusedCount = unusedCount;

    unsigned int signalIndex = dim * index;

    QHBoxLayout *vBox = new QHBoxLayout();
    mSignals = new CSignalValue*[mDim];

    for (unsigned int i=0; i<mDim; ++i) {
        CSignalValue *sv = new CSignalValue();
        mSignals[i] = sv;
        vBox->addWidget(sv);

        if (i >= (mDim - mUnusedCount))
            sv->SetUnused();
        else {
            sv->SetSignalHint(QString("%1%2")
                              .arg(signalHint)
                              .arg(signalIndex));
            sv->SetSignalValue(false);
        }

        signalIndex++;
    }

    setLayout(vBox);
    setTitle(QString("%1%2")
             .arg(groupHint)
             .arg(mIndex));
}

CSignalValueGroup::~CSignalValueGroup() {
    delete[] mSignals;
}

void CSignalValueGroup::SetSignalValue(unsigned int signalIndex, bool value) {
    Q_ASSERT(signalIndex < (mDim - mUnusedCount));

    if (signalIndex < (mDim - mUnusedCount)) {
        mSignals[signalIndex]->SetSignalValue(value);
    }
}
