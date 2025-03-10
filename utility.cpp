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


float stringToFloatDollar(std::string str) {
    std::string modifiedStr = str; // Create a copy to modify

    if (!modifiedStr.empty() && modifiedStr[0] == '$') {
        modifiedStr = modifiedStr.substr(1); // Remove the leading '$'
    }

    std::stringstream ss(modifiedStr);
    float result;

    if (ss >> result) {
        char remaining;
        if (ss >> remaining) {
            throw std::invalid_argument("Invalid float format: trailing characters.");
        }
        return result;
    } else {
        throw std::invalid_argument("Invalid float format: no valid float found.");
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
    std::unordered_set<CollegeData> seen;  // To track unique rows
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
                CollegeData newData;
                if (fields.size() == 3) {
                    newData = {fields[0], fields[1], distance};
                } else if (fields.size() > 3) {
                    std::string collegeEnd = fields[1];
                    for (size_t i = 2; i < fields.size() - 1; ++i) {
                        collegeEnd += ", " + fields[i];
                    }
                    newData = {fields[0], collegeEnd, distance};
                }

                // Only add if not already seen
                if (seen.find(newData) == seen.end()) {
                    data.push_back(newData);
                    seen.insert(newData); // Mark as seen
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


std::vector<CollegeData> loadCollegeDataCSV(const std::string& filename, std::vector<CollegeData>& data) {
    std::unordered_set<CollegeData> seen;  // To track unique rows
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::vector<std::string> fields;
        std::string field;
        bool inQuotes = false;
        std::string currentField;

        // Loop through each character in the line, process based on quote state
        for (size_t i = 0; i < line.size(); ++i) {
            char ch = line[i];

            if (inQuotes) {
                // If inside quotes, accumulate characters in currentField
                currentField += ch;

                // If closing quote is found, close the quoted field
                if (ch == '"') {
                    // Check for the case of two quotes in a row (escaped quote within a quoted string)
                    if (i + 1 < line.size() && line[i + 1] == '"') {
                        currentField += '"'; // Add one quote to the field
                        ++i; // Skip next quote
                    } else {
                        inQuotes = false;
                    }
                }
            } else {
                if (ch == '"') {
                    // Start of quoted field
                    inQuotes = true;
                    currentField.clear(); // Reset the current field to start accumulating data
                } else if (ch == ',') {
                    // End of a non-quoted field, add to fields vector
                    fields.push_back(trim(currentField));
                    currentField.clear(); // Clear the current field
                } else {
                    currentField += ch; // Accumulate characters for the current field
                }
            }
        }

        // Add the last field (after the last comma)
        if (!currentField.empty()) {
            fields.push_back(trim(currentField));
        }

        // Now we need to ensure there are at least 3 fields (start college, end college, and distance)
        if (fields.size() >= 3) {
            try {
                float distance = std::stof(fields[fields.size() - 1]);
                CollegeData newData;
                if (fields.size() == 3) {
                    newData = {fields[0], fields[1], distance};
                } else if (fields.size() > 3) {
                    std::string collegeEnd = fields[1];
                    for (size_t i = 2; i < fields.size() - 1; ++i) {
                        collegeEnd += ", " + fields[i];
                    }
                    newData = {fields[0], collegeEnd, distance};
                }

                // Only add if not already seen
                if (seen.find(newData) == seen.end()) {
                    data.push_back(newData);
                    seen.insert(newData); // Mark as seen
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

float findClosestCollege2(const std::string& currentCollege, std::vector<CollegeData>& data, std::unordered_set<std::string>& visitedCampuses, int& nextIndex, const std::unordered_set<std::string>& collegesToVisit) {
    float minDistance = std::numeric_limits<float>::max();
    nextIndex = -1;

    for (size_t i = 0; i < data.size(); ++i) {
        if (visitedCampuses.find(data[i].collegeEnd) == visitedCampuses.end() &&
            data[i].collegeStart == currentCollege &&
            data[i].distance < minDistance &&
            collegesToVisit.find(data[i].collegeEnd) != collegesToVisit.end()) {
            minDistance = data[i].distance;
            nextIndex = i;
        }
    }
    return minDistance;
}

std::vector<CollegeData> planEfficientTrip(const QStringList& collegesToVisit, std::vector<CollegeData> data, float& totalDistance) {
    std::vector<CollegeData> route;
    std::unordered_set<std::string> visitedCampuses;
    totalDistance = 0.0;

    if (collegesToVisit.isEmpty()) {
        return route; // Return empty route if no colleges are provided
    }

    std::string currentCollege = collegesToVisit.first().toStdString();
    visitedCampuses.insert(currentCollege);

    std::unordered_set<std::string> remainingColleges;
    for (int i = 1; i < collegesToVisit.size(); ++i) {
        remainingColleges.insert(collegesToVisit[i].toStdString());
    }

    while (!remainingColleges.empty()) {
        int nextIndex;
        float distance = findClosestCollege2(currentCollege, data, visitedCampuses, nextIndex, remainingColleges);

        if (nextIndex == -1) {
            // No valid next college found from the current college
            // Find the closest remaining college from all visited colleges
            int bestNextIndex = -1;
            float bestDistance = std::numeric_limits<float>::max();
            std::string bestStartCollege;

            for (const auto& visited : visitedCampuses) {
                int tempNextIndex;
                float tempDistance = findClosestCollege2(visited, data, visitedCampuses, tempNextIndex, remainingColleges);
                if (tempNextIndex != -1 && tempDistance < bestDistance) {
                    bestDistance = tempDistance;
                    bestNextIndex = tempNextIndex;
                    bestStartCollege = visited;
                }
            }

            if (bestNextIndex == -1) {
                break; // No path to remaining colleges
            }
            nextIndex = bestNextIndex;
            distance = bestDistance;
            currentCollege = bestStartCollege;

        }

        route.push_back(data[nextIndex]);
        totalDistance += distance;
        currentCollege = data[nextIndex].collegeEnd;
        visitedCampuses.insert(currentCollege);
        remainingColleges.erase(currentCollege);
    }

    return route;
}

bool isCollegeMatch(QStandardItemModel* model, const QString& searchValue) {
    if (!model) return false;

    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem* startItem = model->item(row, 0); // Column 0: collegeStart
        QStandardItem* endItem = model->item(row, 1);   // Column 1: collegeEnd

        if (startItem && startItem->text() == searchValue) {
            return true; // Match found
        } else if (endItem && endItem->text() == searchValue) {
            return true; // Match found
        }
    }
    return false; // No match found
}

void showFileLoadedMessage(QWidget* parent, const QString filename) {
    QString message = QString("File '%1' successfully loaded.").arg(filename);
    QMessageBox::information(parent, "File Loaded", message);
}


void showFileSavedMessage(QWidget* parent, const QString filename) {
    QString message = QString("File '%1' successfully Saved.").arg(filename);
    QMessageBox::information(parent, "File Saved", message);
}


void saveCollegeListToCSV(const std::vector<CollegeData>& collegeList, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Write header
    outFile << "collegeStart,collegeEnd,distance\n";

    // Function to properly format a field (enclose in quotes if it contains a comma)
    auto formatCSVField = [](const std::string& field) -> std::string {
        return (field.find(',') != std::string::npos) ? "\"" + field + "\"" : field;
    };

    // Write data rows
    for (const auto& college : collegeList) {
        outFile << formatCSVField(college.collegeStart) << ","
                << formatCSVField(college.collegeEnd) << ","
                << college.distance << "\n";
    }

    outFile.close();
}

void saveSouvenirListToCSV(const std::vector<SouvenirData>& souvenirList, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Write CSV header
    outFile << "college,souvenir,cost\n";

    // Function to properly format a field (enclose in quotes if it contains a comma)
    auto formatCSVField = [](const std::string& field) -> std::string {
        return (field.find(',') != std::string::npos) ? "\"" + field + "\"" : field;
    };

    // Write data rows
    for (const auto& souvenir : souvenirList) {
        outFile << formatCSVField(souvenir.college) << ","
                << formatCSVField(souvenir.souvenir) << ","
                << formatCSVField(souvenir.cost) << "\n";
    }

    outFile.close();
}
