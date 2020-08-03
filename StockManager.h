#pragma once
#include <string>
#include <map>
#include "AVLTree.h"
#include "FiveYearHashMap.h"

enum StockOrder{Ascend, Descend};

class StockManager
{
private:
	struct Stock {
		double avgValue;
		std::string name;
		FiveYearHashMap* fyhm;
		Stock();
		Stock(std::string name, std::string file);
		void Print();
	};
	AVLTree<Stock*>* stocksByValue;
	AVLTree<Stock*>* stocksByName;
	std::vector<Stock*> FindAllStocks();
	std::vector<Stock*> FindTopStocks(int num, StockOrder order);
	Stock* FindStock(std::string name);

	static bool compByName(Stock* first, Stock* second);
	static bool compByValue(Stock* first, Stock* second);

public:
	StockManager();
	StockManager(std::string fileName);
	void LoadFile(std::string fileName);
	void PrintStock(std::string name);
};

