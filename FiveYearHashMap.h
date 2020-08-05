//
// Created by e2sho on 7/24/2020.
//


#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#pragma once

class FiveYearHashMap
{


public:

    const static int days = 31 * 12;//372, days in my modified calendar
    int size;
    float averageValue;
    class ValueNode
    {
    private:
        int hashedKey;
    public:
        float value;
        ValueNode(int hashedKey, float value);
        bool operator< (const ValueNode* a);
        bool operator> (const ValueNode* a);
        bool operator == (const ValueNode* a);
    };
    //prevents collisions
    class KeyNode
    {
    public:
        int year;
        KeyNode* nextNode = nullptr;
        ValueNode* theValue = nullptr;
        KeyNode(int year, ValueNode* theValue, KeyNode* nextNode);
        bool operator< (const KeyNode* a);
        bool operator> (const KeyNode* a);
        bool operator == (const KeyNode* a);
        ~KeyNode();
    };

    KeyNode* keys[days] = { nullptr };
    std::vector<ValueNode*> values;
    FiveYearHashMap(std::ifstream& fin,  std::string name, std::ifstream::streampos& track);
    void setPair(std::string& key, float value);
    int hash(std::string& key);
    std::string reverseHash(int hashedKey);
    ValueNode* operator[] (std::string key);
    float getValue(std::string key);

    ~FiveYearHashMap();


private:
    float setAvgValue();
    int numlines;//value node setter
    void sortValues();
};
