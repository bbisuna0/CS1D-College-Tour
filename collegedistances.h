#ifndef COLLEGEDISTANCES_H
#define COLLEGEDISTANCES_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class collegedistances;
}

class collegedistances : public QDialog
{
    Q_OBJECT

public:
    explicit collegedistances(QWidget *parent = nullptr);
    explicit collegedistances(std::vector<CollegeData>& data, QWidget *parent = nullptr);
    ~collegedistances();

private slots:
    void on_buttonBox_accepted();

    void on_saddlebackPB_clicked();

public slots:
    void filterTable(QString filter) {
        QString filterString = filter;
        QRegExp regex(QRegExp::escape(filterString), Qt::CaseSensitive, QRegExp::FixedString);
        proxyModel->setFilterKeyColumn(0); // Filter by column 0
        proxyModel->setFilterRegExp(regex);
    }

private:
    Ui::collegedistances *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
};


#endif // COLLEGEDISTANCES_H
