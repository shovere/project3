//
// Created by e2sho on 7/24/2020.
//

#ifndef HASH_ONEYEARHASHMAP_H
#define HASH_ONEYEARHASHMAP_H

#include <string>


class OneYearHashMap
{
public:
    class Node
    {
    private:
        int hashedKey;
    public:
        float value;
        Node(int hashedKey, float value);
    };

    OneYearHashMap(int year);
    void setPair(std::string& key, float& value);
    int hash(std::string& key);
    std::string reverseHash(int hashedKey);
    Node* operator[] (std::string& key);
    float getValue(std::string& key);

private:
    void sortValues();
    int size = 0;
    const static int days = 372;
    Node* keys[days] = {nullptr};
    Node* values[days] = {nullptr};
    int year;
};


#endif //HASH_ONEYEARHASHMAP_H
