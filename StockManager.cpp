#include "StockManager.h"
#include "AVLTree.h"
#include <string>
#include <iostream>
#include <fstream>

StockManager::Stock::Stock()
{
    avgValue = 0;
    name= "";
    fyhm = nullptr;
}

StockManager::Stock::Stock(std::string name, std::ifstream& fin, std::ifstream::streampos& track)
{
    this->name = name;
    fyhm = new FiveYearHashMap(fin,this->name,track);
    avgValue = fyhm->averageValue;

}
void StockManager::Stock::Print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Average Price: " << avgValue << std::endl;
    std::cout << std::endl;
}


StockManager::StockManager() {
    stocksByValue = new AVLTree<Stock*>(compByValue);
    stocksByName = new AVLTree<Stock*>(compByName);
    setDates();
}

StockManager::StockManager(std::string fileName) {
    stocksByValue = new AVLTree<Stock*>(compByValue);
    stocksByName = new AVLTree<Stock*>(compByName);
    LoadFile(fileName);
    setDates();
}

StockManager::StockManager(StockManager& other) {
    stocksByValue = new AVLTree<Stock*>(compByValue);
    *stocksByValue = *other.stocksByValue;
    stocksByName = new AVLTree<Stock*>(compByName);
    *stocksByName = *other.stocksByName;
}

StockManager& StockManager::operator=(StockManager& other) {
    stocksByValue = new AVLTree<Stock*>(compByValue);
    *stocksByValue = *other.stocksByValue;
    stocksByName = new AVLTree<Stock*>(compByName);
    *stocksByName = *other.stocksByName;
    return *this;
}

StockManager::~StockManager() {
    delete stocksByValue;
    delete stocksByName;
}

bool StockManager::compByName(Stock* first, Stock* second) {
    return first->name.compare(second->name) < 0;
}

bool StockManager::compByValue(Stock* first, Stock* second) {
    return first->avgValue < second->avgValue;
}

int StockManager::GetTreeSize() {
    return stocksByName->GetSize();
}

std::vector<StockManager::Stock*> StockManager::FindDescendingStocksByValue(int num) {
    std::vector<Stock*> vec;
    return stocksByValue->Descend(vec, num);
}

std::vector<StockManager::Stock*> StockManager::FindAscendingStocksByValue(int num) {
    std::vector<Stock*> vec;
    return stocksByValue->Ascend(vec, num);
}

std::vector<StockManager::Stock*> StockManager::FindDescendingStocksByName(int num) {
    std::vector<Stock*> vec;
    return stocksByName->Descend(vec, num);
}

std::vector<StockManager::Stock*> StockManager::FindAscendingStocksByName(int num) {
    std::vector<Stock*> vec;
    return stocksByName->Ascend(vec, num);
}

StockManager::Stock* StockManager::FindStock(std::string name) {
    std::cout << "entered" << std::endl;
    Stock* stock = new Stock();
    stock->name = name;
    Stock* temp;
    temp = stocksByName->Find(stock);
    delete stock;
    stock = nullptr;
    return temp;

}

void StockManager::setDates()
{
    bool isLeapYear = false;
    std::string year;
    std::string month;
    std::string day;
    std::string date;
    int maxDay=0;
    for (int i = 13; i < 19; i++)
    {
        if (i == 16)
            isLeapYear = true;
        year = std::to_string(i);

        for (int j = 1; j < 13; j++ )
        {
            month = std::to_string(j);
            if (isLeapYear && j == 2)
            {
                isLeapYear = false;
                maxDay = 29;
            }
            else if (j == 2)
                maxDay = 28;

            switch (j)
            {
            case 1:
                maxDay = 31;
                break;
            case 3:
                maxDay = 31;
                break;
            case 5:
                maxDay = 31;
                break;
            case 7:
                maxDay = 31;
                break;
            case 8:
                maxDay = 31;
                break;
            case 10:
                maxDay = 31;
                break;
            case 12:
                maxDay = 31;
                break;
            }

            switch (j)
            {
            case 4:
                maxDay = 30;
                break;
            case 6:
                maxDay = 30;
                break;
            case 9:
                maxDay = 30;
                break;
            case 11:
                maxDay = 30;
                break;
            }
            for (int k = 1  ; k < maxDay; k++)
            {
                if(month.size() < 2)
                {
                    month = '0' + month;
                }

                day = std::to_string(k);

                if(day.size() <2)
                {
                    day = "0" + day;
                }
                if(year.size()<4){
                    year = "20" + year;
                }

                date = year + "-" + month + "-" + day;
                dates.push_back(date);
            }

        }
    }
}

void StockManager::LoadFile(std::string fileName) {

    std::ifstream fin(fileName, std::ios::in);
    std::ifstream::streampos track = fin.tellg();
    std::string name = "";
    std::string line;
    bool begin = true;
    while (fin >>line)
    {

        if (begin)
        {
            track = fin.tellg();
            begin = false;
            continue;
        }
        int it = 0;
        std::string word;
        std::stringstream s(line);
        while (std::getline(s, word, ','))
        {
            if (it == 6 && word != name && word != "Name")
            {

                fin.seekg(track);
                Stock *st = new Stock(word, fin, track);
                stocksByName->Insert(st);
                stocksByValue->Insert(st);
                name = word;
            }
            it++;
        }

        fin.seekg(track);
        begin = true;

    }
    fin.close();
}

void StockManager::PrintStock(std::string name) {
    FindStock(name)->Print();
}
