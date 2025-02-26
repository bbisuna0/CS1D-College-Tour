#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>

namespace Ui {
class purchasesouvenirs;
}

class purchasesouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit purchasesouvenirs(QWidget *parent = nullptr);
    explicit purchasesouvenirs(const std::vector<SouvenirPurchase>& data, QWidget *parent = nullptr);
    ~purchasesouvenirs();

private slots:
    void on_purchaseButton_clicked();

private:
    Ui::purchasesouvenirs *ui;
    QStandardItemModel *model;
};

#endif // PURCHASESOUVENIRS_H
