#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <GL/glut.h>

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QTranslator *translator = new QTranslator;
    if(!translator->load("/home/hubert/wds/wds-app/wds-app_en_EN.qm")) {
        qDebug() << "Error in loading translation file";
    }
    QApplication a(argc, argv);
    a.installTranslator(translator);
    MainWindow w;
    w.show();
    return a.exec();
}
