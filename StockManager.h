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
	AVLTree<Stock*>* stocksByValue;//move these back to private later
	AVLTree<Stock*>* stocksByName;
	StockManager();
	StockManager(std::string fileName);
	StockManager(StockManager& other);
	StockManager& operator=(StockManager& other);
	~StockManager();
	std::vector<Stock*> FindAllStocksByName();
	std::vector<Stock*> FindAllStocksByValue();
	std::vector<Stock*> FindTopStocksByName(int num);
	std::vector<Stock*> FindBottomStocksByName(int num);
	std::vector<Stock*> FindTopStocksByValue(int num);
	std::vector<Stock*> FindBottomStocksByValue(int num);
	Stock* FindStock(std::string name);
	void PrintStock(std::string name);
	std::vector<std::string> dates;
};

