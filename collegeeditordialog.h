#ifndef COLLEGEEDITORDIALOG_H
#define COLLEGEEDITORDIALOG_H

#include <QDialog>
#include <vector>
#include "utility.h"  // Ensure this contains the CollegeData struct

namespace Ui {
class CollegeEditorDialog;
}

/**
 * @class CollegeEditorDialog
 * @brief Dialog for editing college data.
 *
 * This class provides a user interface for adding, deleting, and modifying
 * college data entries.
 */
class CollegeEditorDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the CollegeEditorDialog.
     * @param collegeList Reference to a list of college data.
     * @param parent Optional parent widget.
     */
    explicit CollegeEditorDialog(std::vector<CollegeData>& collegeList, QWidget *parent = nullptr);

    /// @brief Destructor for CollegeEditorDialog.
    ~CollegeEditorDialog();

private slots:
    /// @brief Handles the event when the add button is clicked.
    void on_addButton_clicked();

    /// @brief Handles the event when the delete button is clicked.
    void on_deleteButton_clicked();

    /// @brief Handles the event when the save button is clicked.
    void on_saveButton_clicked();

    /**
     * @brief Validates a table cell when edited.
     * @param row The row of the edited cell.
     * @param column The column of the edited cell.
     */
    void validateCell(int row, int column);

private:
    Ui::CollegeEditorDialog *ui; /**< Pointer to the UI instance. */
    std::vector<CollegeData>& collegeList; /**< Reference to the original list of college data. */

    /// @brief Populates the table with existing college data.
    void loadTable();
};

#endif // COLLEGEEDITORDIALOG_H
