#include "selectionsort.h"
#include <iostream>
#include <vector>

void SelectionSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        // Find the minimum element in the unsorted part of the array
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element
        std::swap(arr[i], arr[minIndex]);

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);
    }
}

void SelectionSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void SelectionSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

void SelectionSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}