#include "tripplanning.h"
#include "ui_tripplanning.h"
#include "utility.h"
#include "tripdisplay.h"
#include <QInputDialog>

tripplanning::tripplanning(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripplanning)
{
    ui->setupUi(this);
}

tripplanning::~tripplanning()
{
    delete ui;
}

void tripplanning::on_exitButton_clicked()
{
    this->close();
}


void tripplanning::on_visitSBCButton_clicked()
{
    std::vector<CollegeData> data;
    data = loadCollegeDataCSV("collegedist1.csv");
    std::vector<CollegeData> trip;
    float totalDistance;
    trip = planEfficientRoute("Saddleback College", data, 11, totalDistance);
    // qDebug() << QString::fromStdString(data[6].collegeStart);
    // qDebug() << QString::fromStdString(data[6].collegeEnd);
    // qDebug() << data[6].distance;
    tripdisplay c(trip, totalDistance, this);
    //c.setAttribute(Qt::WA_DeleteOnClose);
    c.exec();
}


void tripplanning::on_asuTripButton_clicked()
{
    bool ok;
    int stops = QInputDialog::getInt(nullptr, "ASU Trip", "Planned Stops:", 0, -100, 100, 1, &ok);
    if (ok) {
        std::vector<CollegeData> data;
        data = loadCollegeDataCSV("collegedist1.csv");
        std::vector<CollegeData> trip;
        float totalDistance;
        trip = planShortestTrip("Arizona State University", data, stops, totalDistance);
        tripdisplay c(trip, totalDistance, this);
        //c.setAttribute(Qt::WA_DeleteOnClose);
        c.exec();
    } else {
        qDebug() << "Dialog canceled";
    }
}


void tripplanning::on_uciTripButton_clicked()
{
    std::vector<CollegeData> data;
    data = loadCollegeDataCSV("collegedist1.csv");
    std::vector<CollegeData> trip;
    float totalDistance;
    trip = planEfficientRoute("University of California, Irvine (UCI)", data, 13, totalDistance);
    tripdisplay c(trip, totalDistance, this);
    //c.setAttribute(Qt::WA_DeleteOnClose);
    c.exec();
}

