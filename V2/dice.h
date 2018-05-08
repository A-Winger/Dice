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
    void saveLast(string&);
    string loadLast(ifstream&);
};

enum Type {d4, d6, d8, d10, d12, d20, DICEFAIL};

void menu();
void what();
void howMuch();
void play();
string normalize(string);
Type diceType(string);

#endif