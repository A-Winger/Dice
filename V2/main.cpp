#include "dice.h"
using namespace std;

int main(){
    bool exit = false;
    char c;
    cout << "\nWelcome to NAME.";
    while(!exit){
        menu();
        //cout << "\nPress 'M' to print the menu, 'Q' to quit.";
        cout << "\n--> ";
        cin.clear();
        cin >> c;
        c = tolower(c);
        switch(c){
            case 'q':{ exit = true; break; }
            //case 'm':{ menu(); break; }
            case 'a':{ play(); break; }
            default: { cerr << "\nWARNING: Unknown command, please pay attention!\n"; }
        }
    }
    cout << "\nGoodbye. :D\n\n";
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

void what(){
    cout << "\n\nWhat type of dice?";
    cout << "\nD4) \tThrow D4.";
    cout << "\nD6) \tThrow D6.";
    cout << "\nD8) \tThrow D8.";
    cout << "\nD10)\tThrow D10.";
    cout << "\nD12)\tThrow D12.";
    cout << "\nD20)\tThrow D20.";
    cout << "\n--> ";
}

void howMuch(){
    cout << "\n\nHow many throws? (positive integer)";
    cout << "\n--> ";
}

int Dice::roll(unsigned int& max){
    const unsigned int min = 1;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);   
    uniform_int_distribution<int> distribution(min, max);

    unsigned int result = distribution(generator);
    return result;
}

void Dice::saveLast(string& res){
    ofstream save("savefile.txt");
    if(save.is_open()){
        save << res;
    }
    save.close();
}

string Dice::loadLast(ifstream& save){
    string line;
    unsigned int n;
    //Dice d;
    if(save.is_open()){
        while(getline(save, line) && save.good()){
            save >> line;
        } 
    }
    istringstream itmp(line);
    itmp >> n;

    cout << "\nThe last throw is: " << n << ".\n";
    
    save.close();
    return line;
}

/*
void play(){
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
        case 'q': { return; }
        default:{ cerr << "\nUnknown command, please pay attention!\n"; }
    }
    d.saveLast(res);
    d.print(res);
}
*/

void play(){
    Dice d;
    string dice;
    int n;
    unsigned int res, type;
    what();
    cin >> dice;
    cin.clear();
    normalize(dice);
    Type t = diceType(dice);
    switch(t){
        case d4: { type = 4; break; }
        case d6: { type = 6; break; }
        case d8: { type = 8; break; }
        case d10: { type = 10; break; }
        case d12: { type = 12; break; }
        case d20: { type = 20; break; }
        case DICEFAIL: { cerr << "\n\nERROR: Invalid dice value.\n"; return; }
    }
    howMuch();
    cin >> n;
    cin.clear();
    if(n > 0){
        string result;
        for(int i = 0; i < n; i++){
            res = d.roll(type);
            cout << "\nRoll #" << (i + 1) << ": " << res << ".";
            ostringstream otmp;
            otmp << " " << res;
            result.append(otmp.str());
            d.saveLast(result);
        }
    }else{ cerr << "\nERROR: Invalid throws value.\n"; }
}

Type diceType(string& s){
    if(s == "d4"){
        return d4;
    }if(s == "d6"){
        return d6;
    }if(s == "d8"){
        return d8;
    }if(s == "d10"){
        return d10;
    }if(s == "d12"){
        return d12;
    }if(s == "d20"){
        return d20;
    }else{
        cerr << "\nInvalid type of dice!\n";
        return DICEFAIL;
    }
}

string normalize(string& str){
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}