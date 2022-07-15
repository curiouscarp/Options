#include <iostream>
#include <string>

#include "Tree.h"
#include "BlackScholes.h"

using namespace std;

int main() {

    double time,stock,strike,rf_rate,vol;
    bool type,model;
    cout << "Hello, World!" << std::endl;
    cout << "Welcome to the Options pricing tool\nThis calculates your put/call"
                 " using Black Scholes or binomial tree pricing.\n";

    bool done = false;
    while(!done){

//        //Gather input
//        cout << "\nPlease enter the time to maturity\n";
//        cin >> time;
//
//        cout << "\nEnter the current stock price\n";
//        cin >> stock;
//
//        cout << "\nEnter the your strike price\n";
//        cin >> strike;
//
//        cout << "\nWhat is the current risk free rate (measured in percentage points)?\n";
//        cin >> rf_rate;
//        rf_rate /= 100;
//
//        cout << "\nWhat is the implied volatility (measured in standard deviations)?\n";
//        cin >> vol;
//
//        cout << "\nLastly, is this a (1) call or (0) put?\n1 for call and 0 for put\n";
//        cin >> type;
//
//        cout << "Which pricing model would you like to use?";
//        cout << "\n1 is for Black-Scholes and  0 is for binomial";
//        cin >> model;

        time = 2;
        stock = 100;
        strike = 105;
        rf_rate = 5;
        vol = .182322;
        type = 0;
        model = 0;

        if(model){
            BlackScholes* scholes_model = new BlackScholes(stock,strike,rf_rate,vol,time,type);
            scholes_model->print();
        }
        else{
            uint32_t height;
            cout << "\nWhat height for the tree?";
            cin >> height;
            Tree* binomial_model = new Tree(stock,strike,rf_rate,vol,time,height,type);
            binomial_model->print();
        }

        bool valid_input = false;
        while(!valid_input){
            string answer;
            cout << "Done (y/n)?";
            cin >> answer;
            if(answer == "y"){
                done = true;
                valid_input = true;
            }
            else if(answer == "n"){
                done = false;
                valid_input = true;
            }
            else{
                cout << "unknown input please try again!\n";
                valid_input = false;
            }
        }
    }

    return 0;
}
