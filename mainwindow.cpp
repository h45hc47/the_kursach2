#include "mainwindow.h"

#include <map>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>


MainWindow::MainWindow(QWidget* parent, const std::string& host, const std::string& user, const std::string& password, const std::string& database)
    : QMainWindow(parent),
    mysqlHandler(host, user, password, database),
    originalArray() {

    algorithmTableMap = {
        {"Bubble Sort", "bubble_sort"},
        {"Insertion Sort", "insertion_sort"},
        {"Quick Sort", "quick_sort"},
        {"Shell Sort", "shell_sort"},
        {"Merge Sort", "merge_sort"},
        {"Selection Sort", "selection_sort"},
        {"Comb Sort", "comb_sort"},
        {"Tim Sort", "tim_sort"}
    };
    
    // Set up the table
    tableWidget = new QTableWidget(this);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    // Set up sorting algorithm combo box
    sortAlgorithmComboBox = new QComboBox(this);
    for (const auto& algorithm : algorithmTableMap) {
        sortAlgorithmComboBox->addItem(algorithm.first);
    }

    // Set up array size spin box
    arraySizeSpinBox = new QSpinBox(this);

    // Set up lower and upper bound line edits
    lowerBoundLineEdit = new QLineEdit(this);
    upperBoundLineEdit = new QLineEdit(this);

    // Set up buttons
    fillArrayButton = new QPushButton("Fill Array", this);
    sortButton = new QPushButton("Sort", this);

    // Connect signals and slots
    connect(fillArrayButton, &QPushButton::clicked, this, &MainWindow::fillArray);
    connect(sortButton, &QPushButton::clicked, this, &MainWindow::sortArray);

    // Set up layout
    QHBoxLayout* controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(new QLabel("Sorting Algorithm:", this));
    controlsLayout->addWidget(sortAlgorithmComboBox);
    controlsLayout->addWidget(new QLabel("Array Size:", this));
    controlsLayout->addWidget(arraySizeSpinBox);
    controlsLayout->addWidget(new QLabel("Lower Bound:", this));
    controlsLayout->addWidget(lowerBoundLineEdit);
    controlsLayout->addWidget(new QLabel("Upper Bound:", this));
    controlsLayout->addWidget(upperBoundLineEdit);
    controlsLayout->addWidget(fillArrayButton);
    controlsLayout->addWidget(sortButton);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(tableWidget);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}


void MainWindow::fillArray() {
    // Clear the table
    tableWidget->clear();

    // Get the array size and bounds
    int arraySize = arraySizeSpinBox->value();
    double lowerBound = lowerBoundLineEdit->text().toDouble();
    double upperBound = upperBoundLineEdit->text().toDouble();

    // Generate random data within the specified range
    originalArray.clear();
    srand(static_cast<unsigned int>(time(0)));  // Seed for random numbers
    for (int i = 0; i < arraySize; ++i) {
        double randomValue = lowerBound + (rand() / (RAND_MAX + 1.0)) * (upperBound - lowerBound);
        originalArray.push_back(randomValue);
    }

    // Display the array in the table
    tableWidget->setRowCount(1);
    tableWidget->setColumnCount(arraySize);
    for (int i = 0; i < arraySize; ++i) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(originalArray[i]));
        tableWidget->setItem(0, i, item);
    }
}

void MainWindow::sortArray() {
    // Get the selected sorting algorithm
    QString selectedAlgorithm = sortAlgorithmComboBox->currentText();

    // Get the array from the table
    std::vector<double> arr;
    for (int i = 0; i < tableWidget->columnCount(); ++i) {
        QTableWidgetItem* item = tableWidget->item(0, i);
        if (item) {
            arr.push_back(item->text().toDouble());
        }
    }

    // Perform sorting based on the selected algorithm
    std::string tableName = algorithmTableMap[selectedAlgorithm];
    if (selectedAlgorithm == "Bubble Sort") {
        BubbleSort::dropTable(mysqlHandler, tableName);
        BubbleSort::createTable(mysqlHandler, tableName, arr.size());
        BubbleSort::sort(arr, mysqlHandler, tableName);
    }
    else if (selectedAlgorithm == "Insertion Sort") {
        InsertionSort::dropTable(mysqlHandler, tableName);
        InsertionSort::createTable(mysqlHandler, tableName, arr.size());
        InsertionSort::sort(arr, mysqlHandler, tableName);
    }
    else if (selectedAlgorithm == "Shell Sort") {
        ShellSort::dropTable(mysqlHandler, tableName);
        ShellSort::createTable(mysqlHandler, tableName, arr.size());
        ShellSort::sort(arr, mysqlHandler, tableName);
    }
    else if (selectedAlgorithm == "Merge Sort") {
        MergeSort::dropTable(mysqlHandler, tableName);
        MergeSort::createTable(mysqlHandler, tableName, arr.size());
        MergeSort::sort(arr, mysqlHandler, tableName);
    }
    else if (selectedAlgorithm == "Selection Sort") {
        SelectionSort::dropTable(mysqlHandler, tableName);
        SelectionSort::createTable(mysqlHandler, tableName, arr.size());
        SelectionSort::sort(arr, mysqlHandler, tableName);
    }
    else if (selectedAlgorithm == "Comb Sort") {
        CombSort::dropTable(mysqlHandler, tableName);
        CombSort::createTable(mysqlHandler, tableName, arr.size());
        CombSort::sort(arr, mysqlHandler, tableName);
    }
    else if (selectedAlgorithm == "Tim Sort") {
        TimSort::dropTable(mysqlHandler, tableName);
        TimSort::createTable(mysqlHandler, tableName, arr.size());
        TimSort::sort(arr, mysqlHandler, tableName);
    }
    else if (selectedAlgorithm == "Quick Sort") {
        QuickSort::dropTable(mysqlHandler, tableName);
        QuickSort::createTable(mysqlHandler, tableName, arr.size());
        QuickSort::sort(arr, mysqlHandler, tableName);
    }
    // Add more conditions for other sorting algorithms if needed

    // Update the table with sorting iterations
    updateTable(arr);
}

void MainWindow::updateTable(const std::vector<double>& arr) {
    // Clear the table
    tableWidget->clear();

    // Display the original array in the table
    tableWidget->setRowCount(1);
    tableWidget->setColumnCount(originalArray.size());
    for (int i = 0; i < originalArray.size(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(originalArray[i]));
        tableWidget->setItem(0, i, item);
    }

    // Retrieve and display iterations from the database
    std::string tableName = algorithmTableMap[(sortAlgorithmComboBox->currentText()).toLocal8Bit().constData()];
    std::vector<std::vector<double>> iterations = mysqlHandler.getIterations(tableName);

    // Add rows for each iteration
    int rowCount = tableWidget->rowCount();
    tableWidget->setRowCount(rowCount + iterations.size());
    for (int i = 0; i < iterations.size(); ++i) {
        for (int j = 0; j < iterations[i].size(); ++j) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(iterations[i][j]));
            tableWidget->setItem(rowCount + i, j, item);
        }
    }
}