#ifndef SOUVENIRDIALOG_H
#define SOUVENIRDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QHeaderView>
#include "utility.h"
#include <set>
#include <map>

class SouvenirDialog : public QDialog {
    Q_OBJECT

public:
    explicit SouvenirDialog(std::vector<SouvenirData>& souvenirList, QWidget* parent = nullptr);
    std::vector<SouvenirData> getUpdatedSouvenirList() const;

private slots:
    void onCollegeSelectionChanged(int index);
    void onAddRow();
    void onDeleteRow();
    void onSave();
    void onCellChanged(int row, int column);

private:
    void populateColleges();
    void loadSouvenirs(const std::string& college);
    void storeCurrentSouvenirs();
    bool validateRow(int row);
    void formatCostField(int row);

    QComboBox* collegeComboBox;
    QTableWidget* tableWidget;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* saveButton;

    std::vector<SouvenirData>& souvenirList;
    std::map<std::string, std::vector<SouvenirData>> collegeSouvenirs;
    std::string currentCollege;
};

#endif // SOUVENIRDIALOG_H
