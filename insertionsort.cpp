#include "insertionsort.h"
#include <iostream>

void InsertionSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        double key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;

            // Сохранение итерации в базу данных
            saveIteration(mysqlHandler, tableName, arr);
        }

        arr[j + 1] = key;

        // Сохранение итерации в базу данных
        saveIteration(mysqlHandler, tableName, arr);
    }
}

void InsertionSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void InsertionSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

void InsertionSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}