#include "listsouvenirs.h"
#include "ui_listsouvenirs.h"
#include "mergedtableview.h"
#include <QStandardItemModel>

listsouvenirs::listsouvenirs(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::listsouvenirs)
{
    ui->setupUi(this);
}


listsouvenirs::listsouvenirs(const std::vector<SouvenirData>& data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::listsouvenirs)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    //ui->tableView->setModel(model);


    model->setHorizontalHeaderLabels({"College", "Souvenir", "Cost"});

    //Populate Table
    for (const auto& entry : data) {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(QString::fromStdString(entry.college)));
        rowItems.append(new QStandardItem(QString::fromStdString(entry.souvenir)));
        rowItems.append(new QStandardItem(QString::fromStdString(entry.cost)));
        qDebug() << QString::fromStdString(entry.college);
        qDebug() << QString::fromStdString(entry.souvenir);
        qDebug() << QString::fromStdString(entry.cost);
        model->appendRow(rowItems);
    }

    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(0, 400);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);




}




listsouvenirs::~listsouvenirs()
{
    delete ui;
}
