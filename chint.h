#ifndef CHINT_H
#define CHINT_H

#include <QString>

class CHint {
public:
    CHint();
    virtual ~CHint() {}

    QString Y(unsigned int index) const;
    QString P(unsigned int index) const;

protected:
    virtual QString DoY(unsigned int index) const = 0;
    virtual QString DoP(unsigned int index) const = 0;
};

#endif // CHINT_H
