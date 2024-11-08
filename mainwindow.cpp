#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "login_signup/signup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
