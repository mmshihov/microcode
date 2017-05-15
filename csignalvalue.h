#ifndef CSIGNALVALUE_H
#define CSIGNALVALUE_H

#include <QWidget>

namespace Ui {
class CSignalValue;
}

class CSignalValue : public QWidget
{
    Q_OBJECT
    
public:
    explicit CSignalValue(QWidget *parent = 0);
    ~CSignalValue();
    
    void SetUnused();
    void SetSignalValue(bool value);
    void SetSignalHint(const QString& hint);

private:
    Ui::CSignalValue *ui;
};

#endif // CSIGNALVALUE_H
