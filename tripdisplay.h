#ifndef TRIPDISPLAY_H
#define TRIPDISPLAY_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class tripdisplay;
}

class tripdisplay : public QDialog
{
    Q_OBJECT

public:
    explicit tripdisplay(QWidget *parent = nullptr);
    explicit tripdisplay(const std::vector<CollegeData>& data, float totalDistance, QWidget *parent = nullptr);
    ~tripdisplay();

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
    Ui::tripdisplay *ui;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
};


#endif // TRIPDISPLAY_H
