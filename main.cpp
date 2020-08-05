#include "mainwindow.h"
#include <iostream>
#include <string>
#include "FiveYearHashMap.h"
#include "StockManager.h"
#include <QApplication>
#include <vector>
#include <QtCharts>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);

    w.setWindowTitle("Stock Manager");
    std::string file = qApp->applicationDirPath().toStdString() + "/all_stocks_5yr.csv";

    StockManager FO(file);

    w.instantiate(FO);

    w.addNewDropDownName();
    w.addNewDropDownDate();



    w.show();


    return a.exec();
}
