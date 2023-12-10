#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>

#include "mysqlhandler.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "shellsort.h"
#include "mergesort.h"
#include "selectionsort.h"
#include "combsort.h"
#include "timsort.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent, const std::string& host, const std::string& user, const std::string& password, const std::string& database);

private slots:
    void fillArray();
    void sortArray();
    void updateTable(const std::vector<double>& arr);

private:
    MySQLHandler mysqlHandler;
    QTableWidget* tableWidget;
    QComboBox* sortAlgorithmComboBox;
    QSpinBox* arraySizeSpinBox;
    QLineEdit* lowerBoundLineEdit;
    QLineEdit* upperBoundLineEdit;
    QPushButton* fillArrayButton;
    QPushButton* sortButton;
    std::vector<double> originalArray;
    std::map<QString, std::string> algorithmTableMap;
};

#endif // MAINWINDOW_H
