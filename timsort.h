#ifndef TIMSORT_H
#define TIMSORT_H

#include "mysqlhandler.h"
#include <string>
#include <vector>

class TimSort {
public:
    static void sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns);
    static void dropTable(MySQLHandler& mysqlHandler, const std::string& tableName);
private:
    static const int MIN_MERGE = 32;

    static int minRunLength(int n);
    static void insertionSort(std::vector<double>& arr, int left, int right, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void merge(std::vector<double>& arr, int l, int m, int r, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void mergeRuns(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr);
};

#endif // TIMSORT_H
