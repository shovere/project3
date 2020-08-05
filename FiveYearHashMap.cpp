#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "FiveYearHashMap.h"

FiveYearHashMap::KeyNode::~KeyNode() {

    if (nextNode != nullptr)
    {
        delete nextNode;
        nextNode = nullptr;
    }

}


FiveYearHashMap::~FiveYearHashMap() {

    for (int i = 0; i < 372; ++i)
    {
        if (keys[i] != nullptr)
        {
            delete keys[i];
        }
    }

}

//FILE I/O is implicit here, this allows for greater ease of use and input into the map
FiveYearHashMap::FiveYearHashMap(std::ifstream& fin, std::string name, std::ifstream::streampos& track) {

    numlines = 0;
    size = 0;
    std::ifstream::streampos tempTrack;
    std::string temp;
    std::string word;


    int it;

    bool cont = false;
    bool end = false;
    float val = 0;
    std::string date;

    //uses the passed in ifstream object, allows for less passes
    //time complexity is n+tracker, where n is the number of dates in a given stock and tracker is the iterator value
    while (fin >> temp)
    {
        it = 0;
        cont = false;
        std::stringstream s(temp);
        //std::cout << temp << std::endl;
        while (getline(s, word, ','))
        {

            if (word == name && it == 6)
            {
                cont = true;
            }
            else if(word != name && it == 6)
            {
                end = true;
                break;
            }
            if (it == 0)
                date = word;
            if (it == 4)
            {
                try
                {
                    val = std::stof(word);
                }
                catch (...)
                {
                    std::cout << "Exception Caught " << word << " " << temp << std::endl;
                    cont = false;
                }
            }
            it++;

        }


        if (cont)
        {
            this->setPair(date, val);
        }
        if (end)
        {
            fin.seekg(tempTrack) >> temp;
            track = tempTrack;
            break;
        }
        tempTrack = track;
        track = fin.tellg();

    }

    averageValue = setAvgValue();
}


FiveYearHashMap::KeyNode::KeyNode(int year, ValueNode* theValue, KeyNode* nextNode) {
    this->year = year;
    this->nextNode = nextNode;
    this->theValue = theValue;
}

FiveYearHashMap::ValueNode::ValueNode(int hashedKey, float value) {
    this->hashedKey = hashedKey;
    this->value = value;
}


bool FiveYearHashMap::KeyNode::operator<(const FiveYearHashMap::KeyNode* a) {
    return this->year < a->year;
}

bool FiveYearHashMap::KeyNode::operator>(const FiveYearHashMap::KeyNode* a) {
    return this->year > a->year;
}

bool FiveYearHashMap::KeyNode::operator==(const FiveYearHashMap::KeyNode* a) {
    //note this should never happen, however comparisons may need to be made
    return this->year == a->year;
}

bool FiveYearHashMap::ValueNode::operator<(const FiveYearHashMap::ValueNode* a) {
    return this->value < a->value;
}

bool FiveYearHashMap::ValueNode::operator>(const FiveYearHashMap::ValueNode* a) {
    return this->value > a->value;
}

bool FiveYearHashMap::ValueNode::operator==(const FiveYearHashMap::ValueNode* a) {
    return this->value == a->value;
}

