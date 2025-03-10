#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <QDebug>
#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter>
#include <QHeaderView>
#include <unordered_set>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <vector>
#include <string>
#include <set>
#include <QLabel>


struct CollegeData {
    std::string collegeStart;
    std::string collegeEnd;
    float distance;

    bool operator==(const CollegeData& other) const {
        return collegeStart == other.collegeStart && collegeEnd == other.collegeEnd && distance == other.distance;
    }
};

namespace std {
template <>
struct hash<CollegeData> {
    std::size_t operator()(const CollegeData& data) const {
        std::size_t h1 = std::hash<std::string>{}(data.collegeStart);
        std::size_t h2 = std::hash<std::string>{}(data.collegeEnd);
        std::size_t h3 = std::hash<float>{}(data.distance);
        return h1 ^ (h2 << 1) ^ (h3 << 2); // Combine the hashes
    }
};
}

struct SouvenirData {
    std::string college;
    std::string souvenir;
    std::string cost;
};

struct SouvenirPurchase {
    std::string college;
    std::string souvenir;
    std::string cost;
    int quantity;
};

const std::string ORIGINAL_COLLEGE_FILE = "college_original.csv";
const std::string ORIGINAL_SOUVENIR_FILE = "souvenir_original.csv";
const std::string UPDATED_COLLEGE_FILE = "college_updated.csv";
const std::string UPDATED_SOUVENIR_FILE = "souvenir_updated.csv";
const std::string BULK_FILE = "college_bulk.csv";

void createUserTable(); // QSqlDatabase &db
bool checkUserTable(); // check if user table exists
void addUser(int ID, QString username, QString password, bool admin); // add user data into database
bool checkPassword(QString uname, QString pass, bool &admin, QString &uid); // check if user table exists
float stringToFloatDollar(std::string str);
QString getTeamID(QString team);
std::string trim(const std::string& str);
std::vector<CollegeData> loadCollegeDataCSV(const std::string& filename);
std::vector<CollegeData> loadCollegeDataCSV(const std::string& filename, std::vector<CollegeData>& data);
std::vector<SouvenirData> loadSouvenirCSV(const std::string& filename);
float findClosestCollege(const std::string& currentCollege, std::vector<CollegeData>& data, std::unordered_set<std::string>& visitedCampuses, int& nextIndex) ;
std::vector<CollegeData> planEfficientRoute(const std::string startCollege, std::vector<CollegeData> data, int stops, float& distance);
std::vector<CollegeData> planShortestTrip(const std::string& startCollege, std::vector<CollegeData> data, int numStops, float& totalDistance);
float findClosestCollege2(const std::string& currentCollege, std::vector<CollegeData>& data, std::unordered_set<std::string>& visitedCampuses, int& nextIndex, const std::unordered_set<std::string>& collegesToVisit);
std::vector<CollegeData> planEfficientTrip(const QStringList& collegesToVisit, std::vector<CollegeData> data, float& totalDistance);
bool isCollegeMatch(QStandardItemModel* model, const QString& searchValue);
void showFileLoadedMessage(QWidget* parent, const QString filename);
void showFileSavedMessage(QWidget* parent, const QString filename);
void saveCollegeListToCSV(const std::vector<CollegeData>& collegeList, const std::string& filename);
void saveSouvenirListToCSV(const std::vector<SouvenirData>& souvenirList, const std::string& filename);



extern QSqlDatabase db;

class CollegeSelectionDialog : public QDialog {
public:
    CollegeSelectionDialog(const std::vector<CollegeData>& data, QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Colleges to Visit");

        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        QHBoxLayout* listLayout = new QHBoxLayout();

        availableList = new QListWidget();
        selectedList = new QListWidget();

        listLayout->addWidget(availableList);
        listLayout->addWidget(selectedList);

        mainLayout->addLayout(listLayout);

        QHBoxLayout* buttonLayout = new QHBoxLayout();

        addButton = new QPushButton("Add");
        removeButton = new QPushButton("Remove");
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(removeButton);
        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout->addLayout(buttonLayout);

        connect(addButton, &QPushButton::clicked, this, &CollegeSelectionDialog::addSelected);
        connect(removeButton, &QPushButton::clicked, this, &CollegeSelectionDialog::removeSelected);
        connect(okButton, &QPushButton::clicked, this, &CollegeSelectionDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &CollegeSelectionDialog::reject);

        populateAvailableList(data);
    }

