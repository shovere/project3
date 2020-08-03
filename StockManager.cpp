#include "StockManager.h"
#include "AVLTree.h"
#include <string>
#include <iostream>

void StockManager::Stock::Print() {
	std::cout << "Name: " << name << std::endl;
	std::cout << "Average Price: " << avgValue << std::endl;
	std::cout << std::endl;
}

StockManager::StockManager() {
	stocksByValue = new AVLTree<Stock*>(compByValue);
	stocksByName = new AVLTree<Stock*>(compByName);
}

StockManager::StockManager(std::string fileName) {
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

std::vector<StockManager::Stock*> StockManager::FindTopStocks(int num) {
	std::vector<Stock*> vec;
	return stocksByValue->Decend(vec, num);
}

std::vector<StockManager::Stock*> StockManager::FindTopStocks(int num) {
	std::vector<Stock*> vec;
	return stocksByValue->Ascend(vec, num);
}

StockManager::Stock* StockManager::FindStock(std::string name) {
	Stock* stock;
	stock->name = name;
	return stocksByName->Find(stock);
}

bool StockManager::LoadFile(std::string fileName) {

}

void StockManager::PrintStock(std::string name) {
	FindStock(name)->Print();
}
