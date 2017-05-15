#include "cmicrocodemainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;

    QCoreApplication::setOrganizationName("S.M.M.Software");
    QCoreApplication::setOrganizationDomain("m.m.shihov@gmail.com");
    QCoreApplication::setApplicationName("Microcode Engine");

    QSettings settings;

    QString lang = settings.value("ui/language", "en_US").toString();
    if (lang == "ru_RU") {
        translator.load(":translate/ru_RU");
        a.installTranslator(&translator);
    }

    CMicrocodeMainWindow w;
    w.show();
    return a.exec();
}
