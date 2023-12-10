#include <QApplication>

#include <vector>
#include <string>

#include "mainwindow.h"
#include "mysqlhandler.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Set up parameters for MySQLHandler
    std::string host = "127.0.0.1";
    std::string user = "admin";
    std::string password = "admin";
    std::string database = "sorts_database";

    // Create an instance of MainWindow, which will initialize MySQLHandler
    MainWindow mainWindow(nullptr, host, user, password, database);

    mainWindow.show();

    return app.exec();
}