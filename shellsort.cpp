#include "shellsort.h"
#include <iostream>
#include <vector>

void ShellSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int n = arr.size();

    // Start with a large gap and reduce it
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size
        for (int i = gap; i < n; ++i) {
            double temp = arr[i];
            int j;

            // Shift elements of arr[0..i-gap-1], arr[1..i-gap], arr[2..i-gap], ... until you find the right place for arr[i]
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            // Place temp (the original arr[i]) in its correct location
            arr[j] = temp;

            // Save iteration to the database
            saveIteration(mysqlHandler, tableName, arr);
        }
    }
}

void ShellSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void ShellSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

void ShellSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}