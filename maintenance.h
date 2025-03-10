#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDialog>
#include "ui_maintenance.h"
#include "utility.h"

namespace Ui {
class maintenance;
}

class maintenance : public QDialog
{
    Q_OBJECT

public:
    // explicit maintenance(QWidget *parent = nullptr);
    explicit maintenance(std::vector<CollegeData>& collegeListParm, std::vector<SouvenirData>& souvenirListParm, QWidget *parent = nullptr);
    ~maintenance();

private slots:
    void on_exitButton_clicked();

    void on_loadOrgCollegeDataButton_clicked();

    void on_loadOrgSouvenirDataButton_clicked();

    void on_loadBulkDataButton_clicked();

    void on_editCollegeDataButton_clicked();

    void on_editSouvenirDataButton_clicked();

    void on_saveCollegeDataButton_clicked();

    void on_saveSouvenirDataButton_clicked();

    void on_loadUpdatedCollegeDataButton_clicked();

    void on_loadUpdatedSouvenirDataButton_clicked();

private:
    Ui::maintenance *ui;
    std::vector<CollegeData>& collegeList;
    std::vector<SouvenirData>& souvenirList;
};

#endif // MAINTENANCE_H
