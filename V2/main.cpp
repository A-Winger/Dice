#include "dice.h"
using namespace std;

int main(){
    bool exit = false;
    char c;
    cout << "\nWelcome to NAME.";
    while(!exit){
        cout << "\nPress 'M' to print the menu, 'Q' to quit.";
        cout << "\n--> ";
        cin >> c;
        c = tolower(c);
        switch(c){
            case 'q':{ exit = true; break; }
            case 'm':{ menu(); break; }
            case 'a':{ play(); break; }
            default: {
                cerr << "\nUnknown command, please retry: ";
                cin >> c;
                c = tolower(c);
            }
        }
    }
    cout << "\nGoodbye.\n";
    return 0;
}

void menu(){
    cout << endl;
    cout << "\nMenu:";
    cout << "\nA)\tPlay.";
    cout << "\nB)\tPrint last roll.";
    cout << "\nQ)\tQuit.";
    cout << endl;
}

void gamemenu(){
    cout << "\n\nWhat type of dice?";
    cout << "\nQ)\tQuit.";
    cout << "\nA)\tThrow D4.";
    cout << "\nB)\tThrow D6.";
    cout << "\nC)\tThrow D8.";
    cout << "\nD)\tThrow D10.";
    cout << "\nE)\tThrow D12.";
    cout << "\nF)\tThrow D20.";
    cout << "\n\nHow many times?";
    cout << "\n(type) _ (times) --> ";
}

int Dice::roll(unsigned int& max){
    const unsigned int min = 1;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);   
    uniform_int_distribution<int> distribution(min, max);

    unsigned int result = distribution(generator);
    return result;
}

void Dice::saveLast(unsigned int& res){
    ofstream save("savefile.txt");
    if(save.is_open()){
        save << res;
    }
    save.close();
}

string Dice::loadLast(ifstream& save){
    string line;
    unsigned int n;
    Dice d;
    if(save.is_open()){
        while(getline(save, line) && save.good()){
            save >> line;
        } 
    }
    istringstream itmp(line);
    itmp >> n;

    d.print(n);
    save.close();
    return line;
}

void Dice::print(unsigned int& res){
    if(res < 0){
        cerr << "\nError: bad limits.\n\n";
    }else{
        cout << "\nThe result is: " << res << ".\n";
    }
}

bool play(){
    Dice d;
    char c;
    int n;
    unsigned int res, type;
    gamemenu();
    cin >> c >> n;    
    switch(c){
        case 'a': { res = d.roll(type = 4); break; }
        case 'b': { res = d.roll(type = 6); break; }
        case 'c': { res = d.roll(type = 8); break; }
        case 'd': { res = d.roll(type = 10); break; }
        case 'e': { res = d.roll(type = 12); break; }
        case 'f': { res = d.roll(type = 20); break; }
        case 'q': { return true; break; }
        default:{
            cerr << "\nUnknown command, please retry: ";
            cin >> c;
            c = tolower(c);
        }
    }
    d.saveLast(res);
    d.print(res);
    return false;
}