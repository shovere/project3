#include "StockManager.h"
#include <string>
#include <fstream>

void StockManager::Stock::Print(Stock stock) {

}

StockManager::Stock::Stock(std::string name, std::string file)
{
    this->name = name;
    fyhm = new FiveYearHashMap(file, this->name);
    avgValue = fyhm->averageValue;

}

StockManager::StockManager() {

}

StockManager::StockManager(std::string fileName) {
    LoadFile(fileName);
}

void StockManager::LoadFile(std::string fileName) {
        std::fstream fin(filename, std::ios::in);

        std::string name = "";
        std::string line;
        int tracker = 0;
        while(fin >> line)
        {
            if (begin || tracker < 500)//speeds up stuff, 500 is 100 * number of years. ensures we dont miss a stock
            {
                begin = false;
                tracker++;
                continue;
            }
            it = 0;
            cont = false;
            std::stringstream s(temp);
            while (getline(s, word, ','))
            {
                if (it == 6 && word != name)
                {
                    Stock *st = new Stock(word, fileName);
                    stocksByName.Insert(st);
                    stocksByValue.Insert(st);
                    name = word;
                }
                it++;
            }
            tracker = 0;
        }
}


void StockManager::PrintStock(std::string name) {

}

std::vector<StockManager::Stock> StockManager::FindAllStocks() {

}

std::vector<StockManager::Stock> StockManager::FindTopStocks(int num) {

}

std::vector<StockManager::Stock> StockManager::FindTopStocks(int num) {

}
