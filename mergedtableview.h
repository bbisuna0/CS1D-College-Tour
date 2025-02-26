#ifndef MERGEDTABLEVIEW_H
#define MERGEDTABLEVIEW_H

#include <QDebug>
#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter>
#include <QHeaderView>

class MergedTableView : public QTableView {
public:
    MergedTableView(QWidget *parent = nullptr) : QTableView(parent) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        QTableView::paintEvent(event);

        QPainter painter(viewport());
        painter.setRenderHint(QPainter::Antialiasing);

        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(this->model());
        if (!model) return;

        int mergeColumn = 0; // Column to merge by (adjust as needed)
        QString previousValue;
        int mergeStartRow = -1;

        for (int row = 0; row < model->rowCount(); ++row) {
            QString currentValue = model->item(row, mergeColumn) ? model->item(row, mergeColumn)->text() : "";

            if (row == 0) {
                previousValue = currentValue;
                mergeStartRow = 0;
                continue;
            }

            if (currentValue.isEmpty()) {
                continue;
            }

            if (currentValue != previousValue) {
                if (row - mergeStartRow > 1) {
                    mergeCells(mergeColumn, mergeStartRow, row - 1);
                }
                previousValue = currentValue;
                mergeStartRow = row;
            } else if (row == model->rowCount() - 1) {
                if (row - mergeStartRow + 1 > 1) {
                    mergeCells(mergeColumn, mergeStartRow, row);
                }
            }
        }
    }

private:
    void mergeCells(int column, int startRow, int endRow) {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(this->model());
        if (!model) return;

        QModelIndex topIndex = model->index(startRow, column);
        QModelIndex bottomIndex = model->index(endRow, column);
        QRect mergeRect = visualRect(topIndex).united(visualRect(bottomIndex));

        model->setData(topIndex, model->data(topIndex).toString());
        for (int row = startRow + 1; row <= endRow; ++row) {
            model->setData(model->index(row, column), "");
        }
    }
};

#endif // MERGEDTABLEVIEW_H
