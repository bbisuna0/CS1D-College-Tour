#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <QDebug>
#include <QApplication>
#include <QtSql>
#include "utility.h"

class User {
public:
    QString uname;
    bool admin;
    bool login_ok;
    QString uid;
};

extern User myUser;
extern QSqlDatabase db;
const QString DBNAME = "college.db";

#endif // MAIN_H
