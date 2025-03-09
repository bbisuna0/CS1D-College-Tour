#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "main.h"

extern User myUser;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(std::vector<CollegeData>& collegeListParm, std::vector<SouvenirData>& souvenirListParm, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_6_clicked();

    void on_collegeDistanceButton_clicked();

    void on_pushButton_4_clicked();

    void on_souvenirButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<CollegeData>& collegeList;
    std::vector<SouvenirData>& souvenirList;
};
#endif // MAINWINDOW_H
