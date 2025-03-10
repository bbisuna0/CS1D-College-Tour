#include "souvenirdisplay.h".h"
#include <QDoubleValidator>
#include <QDebug>

SouvenirDisplay::SouvenirDisplay(std::vector<SouvenirData>& souvenirList, QWidget* parent)
    : QDialog(parent), souvenirList(souvenirList) {

    setWindowTitle("Edit Souvenirs");
    resize(450, 400);

    // Layouts
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // Combo Box for Colleges
    collegeComboBox = new QComboBox(this);
    connect(collegeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SouvenirDisplay::onCollegeSelectionChanged);
    mainLayout->addWidget(collegeComboBox);

    // Table Widget
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Souvenir", "Cost"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    connect(tableWidget, &QTableWidget::cellChanged, this, &SouvenirDisplay::onCellChanged);
    mainLayout->addWidget(tableWidget);

    // Buttons
    saveButton = new QPushButton("Exit", this);

    connect(saveButton, &QPushButton::clicked, this, &SouvenirDisplay::onSave);

    buttonLayout->addWidget(saveButton);
    mainLayout->addLayout(buttonLayout);

    // Populate colleges and souvenirs
    populateColleges();

    // Ensure first selection loads souvenirs
    if (!collegeComboBox->currentText().isEmpty()) {
        currentCollege = collegeComboBox->currentText().toStdString();
        loadSouvenirs(currentCollege);  // Load souvenirs for the initially selected college
    }
}

void SouvenirDisplay::populateColleges() {
    std::set<std::string> collegeNames;

    // Extract unique college names from souvenirList
    for (const auto& souvenir : souvenirList) {
        collegeNames.insert(souvenir.college);
    }

    // Populate combo box
    for (const auto& college : collegeNames) {
        collegeComboBox->addItem(QString::fromStdString(college));
    }

    // Group souvenirs by college
    for (const auto& souvenir : souvenirList) {
        collegeSouvenirs[souvenir.college].push_back(souvenir);
    }

    if (!collegeNames.empty()) {
        collegeComboBox->setCurrentIndex(0);
    }
}

void SouvenirDisplay::onCollegeSelectionChanged(int index) {
    storeCurrentSouvenirs();
    currentCollege = collegeComboBox->currentText().toStdString();
    loadSouvenirs(currentCollege);
}

void SouvenirDisplay::loadSouvenirs(const std::string& college) {
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    if (collegeSouvenirs.find(college) != collegeSouvenirs.end()) {
        for (const auto& souvenir : collegeSouvenirs[college]) {
            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(souvenir.souvenir)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(souvenir.cost)));
        }
    }
}

void SouvenirDisplay::storeCurrentSouvenirs() {
    if (currentCollege.empty()) return;

    std::vector<SouvenirData> updatedList;
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        if (validateRow(row)) {
            SouvenirData data;
            data.college = currentCollege;
            data.souvenir = tableWidget->item(row, 0)->text().toStdString();
            data.cost = tableWidget->item(row, 1)->text().toStdString();
            updatedList.push_back(data);
        }
    }
    collegeSouvenirs[currentCollege] = updatedList;
}

void SouvenirDisplay::onAddRow() {
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(""));
    tableWidget->setItem(row, 1, new QTableWidgetItem("$0.00"));
}

void SouvenirDisplay::onDeleteRow() {
    int row = tableWidget->currentRow();
    if (row >= 0) {
        tableWidget->removeRow(row);
    }
}

void SouvenirDisplay::onSave() {
    // storeCurrentSouvenirs();
    // souvenirList.clear();
    // for (const auto& [college, souvenirs] : collegeSouvenirs) {
    //     for (const auto& souvenir : souvenirs) {
    //         souvenirList.push_back(souvenir);
    //     }
    // }
    accept();
}

void SouvenirDisplay::onCellChanged(int row, int column) {
    if (column == 1) {
        formatCostField(row);
    }
}

bool SouvenirDisplay::validateRow(int row) {
    if (!tableWidget->item(row, 0) || tableWidget->item(row, 0)->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Invalid Entry", "Souvenir name cannot be empty.");
        return false;
    }

    if (!tableWidget->item(row, 1) || tableWidget->item(row, 1)->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Invalid Entry", "Cost cannot be empty.");
        return false;
    }

    return true;
}

void SouvenirDisplay::formatCostField(int row) {
    QTableWidgetItem* item = tableWidget->item(row, 1);
    if (!item) return;

    bool ok;
    double cost = item->text().remove('$').toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Entry", "Cost must be a number.");
        return;
    }

    item->setText(QString("$%1").arg(cost, 0, 'f', 2));
}

std::vector<SouvenirData> SouvenirDisplay::getUpdatedSouvenirList() const {
    return souvenirList;
}
