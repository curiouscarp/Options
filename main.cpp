// Program for user input to tool
// Zachary Gruber
// Vanderbilt University
// 07/13/2022

#include <iostream>
#include <string>
#include "include/Tree.h"
#include "include/BlackScholes.h"
#include "include/generateData.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc == 1){
        double time,stock,strike,rf_rate,vol;
        bool call,model;
        cout << "Welcome to the Options pricing tool\nThis calculates your put/call"
                " using Black Scholes or binomial tree pricing.\n";

        bool done = false;
        while(!done){

            //Gather input
            cout << "\nPlease enter the time to maturity in years\n";
            cin >> time;

            cout << "\nEnter the current stock price\n";
            cin >> stock;

            cout << "\nEnter the your strike price\n";
            cin >> strike;

            cout << "\nWhat is the current risk free rate in percentage points\n";
            cin >> rf_rate;
            rf_rate /= 100;

            cout << "\nWhat is the implied volatility in annualized standard devs of log returns?\n";
            cin >> vol;

            cout << "\nLastly, is this a (1) call or (0) put?\n1 for call and 0 for put\n";
            cin >> call;

            cout << "Which pricing model would you like to use?";
            cout << "\n1 for Black-Scholes and 0 for binomial";
            cin >> model;

            if(model){
                BlackScholes* scholes_model = new BlackScholes(stock,strike,rf_rate,vol,time,call);
                scholes_model->print();
            }
            else{
                uint32_t height;
                cout << "\nWhat height for tree?";
                cin >> height;
                Tree* binomial_model = new Tree(stock,strike,rf_rate,vol,time,height,call);
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
    }
    else{
        //input strike price based on command line arg. doesn't include faulty input detection.
        int price = atoi(argv[1]);
        generate(price);
    }
    return 0;
}

