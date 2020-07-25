//
// Created by e2sho on 7/24/2020.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <string>


class OneYearHashMap
{
public:
    class KeyNode
    {
    private:
        int hashedKey;
    public:
        float value;
        KeyNode(int hashedKey, float value);
        bool operator< (const KeyNode* a);
        bool operator> (const KeyNode* a);
        bool operator == (const KeyNode* a);
    };

    OneYearHashMap(int year);
    void setPair(std::string& key, float& value);
    int hash(std::string& key);
    std::string reverseHash(int hashedKey);
    KeyNode* operator[] (std::string& key);
    float getValue(std::string& key);


private:
    void sortValues();
    int size = 0;
    const static int days = 372;
    KeyNode* keys[days] = {nullptr};
    KeyNode* values[days] = {nullptr};
    int year;
};


OneYearHashMap::KeyNode::KeyNode(int hashedKey, float value) {
    this->hashedKey = hashedKey;
    this->value = value;
}

bool OneYearHashMap::KeyNode::operator<(const OneYearHashMap::KeyNode* a) {
    return this->value < a->value;
}

bool OneYearHashMap::KeyNode::operator>(const OneYearHashMap::KeyNode* a) {
    return this->value > a->value;
}

bool OneYearHashMap::KeyNode::operator==(const OneYearHashMap::KeyNode *a) {
    return this->value == a->value;
}

OneYearHashMap::OneYearHashMap(int year) {
    this->year = year;
}
void OneYearHashMap::setPair(std::string &key, float &value) {

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

    keys[hash(key)] = new KeyNode(hash(key), value);
    values[size] = keys[hash(key)];
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

OneYearHashMap::KeyNode *OneYearHashMap::operator[](std::string &key) {
    return keys[hash(key)];
}

float OneYearHashMap::getValue(std::string &key) {
    return keys[hash(key)]->value;
}

void OneYearHashMap::sortValues() {

    std::sort(values, values+size,
              [](const KeyNode* a, const KeyNode* b)->bool
              {
                  return a->value > b->value;
              });
}


