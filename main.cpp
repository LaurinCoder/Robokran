#include "mainwindow.h"
#include <QApplication>
#include <grippoint.h> //added for Grippoint 23.11.17



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.setGeometry(50,50,1200,700);
    w.show();
    return a.exec();

}
