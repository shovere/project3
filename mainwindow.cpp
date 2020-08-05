#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StockManager.h"


StockManager Pass;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TableByStock->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->TableByDate->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->TableLoadS, SIGNAL(clicked()),this,SLOT(loadTableByStock()));
    connect(ui->TableLoadD, SIGNAL(clicked()),this,SLOT(loadTableByDate()));
    connect(ui->LoadAscending, SIGNAL(clicked()), this, SLOT(loadAverageChartA()));
    connect(ui->LoadDescending, SIGNAL(clicked()), this, SLOT(loadAverageChartD()));
    connect(ui->GraphLoadS, SIGNAL(clicked()), this, SLOT(loadGraphS()));
    connect(ui->GraphLoadD, SIGNAL(clicked()), this, SLOT(loadGraphD()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::instantiate(StockManager Original)
{

Pass = Original;
}

void MainWindow::addNewDropDownName()
{
    for (int i = 0; i  < Pass.GetTreeSize() ;i++)
    {
        QString hold = QString::fromStdString(Pass.FindAscendingStocksByName(Pass.GetTreeSize())[i]->name);
        ui->ByStockDD->addItem(hold);
        ui->ByStockDDG->addItem(hold);
    }
}

void MainWindow::addNewDropDownDate()
{

    for (unsigned int i = 0; i < Pass.dates.size();i++)
    {
        QString hold = QString::fromStdString(Pass.dates[i]);
        ui->ByDateDD->addItem(hold);
        ui->ByDateDDG->addItem(hold);
    }

}

void MainWindow::loadTableByStock()
{
    ui->TableByStock->setRowCount(0);
    for (unsigned int i = 0; i < Pass.dates.size();i++)
    {
        float f = Pass.FindStock(ui->ByStockDD->currentText().toStdString())->fyhm->getValue(Pass.dates[i]);
        if (f != -1)
        {
            QString hold = QString::number(f);
            updateTableByStock(QString::fromStdString(Pass.dates[i]), hold);
        }
    }
}


void MainWindow::updateTableByStock(QString Date, QString Price)
{
    ui->TableByStock->insertRow(ui->TableByStock->rowCount());
    ui->TableByStock->setItem(ui->TableByStock->rowCount()-1, 0, new QTableWidgetItem(Date));
    ui->TableByStock->setItem(ui->TableByStock->rowCount()-1, 1, new QTableWidgetItem(Price));
    ui->TableByStock->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::loadTableByDate()
{
    ui->TableByDate->setRowCount(0);
   for (int i = 0; i  < Pass.GetTreeSize();i++)
   {
       float f = Pass.FindAscendingStocksByName(Pass.GetTreeSize())[i]->fyhm->getValue(ui->ByDateDD->currentText().toStdString());
       if (f != -1)
       {
       QString hold = QString::number(f);
       updateTableByDate(QString::fromStdString(Pass.FindAscendingStocksByName(Pass.GetTreeSize())[i]->name), hold);
       }
   }

}

void MainWindow::updateTableByDate(QString Date, QString Price)
{
    ui->TableByDate->insertRow(ui->TableByDate->rowCount());
    ui->TableByDate->setItem(ui->TableByDate->rowCount()-1, 0, new QTableWidgetItem(Date));
    ui->TableByDate->setItem(ui->TableByDate->rowCount()-1, 1, new QTableWidgetItem(Price));
    ui->TableByDate->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::loadAverageChartA()
{
    QLineSeries *aescendingSeries = new QLineSeries;
    QCategoryAxis *xAxis = new QCategoryAxis;
    QChart *averageChartA = new QChart;
    QValueAxis *yAxis = new QValueAxis;

    for (int i =0; i < ui->NumStockDD->currentText().toInt(); i++)
    {

        float f = Pass.FindAscendingStocksByValue(Pass.GetTreeSize())[i]->avgValue;
        QString Name = QString::fromStdString(Pass.FindAscendingStocksByValue(Pass.GetTreeSize())[i]->name);
        aescendingSeries->append(i, f);
        xAxis->append(Name, i);
    }
    averageChartA->addSeries(aescendingSeries);

    averageChartA->addAxis(xAxis,Qt::AlignBottom);
    averageChartA->addAxis(yAxis,Qt::AlignLeft);
    aescendingSeries->attachAxis(xAxis);
    aescendingSeries->attachAxis(yAxis);
    averageChartA->legend()->hide();

    ui->AvgGraph->setChart(averageChartA);


}


void MainWindow::loadAverageChartD()
{
    QLineSeries *descendingSeries = new QLineSeries;
    QCategoryAxis *xAxis = new QCategoryAxis;
    QChart *averageChartA = new QChart;
    QValueAxis *yAxis = new QValueAxis;

    for (int i =0; i < ui->NumStockDD->currentText().toInt(); i++)
    {
        float f = Pass.FindDescendingStocksByValue(Pass.GetTreeSize())[i]->avgValue;
        QString Name = QString::fromStdString(Pass.FindDescendingStocksByValue(Pass.GetTreeSize())[i]->name);
        descendingSeries->append(i, f);
        xAxis->append(Name, i);
    }
    averageChartA->addSeries(descendingSeries);
    averageChartA->addAxis(xAxis,Qt::AlignBottom);
    averageChartA->addAxis(yAxis,Qt::AlignLeft);
    descendingSeries->attachAxis(xAxis);
    descendingSeries->attachAxis(yAxis);
    averageChartA->legend()->hide();
    ui->AvgGraph->setChart(averageChartA);

}

void MainWindow::loadGraphS()
{
    QLineSeries *stockPrices = new QLineSeries;
    QCategoryAxis *xAxis = new QCategoryAxis;
    QChart *graphS = new QChart;
    QValueAxis *yAxis = new QValueAxis;

    for (unsigned int i = 0; i < Pass.dates.size();i++)
    {
        float f = Pass.FindStock(ui->ByStockDDG->currentText().toStdString())->fyhm->getValue(Pass.dates[i]);
        if (f != -1)
        {
            xAxis->append(QString::fromStdString(Pass.dates[i]), i);
            stockPrices->append(i,f);
        }
    }
    graphS->addSeries(stockPrices);
    graphS->addAxis(xAxis, Qt::AlignBottom);
    graphS->addAxis(yAxis,Qt::AlignLeft);
    stockPrices->attachAxis(xAxis);
    stockPrices->attachAxis(yAxis);
    graphS->legend()->hide();

    ui->ByStockGraph->setChart(graphS);

}

void MainWindow::loadGraphD()
{
    QLineSeries *stockPrices = new QLineSeries;
    QCategoryAxis *xAxis = new QCategoryAxis;
    QChart *graphD = new QChart;
    QValueAxis *yAxis = new QValueAxis;

    for (int i = 0; i  < Pass.GetTreeSize();i++)
    {
        float f = Pass.FindAscendingStocksByName(Pass.GetTreeSize())[i]->fyhm->getValue(ui->ByDateDDG->currentText().toStdString());
        if (f != -1){
            xAxis->append(QString::fromStdString(Pass.FindAscendingStocksByName(Pass.GetTreeSize())[i]->name),i);
            stockPrices->append(i,f);

        }
    }
    graphD->addSeries(stockPrices);
    graphD->addAxis(xAxis, Qt::AlignBottom);
    graphD->addAxis(yAxis,Qt::AlignLeft);
    stockPrices->attachAxis(xAxis);
    stockPrices->attachAxis(yAxis);
    graphD->legend()->hide();

    ui->ByDateGraph->setChart(graphD);

}

