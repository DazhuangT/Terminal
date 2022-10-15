#include "mainwindow.h"
#include <QApplication>

//Dazhuang Teng 251052285
//10/5/2021
//this class display the window
int main(int argc, char *argv[])
{
    QApplication asn(argc, argv);
    MainWindow Gui;
    Gui.show();
    return asn.exec();
}
