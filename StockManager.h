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

public:
	AVLTree<Stock*>* stocksByValue;
	AVLTree<Stock*>* stocksByName;
	StockManager();
	StockManager(std::string fileName);
	std::vector<Stock*> FindAllStocks();
	std::vector<Stock*> FindTopStocks(int num);
	std::vector<Stock*> FindBottomStocks(int num);
	Stock* FindStock(std::string name);
	void PrintStock(std::string name);
	std::vector<std::string> dates;
};

