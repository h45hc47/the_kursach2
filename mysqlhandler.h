#ifndef MYSQLHANDLER_H
#define MYSQLHANDLER_H

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <string>
#include <vector>

class MySQLHandler {
public:
    MySQLHandler(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~MySQLHandler();

    void createTable(const std::string& tableName, int numColumns);
    void dropTable(const std::string& tableName);
    void saveIteration(const std::string& tableName, const std::vector<double>& arr);
    std::vector<std::vector<double>> getIterations(const std::string& tableName);
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
};

#endif // MYSQLHANDLER_H
