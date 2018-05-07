#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <fstream>
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
private:
    unsigned int min = 1;
    unsigned int max;
};

void menu();
void gamemenu();
void play();

#endif