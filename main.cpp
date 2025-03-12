#include "mainwindow.h"
#include "login.h"
//#include "reguser.h"
#include <QDebug>
#include <QApplication>
#include <QtSql>
#include "main.h"
#include "utility.h"
#include <QMessageBox>
// #include <OpenXLSX/OpenXLSX.hpp>

User myUser;
QSqlDatabase db;
std::vector<CollegeData> collegeList;
std::vector<SouvenirData> souvenirList;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBNAME);

    if(!db.open())
    {
        qDebug() << "Error opening user database";
    }

    bool existingDB = QFile::exists(DBNAME);

    if (!existingDB)
    {}
        //createDB();
    if (!(checkUserTable()))
    {
        qDebug() << "User table not found!\nCreating user table.\n";
        createUserTable();
    }
    //addUser(1,"admin","password", true);
    //addUser(2,"user","user", false);
    //addUser(3,"bernard","bisuna", true);

    login l;
    l.setModal(true);
    l.setWindowFlags(l.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    l.exec();
    /*
    QMessageBox msgBox;
    msgBox.setText("uname: " + myUser.uname);
    msgBox.exec();
    */
    if (!myUser.login_ok)
    {
        a.quit();
        QString connectionName = db.connectionName();
        db.close();
        QSqlDatabase::removeDatabase(connectionName);
        return 0;
    }

    // load college data for distances (default data)
    // collegeList = loadCollegeDataCSV(ORIGINAL_COLLEGE_FILE);
    // souvenirList = loadSouvenirCSV(ORIGINAL_SOUVENIR_FILE);
    collegeList = loadCollegeDataCSV(UPDATED_COLLEGE_FILE);
    souvenirList = loadSouvenirCSV(UPDATED_SOUVENIR_FILE);

    MainWindow w(collegeList, souvenirList, nullptr);
    //w.show();
    w.showNormal();
    int result = a.exec();
    w.close();
    QString connectionName = db.connectionName();
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
    exit(result);
}
