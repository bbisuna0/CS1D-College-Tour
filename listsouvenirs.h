#ifndef LISTSOUVENIRS_H
#define LISTSOUVENIRS_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>

namespace Ui {
class listsouvenirs;
}

class listsouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit listsouvenirs(QWidget *parent = nullptr);
    explicit listsouvenirs(const std::vector<SouvenirData>& data, QWidget *parent = nullptr);
    ~listsouvenirs();

private:
    Ui::listsouvenirs *ui;
    QStandardItemModel *model;
};

#endif // LISTSOUVENIRS_H
