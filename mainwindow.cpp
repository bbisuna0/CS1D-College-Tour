#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collegedistances.h"
#include "listsouvenirs.h"
#include "utility.h"
#include <QDebug>
#include <QDir>
#include "tripplanning.h"
#include "maintenance.h"

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
//     if (!myUser.admin)
//     {
//         ui->pushButton_5->setEnabled(false);
//     }
// }

MainWindow::MainWindow(std::vector<CollegeData>& collegeListParm, std::vector<SouvenirData>& souvenirListParm, QWidget *parent)
    : QMainWindow(parent), collegeList(collegeListParm), souvenirList(souvenirListParm)
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


void MainWindow::on_collegeDistanceButton_clicked()
{
    // std::vector<CollegeData> data;
    // data = loadCollegeDataCSV("collegedist1.csv");
    QString currentDir = QDir::currentPath();
    qDebug() << "Current working directory:" << currentDir;
    // qDebug() << QString::fromStdString(data[6].collegeStart);
    // qDebug() << QString::fromStdString(data[6].collegeEnd);
    // qDebug() << data[6].distance;
    collegedistances c(collegeList, this);
    c.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_4_clicked()
{
    tripplanning c(collegeList, souvenirList, this);
    c.exec();
}

void MainWindow::on_souvenirButton_clicked()
{
    // std::vector<SouvenirData> data;
    // data = loadSouvenirCSV("souvenirs1.csv");
    // qDebug() << QString::fromStdString(data[0].college);
    // qDebug() << QString::fromStdString(data[0].souvenir);
    // qDebug() << QString::fromStdString(data[0].cost);

    listsouvenirs c(souvenirList, this);
    c.exec();
}


void MainWindow::on_pushButton_5_clicked()
{
    maintenance c(collegeList, souvenirList, this);
    c.exec();
    qDebug() << "Size of list main: " << collegeList.size();
}
