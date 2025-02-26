#include "tripdisplay.h"
#include "ui_tripdisplay.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>

tripdisplay::tripdisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripdisplay)
{
    ui->setupUi(this);

}

tripdisplay::tripdisplay(const std::vector<CollegeData>& data, float totalDistance, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripdisplay)
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
    ui->label_2->setText(QString::fromStdString("Total Distance Travelled: ") + QString::number(totalDistance, 'f', 2));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);




}




tripdisplay::~tripdisplay()
{
    delete ui;
}

void tripdisplay::on_buttonBox_accepted()
{
    this->close();
}


void tripdisplay::on_saddlebackPB_clicked()
{
    filterTable("Saddleback College");
}

