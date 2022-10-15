#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include <QString>
#include <QByteArray>
#include "command.h"
#include <string>

//Dazhuang Teng 251052285
// 10/5/2021
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
  void handleButton();//all the button action
  void displayHistory();//all the listwidger action
private:
    QLabel *commandQ;
    QLabel *exit;
    QLabel *code;
    QLabel *output;
    QLabel *history;
    QLabel *nothing;//this is an empty label, just to adjust the prostion of some item
    QLineEdit *command_input;//inputarea
    QTextEdit *command_output;//output area
    QPushButton *runButton;//working button, the only way to complie this is to click.
    QGridLayout *layoutpart1;
    QVBoxLayout *layoutpart2;
    QVBoxLayout *layoutpart3;
    QHBoxLayout *finallayout;
    QHBoxLayout *layoutpart4;
    QListWidget *command_history;
    std::string historyText[1000];//the array that save all histoty output
};
#endif // MAINWINDOW_H
