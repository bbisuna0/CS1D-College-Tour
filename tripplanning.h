#ifndef TRIPPLANNING_H
#define TRIPPLANNING_H

#include <QDialog>
#include "utility.h"

namespace Ui {
class tripplanning;
}

class tripplanning : public QDialog
{
    Q_OBJECT

public:
    explicit tripplanning(QWidget *parent = nullptr);
    explicit tripplanning(std::vector<CollegeData>& collegeListParm, std::vector<SouvenirData>& souvenirListParm, QWidget *parent = nullptr);
    ~tripplanning();

private slots:
    void on_exitButton_clicked();

    void on_visitSBCButton_clicked();

    void on_asuTripButton_clicked();

    void on_uciTripButton_clicked();

    void on_customTripButton_clicked();

private:
    Ui::tripplanning *ui;
    std::vector<CollegeData> collegeList;
    std::vector<SouvenirData> souvenirList;
};

#endif // TRIPPLANNING_H
