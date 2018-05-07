#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
using namespace std;

class Dice {
public:
    int roll(unsigned int&);
    void saveLast(unsigned int&);
    string loadLast(ifstream&);
    void print(unsigned int&);
};

void menu();
void gamemenu();
bool play();

#endif