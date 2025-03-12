#ifndef LISTSOUVENIRS_H
#define LISTSOUVENIRS_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>

namespace Ui {
class listsouvenirs;
}

/**
 * @class listsouvenirs
 * @brief Represents the souvenir listing dialog.
 *
 * This class provides a dialog that displays a list of available souvenirs
 * using a table model.
 */
class listsouvenirs : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the listsouvenirs dialog.
     * @param data Reference to a list of souvenir data.
     * @param parent Optional parent widget.
     */
    explicit listsouvenirs(std::vector<SouvenirData>& data, QWidget *parent = nullptr);

    /// @brief Destructor for listsouvenirs.
    ~listsouvenirs();

private slots:
    /// @brief Handles the event when the push button is clicked.
    void on_pushButton_clicked();

private:
    Ui::listsouvenirs *ui;  /**< Pointer to the UI instance of the listsouvenirs dialog. */
    QStandardItemModel *model; /**< Pointer to the table model for displaying souvenirs. */
    std::vector<SouvenirData>& souvenirList; /**< Reference to the list of souvenir data. */
};

#endif // LISTSOUVENIRS_H
