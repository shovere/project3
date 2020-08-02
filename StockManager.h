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
		void Print(Stock stock);
	};
	AVLTree<Stock> stocksByValue;
	AVLTree<Stock> stocksByName;

public:
	StockManager();
	StockManager(std::string fileName);
	bool LoadFile(std::string fileName);
	void PrintStock(std::string name);
	std::vector<Stock> FindAllStocks();
	std::vector<Stock> FindTopStocks(int num);
	std::vector<Stock> FindTopStocks(int num);
};

