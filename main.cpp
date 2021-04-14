#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <time.h>
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);

    QFile styleSheetFile("D:/L3/S6/GraphesAlgo/Projet/grapheUi/Combinear.qss");

    //Jules D:/L3/S6/GraphesAlgo/Projet/grapheUi/Combinear.qss
    //lucas D:/Git/grapheUi/Combinear.qss

    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet); // .qss


    MainWindow w;
    w.show();
    return a.exec();
}
