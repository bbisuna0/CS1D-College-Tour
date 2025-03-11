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

tripplanning::tripplanning(std::vector<CollegeData>& collegeListParm, std::vector<SouvenirData>& souvenirListParm, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripplanning)
{
    ui->setupUi(this);
    collegeList = collegeListParm;
    souvenirList = souvenirListParm;
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
    // std::vector<CollegeData> data;
    // data = loadCollegeDataCSV("collegedist1.csv");
    std::vector<CollegeData> trip;
    float totalDistance;
    trip = planEfficientRoute("Saddleback College", collegeList, 10, totalDistance);
    // qDebug() << QString::fromStdString(data[6].collegeStart);
    // qDebug() << QString::fromStdString(data[6].collegeEnd);
    // qDebug() << data[6].distance;
    tripdisplay c(trip, totalDistance, souvenirList, this);
    c.exec();
}


void tripplanning::on_asuTripButton_clicked()
{
    bool ok;
    int stops = QInputDialog::getInt(nullptr, "ASU Trip", "Planned Stops:", 1, 1, 100, 1, &ok);
    if (ok) {
        // std::vector<CollegeData> data;
        // data = loadCollegeDataCSV("collegedist1.csv");
        std::vector<CollegeData> trip;
        float totalDistance;
        trip = planShortestTrip("Arizona State University", collegeList, stops, totalDistance);
        tripdisplay c(trip, totalDistance, souvenirList, this);
        c.exec();
    } else {
        qDebug() << "Dialog canceled";
    }
}


void tripplanning::on_uciTripButton_clicked()
{
    // std::vector<CollegeData> data;
    // data = loadCollegeDataCSV("collegedist1.csv");
    std::vector<CollegeData> trip;
    float totalDistance;
    trip = planEfficientRoute("University of California, Irvine (UCI)", collegeList, 12, totalDistance);
    tripdisplay c(trip, totalDistance, souvenirList, this);
    c.exec();
}


void tripplanning::on_customTripButton_clicked()
{
    std::vector<CollegeData> trip;
    CollegeSelectionDialog dialog(collegeList);
    if (dialog.exec() == QDialog::Accepted) {
        QStringList selectedColleges = dialog.getSelectedColleges();
        float totalDistance;
        trip = planEfficientTrip(selectedColleges, collegeList, totalDistance);
        tripdisplay c(trip, totalDistance, souvenirList, this);
        c.exec();
        }
}

