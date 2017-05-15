#ifndef CDCMCTEXTSOURCE_H
#define CDCMCTEXTSOURCE_H

#include <QObject>
#include "../../../chint.h"

class CDcmcTextSource : public QObject {
    Q_OBJECT
public:
    explicit CDcmcTextSource(QObject *parent = 0);

    static QString PhysicalY_Way1(unsigned int index);
    static QString PhysicalP_Way1(unsigned int index);
    static QString NameWay1();

    static QString PhysicalY_Way2(unsigned int index);
    static QString PhysicalP_Way2(unsigned int index);
    static QString NameWay2();

    static QString PhysicalY_Way3(unsigned int index);
    static QString PhysicalP_Way3(unsigned int index);
    static QString NameWay3();

    static QString PhysicalY_Way4(unsigned int index);
    static QString PhysicalP_Way4(unsigned int index);
    static QString NameWay4();
};

class CDcmcHint_Way1 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcmcTextSource::PhysicalY_Way1(index);}
    virtual QString DoP(unsigned int index) const {return CDcmcTextSource::PhysicalP_Way1(index);}
};

class CDcmcHint_Way2 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcmcTextSource::PhysicalY_Way2(index);}
    virtual QString DoP(unsigned int index) const {return CDcmcTextSource::PhysicalP_Way2(index);}
};

class CDcmcHint_Way3 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcmcTextSource::PhysicalY_Way3(index);}
    virtual QString DoP(unsigned int index) const {return CDcmcTextSource::PhysicalP_Way3(index);}
};

class CDcmcHint_Way4 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CDcmcTextSource::PhysicalY_Way4(index);}
    virtual QString DoP(unsigned int index) const {return CDcmcTextSource::PhysicalP_Way4(index);}
};

#endif // CDCMCTEXTSOURCE_H