    QStringList getSelectedColleges() const {
        QStringList selected;
        for (int i = 0; i < selectedList->count(); ++i) {
            selected.append(selectedList->item(i)->text());
        }
        return selected;
    }

private:
    void populateAvailableList(const std::vector<CollegeData>& data) {
        std::set<std::string> uniqueColleges;
        for (const auto& college : data) {
            uniqueColleges.insert(college.collegeStart);
            uniqueColleges.insert(college.collegeEnd);
        }

        for (const auto& college : uniqueColleges) {
            availableList->addItem(QString::fromStdString(college));
        }
    }

    void addSelected() {
        QListWidgetItem* item = availableList->currentItem();
        if (item) {
            selectedList->addItem(item->clone());
            delete availableList->takeItem(availableList->currentRow());
        }
    }

    void removeSelected() {
        QListWidgetItem* item = selectedList->currentItem();
        if (item) {
            availableList->addItem(item->clone());
            delete selectedList->takeItem(selectedList->currentRow());
        }
    }

    QListWidget* availableList;
    QListWidget* selectedList;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* okButton;
    QPushButton* cancelButton;
};

class PurchaseSummaryDialog : public QDialog {
public:
    PurchaseSummaryDialog(QStandardItemModel* model, QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Purchase Summary");
        resize(650, 400); // Increase dialog size to fit data

        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        tableView = new QTableView(this);
        tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        mainLayout->addWidget(tableView);

        summaryModel = new QStandardItemModel(this);
        summaryModel->setHorizontalHeaderLabels({"College", "Total Purchases ($)"});
        tableView->setModel(summaryModel);

        grandTotalLabel = new QLabel(this);
        grandTotalLabel->setAlignment(Qt::AlignCenter);
        grandTotalLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
        mainLayout->addWidget(grandTotalLabel);

        calculateSummary(model);

        // Set column widths
        tableView->setColumnWidth(0, 400); // School column
        tableView->setColumnWidth(1, 180); // Total Purchases column

        // Connect itemChanged signal to update summary dynamically
        connect(model, &QStandardItemModel::itemChanged, this, &PurchaseSummaryDialog::onItemChanged);
    }

private:
    float stringToFloatDollar(const QString& str) {
        QString modifiedStr = str.trimmed();
        if (!modifiedStr.isEmpty() && modifiedStr[0] == '$') {
            modifiedStr.remove(0, 1); // Remove dollar sign
        }
        bool ok;
        float result = modifiedStr.toFloat(&ok);
        return ok ? result : 0.0f; // Return 0.0 if conversion fails
    }

    void calculateSummary(QStandardItemModel* model) {
        if (!model) return;

        QMap<QString, float> schoolTotals;
        float grandTotal = 0.0f;

        QString currentSchool; // Keep track of the last valid college name

        for (int row = 0; row < model->rowCount(); ++row) {
            QStandardItem* schoolItem = model->item(row, 0);
            QStandardItem* souvenirItem = model->item(row, 1);
            QStandardItem* costItem = model->item(row, 2);
            QStandardItem* quantityItem = model->item(row, 3);

            if (!costItem || !quantityItem) continue; // Skip invalid rows

            // If the college name exists, update our tracking variable
            QString school = schoolItem ? schoolItem->text().trimmed() : "";
            if (!school.isEmpty()) {
                currentSchool = school; // Store the latest valid school name
            }

            // Skip invalid rows (must have a valid school & souvenir)
            if (currentSchool.isEmpty() || !souvenirItem) continue;

            float cost = stringToFloatDollar(costItem->text());

            // Get latest quantity entered
            bool ok;
            int quantity = quantityItem->text().toInt(&ok);
            if (!ok || quantity < 0) quantity = 0; // Prevent invalid/negative values

            float totalPurchase = cost * quantity;
            schoolTotals[currentSchool] += totalPurchase;
            grandTotal += totalPurchase;
        }

        // Clear and repopulate summary table
        summaryModel->clear();
        summaryModel->setHorizontalHeaderLabels({"School", "Total Purchases ($)"});

        for (auto it = schoolTotals.constBegin(); it != schoolTotals.constEnd(); ++it) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(it.key())); // School name
            rowItems.append(new QStandardItem(QString("$%1").arg(QString::number(it.value(), 'f', 2)))); // Total purchase
            summaryModel->appendRow(rowItems);
        }

        // Display Grand Total
        grandTotalLabel->setText(QString("Grand Total: $%1").arg(QString::number(grandTotal, 'f', 2)));
    }



    void onItemChanged(QStandardItem* item) {
        if (item->column() == 3) { // Only react to quantity changes
            calculateSummary(item->model()); // Recalculate totals with updated data
        }
    }

    QTableView* tableView;
    QStandardItemModel* summaryModel;
    QLabel* grandTotalLabel;
};




#endif // UTILITY_H
