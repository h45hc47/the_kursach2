#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include "mysqlhandler.h"
#include <string>
#include <vector>

class BucketSort {
public:
    static void sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName, int numBuckets);
    static void createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns);
    static void dropTable(MySQLHandler& mysqlHandler, const std::string& tableName);
private:
    static void saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr);
};

#endif // BUCKETSORT_H
