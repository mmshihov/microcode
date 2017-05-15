#ifndef CSIGNALVALUEGROUP_H
#define CSIGNALVALUEGROUP_H

#include <QGroupBox>

class CSignalValue;

class CSignalValueGroup : public QGroupBox {
    Q_OBJECT
    
public:
    explicit CSignalValueGroup(const QString& groupHint,
                               const QString& signalHint,
                               unsigned int index,
                               unsigned int dim,
                               unsigned int unusedCount = 0,
                               QWidget *parent = 0);
    ~CSignalValueGroup();
    
    void SetSignalValue(unsigned int signalIndex, bool value);

private:
    unsigned int mIndex;
    unsigned int mDim;
    unsigned int mUnusedCount;

    CSignalValue **mSignals;
};

#endif // CSIGNALVALUEGROUP_H
