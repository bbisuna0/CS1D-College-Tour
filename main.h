#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <QDebug>
#include <QApplication>
#include <QtSql>
#include "utility.h"

/**
 * @class User
 * @brief Represents a user in the system.
 *
 * This class stores user-related information, including username,
 * administrative status, login status, and user ID.
 */
class User {
public:
    QString uname;  /**< The username of the user. */
    bool admin;     /**< Indicates whether the user has administrative privileges. */
    bool login_ok;  /**< Indicates whether the user has successfully logged in. */
    QString uid;    /**< The unique identifier of the user. */
};

/// Global instance of the User class representing the currently logged-in user.
extern User myUser;

/// Global database connection instance.
extern QSqlDatabase db;

/// Constant representing the database name.
const QString DBNAME = "college.db";

#endif // MAIN_H
