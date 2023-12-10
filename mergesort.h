#ifndef MERGESORT_H
#define MERGESORT_H

#include "mysqlhandler.h"
#include <string>
#include <vector>

class MergeSort {
public:
    static void sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns);
    static void dropTable(MySQLHandler& mysqlHandler, const std::string& tableName);
private:
    static void merge(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName, int left, int middle, int right);
    static void mergeSort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName, int left, int right);
    static void saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr);
};

#endif // MERGESORT_H
