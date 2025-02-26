#include "utility.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <unordered_set>

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("personnel.dat");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}

void createUserTable() // QSqlDatabase &db
{
    /*
    QString create = "CREATE TABLE if not exists users ("
                     "ID integer,"
                     "username VARCHAR(20),"
                     "password VARCHAR(20));";
    */

    QString create = "CREATE TABLE user ("
        "uid	INTEGER UNIQUE,"
        "uname	TEXT,"
        "pass	TEXT,"
        "admin	INTEGER DEFAULT 0 CHECK(admin >= 0 AND admin <= 1),"
        "PRIMARY KEY(uid AUTOINCREMENT))";

    QSqlQuery query;
    if(!query.exec(create))
    {
        qDebug() << "Error creating table";
    }
    return;
}

bool checkUserTable() // check if user table exists
{
    QString checkUser;
    checkUser = "SELECT name FROM sqlite_master where type='table' AND name='user';";
    QSqlQuery query;
    query.prepare(checkUser);
    if (query.exec()) // found
    {
        return query.next(); // return true if user table found, false if not
    }
    else // error check for table
    {
        qDebug() << query.lastError().text() << endl;
        return false;
    }
}


bool checkUserName(QString uname) // check if user exists
{
    QString checkUserNameQ;
    checkUserNameQ = "SELECT * FROM user where uname=:uname;";
    QSqlQuery query;
    query.prepare(checkUserNameQ);
    query.bindValue(":uname", uname);
    if (query.exec()) // found
    {
        if(query.next())
            return true;
        else
            return false;
    }
    else
        return false;
}


void addUser(int ID, QString username, QString password, bool admin) // add user data into database
{
    if (checkUserName(username))
    {
        QMessageBox::warning(0, QObject::tr("Error Adding User"),
                             "User already exists.");
        return;
    }
    QString addUser = "INSERT INTO user ("
                       "uid, uname, pass, admin)"
                       "VALUES (NULL, :uname , :pass, :admin);";
    QSqlQuery query;
    query.prepare(addUser);
    qDebug() << "created " << ID;
    //query.bindValue(":id", ID);  // auto-increment
    query.bindValue(":uname", username);
    query.bindValue(":pass", password);
    if (admin)
        query.bindValue(":admin", 1);
    else
        query.bindValue(":admin", 0);
    //qDebug() << query.boundValue(":pass");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << endl;
        qDebug() << "Error adding " << username << " to users";

    }
    return;
}


bool checkPassword(QString uname, QString pass, bool &admin, QString &uid) // check if user table exists
{  
    QString checkPassword;
    checkPassword = "SELECT * FROM user where uname=:uname AND pass=:pass;";
    QSqlQuery query;
    query.prepare(checkPassword);
    query.bindValue(":uname", uname);
    query.bindValue(":pass", pass);
    admin = true;
    if (query.exec()) // found
    {
        if (query.next()) {
            uid = query.value(0).toString();
            int i = query.value(3).toInt();
            if (i==1)
                admin = true;
            else
                admin = false;
            return true;
        }
        else
            return false;
    }
    else // error check for table
    {
        qDebug() << query.lastError().text() << endl;
        return false;
    }
}


// Function to trim leading and trailing spaces from a string, preserving spaces inside quotes
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<CollegeData> loadCollegeDataCSV(const std::string& filename) {
    std::vector<CollegeData> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        bool inQuotes = false;
        std::string currentField;

        while (std::getline(ss, field, ',')) {
            if (inQuotes) {
                currentField += (currentField.empty() ? "" : ",") + field; // Add comma if not first part
                if (field.back() == '"') {
                    inQuotes = false;
                    fields.push_back(trim(currentField.substr(0, currentField.length() - 1))); // Trim after closing quote
                    currentField = "";
                }
            } else {
                if (field.front() == '"') {
                    inQuotes = true;
                    currentField = field.substr(1); // Remove starting quote
                } else {
                    fields.push_back(trim(field)); // Trim non-quoted fields
                }
            }
        }

        if (!currentField.empty()) { // Handle the last field if still in quotes
            fields.push_back(trim(currentField));
        }

        if (fields.size() >= 3) {
            try {
                float distance = std::stof(fields[fields.size() - 1]);
                if (fields.size() == 3) {
                    data.push_back({fields[0], fields[1], distance});
                } else if (fields.size() > 3) {
                    std::string collegeEnd = fields[1];
                    for (size_t i = 2; i < fields.size() - 1; ++i) {
                        collegeEnd += ", " + fields[i];
                    }
                    data.push_back({fields[0], collegeEnd, distance});
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Warning: Invalid distance value in line: " << line << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Warning: Distance value out of range in line: " << line << std::endl;
            }
        } else {
            std::cerr << "Warning: Incorrect format in line: " << line << std::endl;
        }
    }

    file.close();
    return data;
}

std::vector<SouvenirData> loadSouvenirCSV(const std::string& filename) {
    std::vector<SouvenirData> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    if (std::getline(file, line)) { // Skip header row
    }

    while (std::getline(file, line)) {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        bool insideQuotes = false;
        std::string currentField;

        while (ss.good()) {
            char c = ss.get();
            if (ss.eof()) break;

            if (c == '"') {
                insideQuotes = !insideQuotes;
            } else if (c == ',' && !insideQuotes) {
                fields.push_back(currentField);
                currentField.clear();
            } else {
                currentField += c;
            }
        }
        fields.push_back(currentField);

        if (fields.size() == 3) {
            data.push_back({fields[0], fields[1], fields[2]});
        }
    }

    file.close();
    return data;
}

float findClosestCollege(const std::string& currentCollege, std::vector<CollegeData>& data, std::unordered_set<std::string>& visitedCampuses, int& nextIndex) {
    float minDistance = std::numeric_limits<float>::max();
    nextIndex = -1;

    for (size_t i = 0; i < data.size(); ++i) {
        if (visitedCampuses.find(data[i].collegeEnd) == visitedCampuses.end() &&
            data[i].collegeStart == currentCollege && data[i].distance < minDistance) {
            minDistance = data[i].distance;
            nextIndex = i;
        }
    }
    return minDistance;
}

std::vector<CollegeData> planEfficientRoute(const std::string startCollege, std::vector<CollegeData> data, int stops, float& totalDistance) {
    std::vector<CollegeData> route;
    std::unordered_set<std::string> visitedCampuses;
    std::string currentCollege = startCollege;
    totalDistance = 0.0;

    for (int i = 0; i <= stops; ++i) {
        int nextIndex;
        float distance = findClosestCollege(currentCollege, data, visitedCampuses, nextIndex);

        if (nextIndex == -1) break; // No more valid colleges to visit

        visitedCampuses.insert(currentCollege); // Mark the current college as visited
        route.push_back(data[nextIndex]);
        totalDistance += distance;
        currentCollege = data[nextIndex].collegeEnd;
    }

    return route;
}

std::vector<CollegeData> planShortestTrip(const std::string& startCollege, std::vector<CollegeData> data, int numStops, float& totalDistance) {
    std::vector<CollegeData> route;
    std::unordered_set<std::string> visitedCampuses;
    std::string currentCollege = startCollege;
    totalDistance = 0.0;

    for (int i = 0; i < numStops; ++i) {
        int nextIndex;
        float distance = findClosestCollege(currentCollege, data, visitedCampuses, nextIndex);

        if (nextIndex == -1) break; // No more valid colleges to visit

        visitedCampuses.insert(currentCollege); // Mark the current college as visited
        route.push_back(data[nextIndex]);
        totalDistance += distance;
        currentCollege = data[nextIndex].collegeEnd;
    }

    return route;
}

