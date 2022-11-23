#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <arduino-serial.h>

//extern "C" {
//int arduinoSerial(int argc, char **argv);
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    char *argv1[]={"appname","-h","test"};
         int argc1 = sizeof(argv1) / sizeof(char*) - 1;
arduinoSerial(argc1,argv1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

