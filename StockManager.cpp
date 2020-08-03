#include "StockManager.h"
#include "AVLTree.h"
#include <string>
#include <iostream>

void StockManager::Stock::Print() {
	std::cout << "Name: " << name << std::endl;
	std::cout << "Average Price: " << avgValue << std::endl;
	std::cout << std::endl;
}

StockManager::Stock::Stock()
{

}

StockManager::Stock::Stock(std::string name, std::string file)
{
	this->name = name;
	fyhm = new FiveYearHashMap(file, this->name);
	avgValue = fyhm->averageValue;

}

StockManager::StockManager() {
	stocksByValue = new AVLTree<Stock*>(compByValue);
	stocksByName = new AVLTree<Stock*>(compByName);
}

StockManager::StockManager(std::string fileName) {
	LoadFile(fileName);
	stocksByValue = new AVLTree<Stock*>(compByValue);
	stocksByName = new AVLTree<Stock*>(compByName);
}

bool StockManager::compByName(Stock* first, Stock* second) {
	return first->name.compare(second->name) < 0;
}

bool StockManager::compByValue(Stock* first, Stock* second) {
	return first->avgValue < second->avgValue;
}

std::vector<StockManager::Stock*> StockManager::FindAllStocks() {
	std::vector<Stock*> vec;
	return stocksByName->Decend(vec);
}

std::vector<StockManager::Stock*> StockManager::FindTopStocks(int num, StockOrder order) {
	std::vector<Stock*> vec;
	if(order == Ascend)
		return stocksByValue->Ascend(vec, num);
	if(order == Descend)
		return stocksByValue->Decend(vec, num);
}
StockManager::Stock* StockManager::FindStock(std::string name) {
	Stock stock;
	stock.name = name;
	return stocksByName->Find(&stock);

}

void StockManager::LoadFile(std::string fileName) {

	std::fstream fin(fileName, std::ios::in);

	std::string name = "";
	std::string line;
	int tracker = 0;
	bool begin = true;
	while (fin >> line)
	{

		if (begin || tracker < 500)//speeds up stuff, 500 is 100 * number of years. ensures we dont miss a stock
		{
			begin = false;
			tracker++;
			continue;
		}
		int it = 0;
		std::string word;
		std::stringstream s(line);
		while (std::getline(s, word, ','))
		{
			if (it == 6 && word != name)
			{
				Stock *st = new Stock(word, fileName);
				stocksByName->Insert(st);
				stocksByValue->Insert(st);
				name = word;
			}
			it++;
		}
		tracker = 0;
	}
}

void StockManager::PrintStock(std::string name) {
	FindStock(name)->Print();
}
