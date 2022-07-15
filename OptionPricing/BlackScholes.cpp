// Black Scholes Implementation
// Zachary Gruber
// 07/13/2022

#include "iostream"
#include "cmath"
#include "BlackScholes.h"

using namespace std;

BlackScholes::BlackScholes(double stock, double strike, double rf_rate, double volatility, double
t, bool style):stock_price(stock), strike_price(strike), risk_free_rate(rf_rate), vol(volatility)
,time(t), type(style){

    //declare intermediary values
    double d1 = (log(stock/strike) + ((rf_rate + (.5 * vol * vol)) * time)) / (vol*sqrt(time));
    double d2 = d1 - (vol * sqrt(time));
    double n_d1;
    double n_d2;

    if(type){
        n_d1 = normalCDF(d1);
        n_d2 = normalCDF(d2);
        price = (stock * n_d1) - strike * (exp(-1 * rf_rate * time)) * n_d2;
    }
    else{
        n_d1 = normalCDF(-1 * d1);
        n_d2 = normalCDF(-1 * d2);
        price = (strike * (exp(-1 * rf_rate * time)) * n_d2) - (stock * n_d1);
    }

}

void BlackScholes::calculateGreeks(){
    cout << "not yet implemented";
    double delta=0,gamma=0,theta=0,vega=0,rho=0;
    cout << "Delta: " << delta;
    cout << "\nGamma: " << gamma;
    cout << "\nTheta: " << theta;
    cout << "\nVega: " << vega;
    cout << "\nRho: " << rho << "\n";
}

void BlackScholes::print(){
    cout << "\nPrice: " << price << "\n";

}

double BlackScholes::normalCDF(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

