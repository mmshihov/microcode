#ifndef CPC2DCTEXTSOURCE_H
#define CPC2DCTEXTSOURCE_H

#include <QObject>
#include "../../../chint.h"


class CPc2DcTextSource : public QObject {
    Q_OBJECT
public:
    CPc2DcTextSource(QObject *parent = 0);

    static QString PhysicalY_Way1(unsigned int index);
    static QString PhysicalP_Way1(unsigned int index);
    static QString NameWay1();
};


class CPc2DcHint_Way1 : public CHint {
protected:
    virtual QString DoY(unsigned int index) const {return CPc2DcTextSource::PhysicalY_Way1(index);}
    virtual QString DoP(unsigned int index) const {return CPc2DcTextSource::PhysicalP_Way1(index);}
};

#endif // CPC2DCTEXTSOURCE_H
