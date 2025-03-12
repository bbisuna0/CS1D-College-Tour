#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "main.h"

/// Global instance representing the logged-in user.
extern User myUser;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The main window of the application.
 *
 * This class represents the main interface for the application, providing
 * functionalities to interact with college and souvenir data.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow object.
     * @param collegeListParm Reference to a list of college data.
     * @param souvenirListParm Reference to a list of souvenir data.
     * @param parent Optional parent widget.
     */
    explicit MainWindow(std::vector<CollegeData>& collegeListParm,
                        std::vector<SouvenirData>& souvenirListParm,
                        QWidget *parent = nullptr);

    /// @brief Destructor for MainWindow.
    ~MainWindow();

private slots:
    /// @brief Handles the event when pushButton_6 is clicked.
    void on_pushButton_6_clicked();

    /// @brief Handles the event when the college distance button is clicked.
    void on_collegeDistanceButton_clicked();

    /// @brief Handles the event when pushButton_4 is clicked.
    void on_pushButton_4_clicked();

    /// @brief Handles the event when the souvenir button is clicked.
    void on_souvenirButton_clicked();

    /// @brief Handles the event when pushButton_5 is clicked.
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;  /**< Pointer to the UI instance. */
    std::vector<CollegeData>& collegeList; /**< Reference to the list of college data. */
    std::vector<SouvenirData>& souvenirList; /**< Reference to the list of souvenir data. */
};

#endif // MAINWINDOW_H
