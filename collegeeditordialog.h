#ifndef COLLEGEEDITORDIALOG_H
#define COLLEGEEDITORDIALOG_H

#include <QDialog>
#include <vector>
#include "utility.h"  // Ensure this contains the CollegeData struct

namespace Ui {
class CollegeEditorDialog;
}

class CollegeEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CollegeEditorDialog(std::vector<CollegeData>& collegeList, QWidget *parent = nullptr);
    ~CollegeEditorDialog();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_saveButton_clicked();
    void validateCell(int row, int column);


private:
    Ui::CollegeEditorDialog *ui;
    std::vector<CollegeData>& collegeList;  // Reference to the original list

    void loadTable();  // Populate the table with existing data
};

#endif // COLLEGEEDITORDIALOG_H
