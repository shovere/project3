//
// Created by e2sho on 7/24/2020.
//

#include "OneYearHashMap.h"
#include <iostream>
#include <algorithm>

OneYearHashMap::Node::Node(int hashedKey, float value) {
    this->hashedKey = hashedKey;
    this->value = value;
}

OneYearHashMap::OneYearHashMap(int year) {
    this->year = year;
}
void OneYearHashMap::setPair(std::string &key, float &value) {

    keys[hash(key)] = new Node(hash(key), value);
    values[size] = keys[hash(key)];

    try
    {
        size++;
        if(size > 366)
            throw 1;
    }
    catch(int e)
    {
        std::cout << "Exception: the number of elements exceeds predefined boundaries, a maximum of 366 elements are allowed." << std::endl;
    }

}

int OneYearHashMap::hash(std::string& key) {
    try
    {
        if(key.length() != 10)
            throw 1;
    }
    catch(int e)
    {
        std::cout << "Exception: Invalid key size. Keys must be of size 10 and format XXXX-XX-XX" << std::endl;
    }

    int month =  std::stoi(key.substr(5,1));
    int day =  std::stoi(key.substr(8,1));
    int hashKey = ((month-1)*31) + day;
    return hashKey;

}

std::string OneYearHashMap::reverseHash(int hashedKey) {
    int month = 0;
    int day = 0;
    if(hashedKey % 31 != 0)
    {
        month = (hashedKey/31)+1;
        day = hashedKey % 31;
    }
    else
    {
        month = (hashedKey / 31);
        day = 31;
    }

    return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
}

OneYearHashMap::Node *OneYearHashMap::operator[](std::string &key) {
    return keys[hash(key)];
}

float OneYearHashMap::getValue(std::string &key) {
    return keys[hash(key)]->value;
}


void OneYearHashMap::sortValues() {

   //todo implement sort function for array of nodes
}


