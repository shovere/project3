#pragma once
#include <string>
#include <map>
#include "AVLTree.h"

class StockManager
{
private:
	struct Stock {
		double avgValue;
		std::string name;
		//Store whatever data structure ethan makes here
		void Print();
	};
	AVLTree<Stock*>* stocksByValue;
	AVLTree<Stock*>* stocksByName;
	std::vector<Stock*> FindAllStocks();
	std::vector<Stock*> FindTopStocks(int num);
	std::vector<Stock*> FindTopStocks(int num);
	Stock* FindStock(std::string name);

	static bool compByName(Stock* first, Stock* second);
	static bool compByValue(Stock* first, Stock* second);

public:
	StockManager();
	StockManager(std::string fileName);
	bool LoadFile(std::string fileName);
	void PrintStock(std::string name);
};

