#ifndef REGUSER_H
#define REGUSER_H

#include <QDialog>

namespace Ui {
class reguser;
}

class reguser : public QDialog
{
    Q_OBJECT

public:
    explicit reguser(QWidget *parent = nullptr);
    ~reguser();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::reguser *ui;
};

#endif // REGUSER_H
