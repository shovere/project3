#pragma once
#include <string>
#include <map>
#include "AVLTree.h"
#include "FiveYearHashMap.h"

class StockManager
{
private:
    struct Stock {
        float avgValue;
        std::string name;
        FiveYearHashMap* fyhm;
        Stock();
        Stock(std::string name, std::ifstream& fin, std::ifstream::streampos& track);
        void Print();
    };

    void setDates();
    void LoadFile(std::string fileName);
    static bool compByName(Stock* first, Stock* second);
    static bool compByValue(Stock* first, Stock* second);
    AVLTree<Stock*>* stocksByValue;
    AVLTree<Stock*>* stocksByName;
public:

    StockManager();
    StockManager(std::string fileName);
    StockManager(StockManager& other);
    StockManager& operator=(StockManager& other);
    ~StockManager();
    int GetTreeSize();
    std::vector<Stock*> FindDescendingStocksByName(int num);
    std::vector<Stock*> FindAscendingStocksByName(int num);
    std::vector<Stock*> FindDescendingStocksByValue(int num);
    std::vector<Stock*> FindAscendingStocksByValue(int num);
    Stock* FindStock(std::string name);
    void PrintStock(std::string name);
    std::vector<std::string> dates;
};
