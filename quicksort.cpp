#include "quicksort.h"
#include <iostream>

void QuickSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName) {
    // Удаляем существующую таблицу перед началом сортировки
    dropTable(mysqlHandler, tableName);

    // Создаем новую таблицу перед началом сортировки
    createTable(mysqlHandler, tableName, arr.size());

    int n = arr.size();
    quickSortUtil(mysqlHandler, arr, 0, n - 1, tableName);
}

void QuickSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void QuickSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

void QuickSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}

int QuickSort::partition(std::vector<double>& arr, int low, int high, MySQLHandler& mysqlHandler, const std::string& tableName) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);

            // Сохранение итерации в базу данных
            saveIteration(mysqlHandler, tableName, arr);
        }
    }

    std::swap(arr[i + 1], arr[high]);

    // Сохранение итерации в базу данных
    saveIteration(mysqlHandler, tableName, arr);

    return (i + 1);
}

void QuickSort::quickSortUtil(MySQLHandler& mysqlHandler, std::vector<double>& arr, int low, int high, const std::string& tableName) {
    if (low < high) {
        int pi = partition(arr, low, high, mysqlHandler, tableName);

        quickSortUtil(mysqlHandler, arr, low, pi - 1, tableName);
        quickSortUtil(mysqlHandler, arr, pi + 1, high, tableName);
    }
}