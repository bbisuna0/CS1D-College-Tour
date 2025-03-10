#include "collegeeditordialog.h"
#include "ui_collegeeditordialog.h"
#include <QMessageBox>

CollegeEditorDialog::CollegeEditorDialog(std::vector<CollegeData>& collegeList, QWidget *parent)
    : QDialog(parent), ui(new Ui::CollegeEditorDialog), collegeList(collegeList)
{
    ui->setupUi(this);
    resize(970, 400);
    loadTable();  // Load data into the table
    connect(ui->collegeTableWidget, &QTableWidget::cellChanged, this, &CollegeEditorDialog::validateCell);

}

CollegeEditorDialog::~CollegeEditorDialog()
{
    delete ui;
}

void CollegeEditorDialog::loadTable()
{
    ui->collegeTableWidget->clear();  // Ensure no previous data remains
    ui->collegeTableWidget->setRowCount(collegeList.size());
    ui->collegeTableWidget->setColumnCount(3);  // Set correct column count

    // Set column headers
    QStringList headers;
    headers << "Start College" << "End College" << "Distance (miles)";
    ui->collegeTableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with existing data
    for (int i = 0; i < static_cast<int>(collegeList.size()); ++i)
    {
        // Create QTableWidgetItems to store data in table cells
        QTableWidgetItem* startItem = new QTableWidgetItem(QString::fromStdString(collegeList[i].collegeStart));
        QTableWidgetItem* endItem = new QTableWidgetItem(QString::fromStdString(collegeList[i].collegeEnd));
        QTableWidgetItem* distanceItem = new QTableWidgetItem(QString::number(collegeList[i].distance));

        // Make cells editable
        startItem->setFlags(startItem->flags() | Qt::ItemIsEditable);
        endItem->setFlags(endItem->flags() | Qt::ItemIsEditable);
        distanceItem->setFlags(distanceItem->flags() | Qt::ItemIsEditable);

        // Set items in the table
        ui->collegeTableWidget->setItem(i, 0, startItem);
        ui->collegeTableWidget->setItem(i, 1, endItem);
        ui->collegeTableWidget->setItem(i, 2, distanceItem);
    }

    ui->collegeTableWidget->resizeColumnsToContents();  // Adjust column width to fit content
}


void CollegeEditorDialog::on_addButton_clicked()
{
    int row = ui->collegeTableWidget->rowCount();
    ui->collegeTableWidget->insertRow(row);
}

void CollegeEditorDialog::on_deleteButton_clicked()
{
    int row = ui->collegeTableWidget->currentRow();
    if (row >= 0)
    {
        ui->collegeTableWidget->removeRow(row);
    }
}

void CollegeEditorDialog::on_saveButton_clicked()
{
    collegeList.clear();  // Clear original data and replace with table contents

    int rowCount = ui->collegeTableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        QTableWidgetItem* startItem = ui->collegeTableWidget->item(i, 0);
        QTableWidgetItem* endItem = ui->collegeTableWidget->item(i, 1);
        QTableWidgetItem* distanceItem = ui->collegeTableWidget->item(i, 2);

        // Validate: Ensure no empty fields
        if (!startItem || startItem->text().trimmed().isEmpty() ||
            !endItem || endItem->text().trimmed().isEmpty() ||
            !distanceItem || distanceItem->text().trimmed().isEmpty())
        {
            QMessageBox::warning(this, "Invalid Entry", "All fields must be filled!");
            return;  // Stop saving and prompt the user
        }

        // Validate: Ensure distance is a valid number
        bool isNumeric;
        float distance = distanceItem->text().toFloat(&isNumeric);
        if (!isNumeric || distance < 0)
        {
            QMessageBox::warning(this, "Invalid Distance", "Distance must be a positive number!");
            return;  // Stop saving
        }

        // Store the validated data in collegeList
        CollegeData college;
        college.collegeStart = startItem->text().toStdString();
        college.collegeEnd = endItem->text().toStdString();
        college.distance = distance;

        collegeList.push_back(college);
    }

    accept();  // Close the dialog and save changes
}


void CollegeEditorDialog::validateCell(int row, int column)
{
    QTableWidgetItem* item = ui->collegeTableWidget->item(row, column);
    if (item && item->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Invalid Input", "Fields cannot be left empty!");
        item->setText("N/A");  // Reset to a default value
    }
}



