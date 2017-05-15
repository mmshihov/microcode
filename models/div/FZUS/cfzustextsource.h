#ifndef CFZUSTEXTSOURCE_H
#define CFZUSTEXTSOURCE_H

#include <QObject>
#include "../../../chint.h"


class CFzusTextSource : public QObject {
    Q_OBJECT
public:
    explicit CFzusTextSource(QObject *parent = 0);

    static QString PhysicalY_Way1(unsigned int index);
    static QString PhysicalP_Way1(unsigned int index);
    static QString NameWay1();

    static QString PhysicalY_Way2(unsigned int index);
    static QString PhysicalP_Way2(unsigned int index);
    static QString NameWay2();

    static QString PhysicalY_Way3(unsigned int index);
    static QString PhysicalP_Way3(unsigned int index);
    static QString NameWay3();
};


class CFzusHint_Way1 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CFzusTextSource::PhysicalY_Way1(index);}
    virtual QString DoP(unsigned int index) const {return CFzusTextSource::PhysicalP_Way1(index);}
};

class CFzusHint_Way2 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CFzusTextSource::PhysicalY_Way2(index);}
    virtual QString DoP(unsigned int index) const {return CFzusTextSource::PhysicalP_Way2(index);}
};

class CFzusHint_Way3 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CFzusTextSource::PhysicalY_Way3(index);}
    virtual QString DoP(unsigned int index) const {return CFzusTextSource::PhysicalP_Way3(index);}
};

#endif // CFZUSTEXTSOURCE_H
