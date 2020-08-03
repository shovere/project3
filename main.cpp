#include <iostream>
#include <string>
#include "FiveYearHashMap.h"
using namespace std;

int main()
{
    string file = "./all_stocks_5yr.csv";
    string name = "AAL";
    FiveYearHashMap fyhm(file, name);

    std::fstream fin;
    fin.open(file, std::ios::in);

    string date = "2013-02-08";
    cout << fyhm[date]->value << endl;

    return 0;
}
