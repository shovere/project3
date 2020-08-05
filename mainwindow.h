#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "StockManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void addNewDropDownName();
    void addNewDropDownDate();
    void instantiate(StockManager);

    void updateTableByStock(QString,QString);
    void updateTableByDate(QString, QString);
    ~MainWindow();
private slots:
    void loadTableByStock();
    void loadTableByDate();
    void loadAverageChartA();
    void loadAverageChartD();
    void loadGraphS();
    void loadGraphD();


private:
    Ui::MainWindow *ui;
};
#endif //   MAINWINDOW_H
