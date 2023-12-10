#include "mergesort.h"
#include <iostream>
#include <vector>

void MergeSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int n = arr.size();
    mergeSort(arr, mysqlHandler, tableName, 0, n - 1);
}

void MergeSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void MergeSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

void MergeSort::merge(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    std::vector<double> leftArray(n1);
    std::vector<double> rightArray(n2);

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; ++i)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArray[j] = arr[middle + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            ++i;
        }
        else {
            arr[k] = rightArray[j];
            ++j;
        }

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);

        ++k;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (i < n1) {
        arr[k] = leftArray[i];
        ++i;
        ++k;

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (j < n2) {
        arr[k] = rightArray[j];
        ++j;
        ++k;

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);
    }
}

void MergeSort::mergeSort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName, int left, int right) {
    if (left < right) {
        // Same as (left + right) / 2, but avoids overflow for large left and right
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, mysqlHandler, tableName, left, middle);
        mergeSort(arr, mysqlHandler, tableName, middle + 1, right);

        // Merge the sorted halves
        merge(arr, mysqlHandler, tableName, left, middle, right);
    }
}

void MergeSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}