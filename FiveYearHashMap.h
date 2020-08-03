//
// Created by e2sho on 7/24/2020.
//


#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


class FiveYearHashMap
{

	
public:
	std::vector<std::string> dates;
	const static int days = 31 * 12;//372
	int size;//value node input tracker, should be same as numlines at end
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
	ValueNode** values = nullptr;
    FiveYearHashMap(std::string& file, std::string& name);
    void setPair(std::string& key, float value);
    int hash(std::string& key);
    std::string reverseHash(int hashedKey);
    ValueNode* operator[] (std::string& key);
    float getValue(std::string& key);
    void importAll(std::string &file, std::string& name);

    ~FiveYearHashMap();


private:
    float setAvgValue();
    int numlines;//value node setter
    void sortValues();
    const static int numValues = 619041;//numValues in data set
   


    //need to implement the big three
};



