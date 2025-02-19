#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

namespace Ui {
class register1;
}

class register1 : public QDialog
{
    Q_OBJECT

public:
    explicit register1(QWidget *parent = nullptr);
    ~register1();

private:
    Ui::register1 *ui;
};

#endif // REGISTER_H
