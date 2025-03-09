#include "utility.h"
#include "maintenance.h"
#include <QInputDialog>

// maintenance::maintenance(QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::maintenance)
// {
//     ui->setupUi(this);
// }

maintenance::maintenance(std::vector<CollegeData>& collegeListParm, std::vector<SouvenirData>& souvenirListParm, QWidget *parent)
    : QDialog(parent), collegeList(collegeListParm), souvenirList(souvenirListParm)
    , ui(new Ui::maintenance)
{
    ui->setupUi(this);
}

maintenance::~maintenance()
{
    delete ui;
}

void maintenance::on_exitButton_clicked()
{
    this->close();
}

void maintenance::on_loadOrgCollegeDataButton_clicked()
{
    // load college data for distances (default data)
    collegeList = loadCollegeDataCSV(ORIGINAL_COLLEGE_FILE);
    showFileLoadedMessage(this, QString::fromStdString(ORIGINAL_COLLEGE_FILE));
}


void maintenance::on_loadOrgSouvenirDataButton_clicked()
{
    // load souvenir data for distances (default data)
    souvenirList = loadSouvenirCSV(ORIGINAL_SOUVENIR_FILE);
    showFileLoadedMessage(this, QString::fromStdString(ORIGINAL_SOUVENIR_FILE));
}


void maintenance::on_loadBulkDataButton_clicked()
{
    std::vector<CollegeData> newList;
    newList = loadCollegeDataCSV(BULK_FILE, collegeList);
    // collegeList = loadCollegeDataCSV(ORIGINAL_COLLEGE_FILE, collegeList);
    //collegeList = newList;
    qDebug() << "Size of list: " << newList.size();
    qDebug() << "Size of list: " << collegeList.size();
    showFileLoadedMessage(this, QString::fromStdString(BULK_FILE));
}

