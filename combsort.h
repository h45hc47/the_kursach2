#ifndef COMBSORT_H
#define COMBSORT_H

#include "mysqlhandler.h"
#include <string>
#include <vector>

class CombSort {
public:
    static void sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName);
    static void createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns);
    static void dropTable(MySQLHandler& mysqlHandler, const std::string& tableName);
private:
    static int getNextGap(int gap);
    static void saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr);
};

#endif // COMBSORT_H
