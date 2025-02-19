#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <QDebug>
#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>

void createUserTable(); // QSqlDatabase &db
bool checkUserTable(); // check if user table exists
void addUser(int ID, QString username, QString password, bool admin); // add user data into database
bool checkPassword(QString uname, QString pass, bool &admin, QString &uid); // check if user table exists
QString getTeamID(QString team);


extern QSqlDatabase db;

#endif // UTILITY_H
