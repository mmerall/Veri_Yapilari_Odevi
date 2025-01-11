#ifndef GEN_H
#define GEN_H
#include <iostream>
using namespace std;
class Gen {
public:
    string genDeger;
    Gen* sonraki;

    Gen(const string& genDeger);
};

#endif