#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
using namespace std;

const int MAX_THROWS = 10;
enum DiceType {D4, D6, D8, D10, D12, D20};

class dice {
public:
    DiceType type;
    int res;
    void request(dice&, vector<dice>&, const int);
    void roll(dice&);
private:
    int min;
    int max;
};

void menu();

//void printResult(ifstream&);
void save(dice&, ofstream&);
vector<string> load(ifstream&);

#endif