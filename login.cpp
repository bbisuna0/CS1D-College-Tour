#include "login.h"
#include "ui_login.h"
#include "reguser.h"
#include "main.h"
#include "utility.h"
#include <QMessageBox>

extern User myUser;

int login_count = 0;

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_label_5_linkActivated(const QString &link)
{
    reguser r;
    r.show();
}

// void login::on_label_5_linkHovered(const QString &link)
// {
//     reguser r;
//     r.show();
// }

void login::on_pushButton_clicked()
{
    reguser r;
    r.setModal(true);
    r.setWindowFlags(r.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    r.exec();
}

void login::on_buttonBox_accepted()
{
  //QLineEdit::text();
  QString uname = ui->le_username->text();
  QString pass = ui->le_password->text();
  //extern QString curr_uname;
  //extern bool curr_admin;
  bool login_ok = checkPassword(uname, pass, myUser.admin, myUser.uid);
  login_count++;
  if (login_ok)
  {
    myUser.uname = uname;
    myUser.login_ok = true;
    this->close();
  }
  else
  {
    myUser.login_ok = false;
    myUser.admin = false;
    if (login_count > 2)
    {
        QMessageBox::warning(0, QObject::tr("Too many invalid login attempt"),
                             "Too many invalid login attempts.");
        this->close();
    }
  }
}

void login::on_buttonBox_rejected()
{
    myUser.uname = "error";
    myUser.login_ok = false;
    myUser.admin = false;
    this->close();
}
