#include "combsort.h"
#include <iostream>
#include <vector>

void CombSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int n = arr.size();
    int gap = n;

    // Initialize swapped variable to check if swapping happens
    bool swapped = true;

    // Continue while gap is more than 1 and last iteration caused a swap
    while (gap != 1 || swapped) {
        // Update the gap value using the next gap function
        gap = getNextGap(gap);

        // Reset the swapped flag on entering the loop
        swapped = false;

        // Compare all elements with the current gap
        for (int i = 0; i < n - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                // Swap arr[i] and arr[i+gap]
                std::swap(arr[i], arr[i + gap]);

                // Set swapped to true
                swapped = true;

                // Save iteration to the database
                saveIteration(mysqlHandler, tableName, arr);
            }
        }
    }
}

void CombSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void CombSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

int CombSort::getNextGap(int gap) {
    // Shrink gap by a factor of 1.3
    gap = (gap * 10) / 13;
    if (gap < 1) {
        return 1;
    }
    return gap;
}

void CombSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}