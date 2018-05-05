#include "dice.h"
using namespace std;

int main(){
    cout << "\nInizial loading...";
    bool exit = false;
    vector<dice> Hystory;
    dice d;
    cout << "\nWelcome to Dice!";
    while(!exit){
        menu();
        int choice;
        cin >> choice;
        switch(choice){
            case 0:{
                cout << "\nGoodBye!\n";
                exit = true;
                break;
            }
            case 1:{
                d.request(d, Hystory, MAX_THROWS);
                ifstream savefile("save.txt");
                //string results = load(savefile);
                //cout << "\nResults: " << results;
                break;
            }
            case 2:{
                ifstream savefile("save.txt");
                vector<string> v = load(savefile);
                for(unsigned int i = 0; i<v.size(); i++){
                    cout << "\nRoll hystory:";
                    cout << "Roll #" << i << ": " << v[i];
                }
                break;
            }
        }
    }
    return 0;
}

void menu(){
    cout << "\n\nMenu:";
    cout << "\n1)\tRoll some dices!";
    cout << "\n2)\tCheck last roll turns.";
    cout << "\n0)\tExit.";
}

void dice::roll(dice& d){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);   
    uniform_int_distribution<int> distribution(d.min, d.max);

    d.res = distribution(generator);
    if((d.res < d.min) || (d.res > d.max)){
        roll(d);    //retry.
    }else{
        ofstream savefile("save.txt");
        save(d, savefile);
        cout << "\nThe result is: " << d.res << ".\n";
    }
}

void dice::request(dice& d, vector<dice>& h, const int N){
    int choice;
    cout << "\nWhat dice you want throw?";
    cout << "\n0)\tD4.\n1)\tD6.\n2)\tD8.\n3)\tD10.\n4)\tD12.\n5)\tD20.";
    cin >> choice;
    switch(choice){
        case 0: d.type = D4; break;
        case 1: d.type = D6; break;
        case 2: d.type = D8; break;
        case 3: d.type = D10; break;
        case 4: d.type = D12; break;
        case 5: d.type = D20; break;
        default: {
            cerr << "\nERROR: invalid input, retry.";
            request(d, h, N);     //retry
        }
    }
    cout << "\nOk, how many throws?";
    cin >> choice;
    while(choice > N){
        cerr << "\nERROR: too many throws, retry: ";
        cin >> choice;
    }
    for(int i = 0; i < choice; ++i){
        dice::roll(d);
        h.push_back(d);
    }
}

void save(vector<dice> h, ofstream& savefile){
    if(savefile.is_open()){
        int i = 0;
        while((i != MAX_THROWS) && savefile.good()){
            savefile << h[i].res << "\t" ;
            i++;
        }
        savefile << "\n";
        savefile.close();
    }
}

vector<string> load(ifstream& savefile){
    vector<string> v;
    if(savefile.is_open()){
        string line;
        while(getline(savefile, line) && savefile.good()){
            v.push_back(line);
        }
    }
    return v;
}