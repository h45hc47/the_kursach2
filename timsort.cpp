#include "timsort.h"
#include <iostream>
#include <vector>
#include <algorithm>

void TimSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int n = arr.size();

    // Calculate minimum run length
    int minRun = minRunLength(n);

    // Sort individual subarrays of size minRun
    for (int i = 0; i < n; i += minRun) {
        insertionSort(arr, i, std::min((i + minRun - 1), (n - 1)), mysqlHandler, tableName);
    }

    // Start merging from size minRun
    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(arr, left, mid, right, mysqlHandler, tableName);
            }
        }
    }

    // Final merge of runs
    mergeRuns(arr, mysqlHandler, tableName);
}

void TimSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void TimSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

int TimSort::minRunLength(int n) {
    int r = 0;
    while (n >= MIN_MERGE) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

void TimSort::insertionSort(std::vector<double>& arr, int left, int right, MySQLHandler& mysqlHandler, const std::string& tableName) {
    for (int i = left + 1; i <= right; ++i) {
        double key = arr[i];
        int j = i - 1;

        // Move elements that are greater than key to one position ahead of their current position
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);
    }
}

void TimSort::merge(std::vector<double>& arr, int l, int m, int r, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int len1 = m - l + 1;
    int len2 = r - m;

    std::vector<double> left(len1);
    std::vector<double> right(len2);

    // Copy data to temporary arrays left[] and right[]
    for (int i = 0; i < len1; ++i) {
        left[i] = arr[l + i];
    }
    for (int j = 0; j < len2; ++j) {
        right[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    // Merge the temporary arrays back into arr[l..r]
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        }
        else {
            arr[k] = right[j];
            ++j;
        }

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);

        ++k;
    }

    // Copy the remaining elements of left[], if there are any
    while (i < len1) {
        arr[k] = left[i];
        ++i;
        ++k;

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);
    }

    // Copy the remaining elements of right[], if there are any
    while (j < len2) {
        arr[k] = right[j];
        ++j;
        ++k;

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);
    }
}

void TimSort::mergeRuns(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int n = arr.size();
    int minRun = minRunLength(n);

    // Start merging from size minRun
    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(arr, left, mid, right, mysqlHandler, tableName);
            }
        }
    }
}

void TimSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}