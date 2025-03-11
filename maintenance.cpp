#include "utility.h"
#include "maintenance.h"
#include <QInputDialog>
#include "collegeeditordialog.h"
#include "souvenirdialog.h"

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


void maintenance::on_editCollegeDataButton_clicked()
{
    CollegeEditorDialog editor(collegeList, this);
    if (editor.exec() == QDialog::Accepted) {
        // Changes are saved automatically as we passed by reference
    }
}


void maintenance::on_editSouvenirDataButton_clicked()
{
    // Create and show the souvenir dialog
    SouvenirDialog dialog(souvenirList, this);
    dialog.exec();
}


void maintenance::on_saveCollegeDataButton_clicked()
{
    // UPDATED_COLLEGE_FILE
    saveCollegeListToCSV(collegeList, UPDATED_COLLEGE_FILE);
    showFileSavedMessage(this, QString::fromStdString(UPDATED_COLLEGE_FILE));
}


void maintenance::on_saveSouvenirDataButton_clicked()
{
    // UPDATED_COLLEGE_FILE
    saveSouvenirListToCSV(souvenirList, UPDATED_SOUVENIR_FILE);
    showFileSavedMessage(this, QString::fromStdString(UPDATED_SOUVENIR_FILE));
}


void maintenance::on_loadUpdatedCollegeDataButton_clicked()
{
    collegeList.clear();
    collegeList = loadCollegeDataCSV(UPDATED_COLLEGE_FILE);
    showFileLoadedMessage(this, QString::fromStdString(UPDATED_COLLEGE_FILE));
}


void maintenance::on_loadUpdatedSouvenirDataButton_clicked()
{
    // load souvenir data for distances (default data)
    souvenirList.clear();
    souvenirList = loadSouvenirCSV(UPDATED_SOUVENIR_FILE);
    showFileLoadedMessage(this, QString::fromStdString(UPDATED_SOUVENIR_FILE));
}

