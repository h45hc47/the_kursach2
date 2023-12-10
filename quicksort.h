#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "mysqlhandler.h"
#include <string>
#include <vector>

class QuickSort {
public:
    static void sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns);
    static void dropTable(MySQLHandler& mysqlHandler, const std::string& tableName);
private:
    static void saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr);
    static int partition(std::vector<double>& arr, int low, int high, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void quickSortUtil(MySQLHandler& mysqlHandler, std::vector<double>& arr, int low, int high, const std::string& tableName);
};

#endif // QUICKSORT_H
