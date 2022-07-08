#include <iostream>
#include <string>
#include <cmath>

using namespace std;

double normalCDF(double value);

int main() {

    double time,stock,strike,rf_rate,vol;
    bool call;
    cout << "Hello, World!" << std::endl;
    cout << "Welcome to the Black Scholes pricing tool\nThis calculates your put/call"
                 " price.\n";
    bool done = false;
    while(!done){
        cout << "\nPlease enter the time to maturity\n";
        cin >> time;

        cout << "\nEnter the current stock price\n";
        cin >> stock;

        cout << "\nEnter the your strike price\n";
        cin >> strike;

        cout << "\nWhat is the current risk free rate (measured in percentage points)?\n";
        cin >> rf_rate;
        rf_rate /= 100;

        cout << "\nWhat is the implied volatility (measured in standard deviations)?\n";
        cin >> vol;

        cout << "\nLastly, is this a (1) call or (0) put?\n1 for call and 0 for put\n";
        cin >> call;

        double d1 = (log(stock/strike) + ((rf_rate + (.5 * vol * vol)) * time)) / (vol*sqrt(time));
        double d2 = d1 - (vol * sqrt(time));

        double n_d1;
        double n_d2;
        double result;
        if(call){
            n_d1 = normalCDF(d1);
            n_d2 = normalCDF(d2);
            result = (stock * n_d1) - strike * (exp(-1 * rf_rate * time)) * n_d2;
        }
        else{
            n_d1 = normalCDF(-1 * d1);
            n_d2 = normalCDF(-1 * d2);
            result = (strike * (exp(-1 * rf_rate * time)) * n_d2) - (stock * n_d1);
        }
        cout << "\nPrice: " << result << "\n";

        double delta=0,gamma=0,theta=0,vega=0,rho=0;
        cout<< "Greeks \n";

        /**
         * to do for Avi
         */

        cout << "Delta: " << delta;
        cout << "\nGamma: " << gamma;
        cout << "\nTheta: " << theta;
        cout << "\nVega: " << vega;
        cout << "\nRho: " << rho << "\n";

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
double normalCDF(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}