//O(Y), where Y is max number of years, thats worst case, best case is O(1)
void FiveYearHashMap::setPair(std::string& key, float value) {
    ValueNode* vNode = new ValueNode(hash(key), value);
    //necessary for sorting and finding dates based on value
    values.push_back(vNode);

    //allows easy access to the number of key value pairs in the map
    this->size++;
    //file IO dependent, in format 2013-12-31, the year is 2013, which gets shortened to 3
    int year = key[3] - 48;
    
    //checks if a node is in the map
    //the map utilizes a sorted linked list within each array index to avoid hashing collisions
    //this allows for considerably less memory to be wasted
    KeyNode* temp = keys[hash(key)];
    KeyNode* prevNode = nullptr;
    
    //if the very first value matches the current value in the array, create a new key value pair and store it
    if (temp == nullptr)
    {
        keys[hash(key)] = new KeyNode(year, vNode, nullptr);
        temp = nullptr;
    }
    //essentially does the same as the above, but this checks the whole list
    //the aboive is needed because it acts as an initializer when there is no value in the array
    while (temp != nullptr)
    {
        //put at end of the list
        if (temp->year > year&& temp->nextNode == nullptr)
        {
            temp->nextNode = new KeyNode(year, vNode, nullptr);
            break;
        }
        //insert ahead of the current node
        else if (temp->year < year)
        {
            if (prevNode == nullptr)
            {
                keys[hash(key)] = new KeyNode(year, vNode, temp);
            }
            else
            {
                prevNode->nextNode = new KeyNode(year, vNode, temp);
            }
            break;
        }
        //replace if duplicate key
        else if(temp->year == year)
        {
             if (prevNode == nullptr)
            {
                keys[hash(key)] = new KeyNode(year, vNode, temp->nextNode);
            }
            else
            {
                prevNode->nextNode = new KeyNode(year, vNode, temp->nextNode);
            }
            //since the former key value pair is no longer a part of the linked list anymore
            //value must be deleted, after being replaced with new node
            delete temp;
            temp = nullptr;
        }
        prevNode = temp;
        temp = temp->nextNode;
    }
    temp = nullptr;
    prevNode = nullptr;
    delete temp;
    delete prevNode;

}

int FiveYearHashMap::hash(std::string& key) {

 
    //strings must be in form XXXX-XX-XX
    int month = std::stoi(key.substr(5, 2));
    int day = std::stoi(key.substr(8, 2));

    //year is handled elswewhere, in hash collision avoidance 
    int hashKey = ((month - 1) * 31) + day - 1;
    return hashKey;
}
//O(1) time complexity
std::string FiveYearHashMap::reverseHash(int hashedKey) {
    int month = 0;
    int day = 0;
    std::string year;

    //get year 
    switch (hashedKey / 372)
    {
    case 0:
        year = "2013";
        break;
    case 1:
        if (hashedKey % 372 != 0)
            year = "2014";
        else
            year = "2013";
        break;
    case 2:
        if (hashedKey % 372 != 0)
            year = "2015";
        else
            year = "2014";
        break;
    case 3:
        if (hashedKey % 372 != 0)
            year = "2016";
        else
            year = "2015";
        break;
    case 4:
        if (hashedKey % 372 != 0)
            year = "2017";
        else
            year = "2016";
        break;
    }
    if (hashedKey % 31 != 0)
    {
        //key = 1, month = 0+1 = 1, day = 1%31 = 1, january 1st
        month = (hashedKey / 31) + 1;
        day = hashedKey % 31;
    }
    else
    {
        //key = 31, month = 31/31 = 1, day = 31 , january 31st
        month = (hashedKey / 31);
        day = 31;
    }
    return  year + "-" + std::to_string(month) + "-" + std::to_string(day);
}
//O(Y), where Y is max number of years, thats worst case, best case is O(1)
FiveYearHashMap::ValueNode* FiveYearHashMap::operator[](std::string key) {
    int year = key[3] - 48;
    KeyNode* temp = keys[hash(key)];
    while (temp != nullptr)
    {
        if (temp->year == year)
        {
            return temp->theValue;
        }
        temp = temp->nextNode;
    }
    return nullptr;
}
//O(Y), where Y is max number of years, thats worst case, best case is O(1)
float FiveYearHashMap::getValue(std::string key) {
    int year = key[3] - 48;
    KeyNode* temp = keys[hash(key)];
    while (temp != nullptr)
    {
        if (temp->year == year)
        {
            return temp->theValue->value;
        }
        temp = temp->nextNode;
    }
    return -1;
}
//nlogn time complexity
void FiveYearHashMap::sortValues() {

    std::sort(values.begin(),values.end(),
        [](const ValueNode* a, const ValueNode* b)->bool
    {
        return a->value > b->value;
    });
}
//n complexity
float FiveYearHashMap::setAvgValue()
{
    float avgCost = 0;
    for (unsigned int i = 0; i < values.size(); ++i)
    {
        avgCost += values[i]->value;
    }
    avgCost /= values.size();
    return avgCost;
}
