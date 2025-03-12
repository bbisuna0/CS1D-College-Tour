#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QDialog>
#include "ui_maintenance.h"
#include "utility.h"

namespace Ui {
class maintenance;
}

/**
 * @class maintenance
 * @brief Dialog for managing and maintaining college and souvenir data.
 *
 * This class provides an interface to load, edit, and save college and
 * souvenir data within the application.
 */
class maintenance : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the maintenance dialog.
     * @param collegeListParm Reference to a list of college data.
     * @param souvenirListParm Reference to a list of souvenir data.
     * @param parent Optional parent widget.
     */
    explicit maintenance(std::vector<CollegeData>& collegeListParm,
                         std::vector<SouvenirData>& souvenirListParm,
                         QWidget *parent = nullptr);

    /// @brief Destructor for maintenance.
    ~maintenance();

private slots:
    /// @brief Handles the event when the exit button is clicked.
    void on_exitButton_clicked();

    /// @brief Loads the original college data.
    void on_loadOrgCollegeDataButton_clicked();

    /// @brief Loads the original souvenir data.
    void on_loadOrgSouvenirDataButton_clicked();

    /// @brief Loads bulk data into the system.
    void on_loadBulkDataButton_clicked();

    /// @brief Opens the college data editor.
    void on_editCollegeDataButton_clicked();

    /// @brief Opens the souvenir data editor.
    void on_editSouvenirDataButton_clicked();

    /// @brief Saves the current college data to a file.
    void on_saveCollegeDataButton_clicked();

    /// @brief Saves the current souvenir data to a file.
    void on_saveSouvenirDataButton_clicked();

    /// @brief Loads the updated college data.
    void on_loadUpdatedCollegeDataButton_clicked();

    /// @brief Loads the updated souvenir data.
    void on_loadUpdatedSouvenirDataButton_clicked();

private:
    Ui::maintenance *ui;  /**< Pointer to the UI instance of the maintenance dialog. */
    std::vector<CollegeData>& collegeList; /**< Reference to the list of college data. */
    std::vector<SouvenirData>& souvenirList; /**< Reference to the list of souvenir data. */
};

#endif // MAINTENANCE_H
