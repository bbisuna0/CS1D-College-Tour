#include "collegedistances.h"
#include "ui_collegedistances.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>

collegedistances::collegedistances(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::collegedistances)
{
    ui->setupUi(this);

}

collegedistances::collegedistances(const std::vector<CollegeData>& data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::collegedistances)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    //ui->tableView->setModel(model);


    model->setHorizontalHeaderLabels({"College Start", "College End", "Distance"});

    // Populate Table
    for (const auto& entry : data) {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(QString::fromStdString(entry.collegeStart)));
        rowItems.append(new QStandardItem(QString::fromStdString(entry.collegeEnd)));
        rowItems.append(new QStandardItem(QString::number(entry.distance, 'f', 2)));
        model->appendRow(rowItems);
    }

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);

    ui->tableView->setColumnWidth(0, 400);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);




}




collegedistances::~collegedistances()
{
    delete ui;
}

void collegedistances::on_buttonBox_accepted()
{
    this->close();
}


void collegedistances::on_saddlebackPB_clicked()
{
    filterTable("Saddleback College");
}

