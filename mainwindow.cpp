#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!myUser.admin)
    {
        ui->pushButton_5->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_6_clicked()
{

    this->close();
}

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{

}


void MainWindow::on_pushButton_5_clicked()
{

}
