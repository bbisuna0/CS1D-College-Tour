#ifndef TRIPPLANNING_H
#define TRIPPLANNING_H

#include <QDialog>
#include "utility.h"

namespace Ui {
class tripplanning;
}

/**
 * @class tripplanning
 * @brief Dialog for planning college trips.
 *
 * This class provides an interface for users to plan trips to different colleges,
 * either using predefined routes or custom trips.
 */
class tripplanning : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the tripplanning dialog.
     * @param parent Optional parent widget.
     */
    explicit tripplanning(QWidget *parent = nullptr);

    /**
     * @brief Constructs the tripplanning dialog with college and souvenir data.
     * @param collegeListParm Reference to a list of available colleges.
     * @param souvenirListParm Reference to a list of souvenirs associated with colleges.
     * @param parent Optional parent widget.
     */
    explicit tripplanning(std::vector<CollegeData>& collegeListParm,
                          std::vector<SouvenirData>& souvenirListParm,
                          QWidget *parent = nullptr);

    /// @brief Destructor for tripplanning.
    ~tripplanning();

private slots:
    /// @brief Handles the event when the exit button is clicked.
    void on_exitButton_clicked();

    /// @brief Plans a trip to Saddleback College.
    void on_visitSBCButton_clicked();

    /// @brief Plans a trip to Arizona State University.
    void on_asuTripButton_clicked();

    /// @brief Plans a trip to the University of California, Irvine.
    void on_uciTripButton_clicked();

    /// @brief Allows the user to plan a custom trip.
    void on_customTripButton_clicked();

private:
    Ui::tripplanning *ui; /**< Pointer to the UI instance of the tripplanning dialog. */
    std::vector<CollegeData> collegeList; /**< List of available colleges for trip planning. */
    std::vector<SouvenirData> souvenirList; /**< List of souvenirs associated with colleges. */
};

#endif // TRIPPLANNING_H
