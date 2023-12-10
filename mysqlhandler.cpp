#include "mysqlhandler.h"

#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

MySQLHandler::MySQLHandler(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
    : driver(nullptr), con(nullptr) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://" + host, user, password);
        con->setSchema(database);
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

MySQLHandler::~MySQLHandler() {
    delete con;
}

void MySQLHandler::createTable(const std::string& tableName, int numColumns) {
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        // Формируем запрос на создание таблицы
        std::string query = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
        for (int i = 1; i <= numColumns; ++i) {
            query += "column_" + std::to_string(i) + " DOUBLE PRECISION";
            if (i < numColumns) {
                query += ", ";
            }
        }
        query += ")";
        stmt->execute(query);
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

void MySQLHandler::dropTable(const std::string& tableName) {
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("DROP TABLE IF EXISTS " + tableName);
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

void MySQLHandler::saveIteration(const std::string& tableName, const std::vector<double>& arr) {
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());

        // Формируем запрос на вставку данных в таблицу
        std::string query = "INSERT INTO " + tableName + " VALUES (";
        for (int i = 0; i < arr.size(); ++i) {
            query += std::to_string(arr[i]);
            if (i < arr.size() - 1) {
                query += ", ";
            }
        }
        query += ")";
        stmt->execute(query);
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

std::vector<std::vector<double>> MySQLHandler::getIterations(const std::string& tableName) {
    std::vector<std::vector<double>> iterations;

    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM " + tableName));

        while (res->next()) {
            std::vector<double> iteration;
            for (int i = 1; i <= res->getMetaData()->getColumnCount(); ++i) {
                iteration.push_back(res->getDouble(i));
            }
            iterations.push_back(iteration);
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }

    return iterations;
}
