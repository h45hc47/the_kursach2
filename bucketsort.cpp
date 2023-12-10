#include "bucketsort.h"
#include <iostream>
#include <algorithm>
#include <vector>

void BucketSort::sort(std::vector<double>& arr, MySQLHandler& mysqlHandler, const std::string& tableName, int numBuckets) {
    // Create buckets
    std::vector<std::vector<double>> buckets(numBuckets);

    // Distribute elements into buckets
    for (double value : arr) {
        int bucketIndex = static_cast<int>(value * numBuckets);
        buckets[bucketIndex].push_back(value);
    }

    // Sort individual buckets using a simple sorting algorithm (e.g., insertion sort)
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());

        // Save iteration to the database
        saveIteration(mysqlHandler, tableName, arr);
    }

    // Concatenate sorted buckets back into the original array
    arr.clear();
    for (const auto& bucket : buckets) {
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
    saveIteration(mysqlHandler, tableName, arr);
}

void BucketSort::createTable(MySQLHandler& mysqlHandler, const std::string& tableName, int numColumns) {
    mysqlHandler.createTable(tableName, numColumns);
}

void BucketSort::dropTable(MySQLHandler& mysqlHandler, const std::string& tableName) {
    mysqlHandler.dropTable(tableName);
}

void BucketSort::saveIteration(MySQLHandler& mysqlHandler, const std::string& tableName, const std::vector<double>& arr) {
    mysqlHandler.saveIteration(tableName, arr);
}