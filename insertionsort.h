#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "mysqlhandler.h"
#include <string>
#include <vector>

class InsertionSort {
public:
    static void sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns);
    static void dropTable(MySQLHandler& mysqlHandler, const std::string& tableName);
private:
    static void saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr);
};

#endif // INSERTIONSORT_H
