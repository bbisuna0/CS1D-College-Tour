#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include <QDebug>
#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter>
#include <QHeaderView>
#include <unordered_set>

struct CollegeData {
    std::string collegeStart;
    std::string collegeEnd;
    float distance;
};

struct SouvenirData {
    std::string college;
    std::string souvenir;
    std::string cost;
};

void createUserTable(); // QSqlDatabase &db
bool checkUserTable(); // check if user table exists
void addUser(int ID, QString username, QString password, bool admin); // add user data into database
bool checkPassword(QString uname, QString pass, bool &admin, QString &uid); // check if user table exists
QString getTeamID(QString team);
std::string trim(const std::string& str);
std::vector<CollegeData> loadCollegeDataCSV(const std::string& filename);
std::vector<SouvenirData> loadSouvenirCSV(const std::string& filename);
float findClosestCollege(const std::string& currentCollege, std::vector<CollegeData>& data, std::unordered_set<std::string>& visitedCampuses, int& nextIndex) ;
std::vector<CollegeData> planEfficientRoute(const std::string startCollege, std::vector<CollegeData> data, int stops, float& distance);
std::vector<CollegeData> planShortestTrip(const std::string& startCollege, std::vector<CollegeData> data, int numStops, float& totalDistance);



extern QSqlDatabase db;





#endif // UTILITY_H
