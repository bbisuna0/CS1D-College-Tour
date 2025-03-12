#ifndef COLLEGEDISTANCES_H
#define COLLEGEDISTANCES_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class collegedistances;
}

/**
 * @class collegedistances
 * @brief Dialog for displaying and filtering college distances.
 *
 * This class provides a user interface for viewing college distance data
 * and filtering it based on user input.
 */
class collegedistances : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the collegedistances dialog.
     * @param parent Optional parent widget.
     */
    explicit collegedistances(QWidget *parent = nullptr);

    /**
     * @brief Constructs the collegedistances dialog with college data.
     * @param data Reference to a list of college data.
     * @param parent Optional parent widget.
     */
    explicit collegedistances(std::vector<CollegeData>& data, QWidget *parent = nullptr);

    /// @brief Destructor for collegedistances.
    ~collegedistances();

private slots:
    /// @brief Handles the event when the accept button in the button box is clicked.
    void on_buttonBox_accepted();

    /// @brief Handles the event when the Saddleback button is clicked.
    void on_saddlebackPB_clicked();

public slots:
    /**
     * @brief Filters the table based on user input.
     * @param filter The filter string used for searching.
     */
    void filterTable(QString filter) {
        QString filterString = filter;
        QRegExp regex(QRegExp::escape(filterString), Qt::CaseSensitive, QRegExp::FixedString);
        proxyModel->setFilterKeyColumn(0); // Filter by column 0
        proxyModel->setFilterRegExp(regex);
    }

private:
    Ui::collegedistances *ui;  /**< Pointer to the UI instance of the collegedistances dialog. */
    QStandardItemModel *model; /**< Pointer to the table model for displaying college distances. */
    QSortFilterProxyModel *proxyModel; /**< Proxy model for filtering table data. */
};

#endif // COLLEGEDISTANCES_H
