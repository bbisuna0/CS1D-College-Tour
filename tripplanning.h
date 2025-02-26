#ifndef TRIPPLANNING_H
#define TRIPPLANNING_H

#include <QDialog>

namespace Ui {
class tripplanning;
}

class tripplanning : public QDialog
{
    Q_OBJECT

public:
    explicit tripplanning(QWidget *parent = nullptr);
    ~tripplanning();

private slots:
    void on_exitButton_clicked();

    void on_visitSBCButton_clicked();

    void on_asuTripButton_clicked();

    void on_uciTripButton_clicked();

private:
    Ui::tripplanning *ui;
};

#endif // TRIPPLANNING_H
