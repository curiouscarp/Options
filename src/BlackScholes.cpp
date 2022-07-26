// Black Scholes Implementation
// Zachary Gruber
// Vanderbilt University
// 07/13/2022

#include "iostream"
#include "cmath"
#include "../include/BlackScholes.h"

BlackScholes::BlackScholes(double stock, double strike, double rf_rate, double volatility, double
t, bool style):stock_price(stock), strike_price(strike), risk_free_rate(rf_rate), vol(volatility)
,time(t), type(style){

    //declare intermediary values
    double d1 = (log(stock_price/strike_price) + ((risk_free_rate + (.5 * vol * vol)) *
            time)) /
            (vol*sqrt(time));
    double d2 = d1 - (vol * sqrt(time));
    double n_d1;
    double n_d2;

    //call
    if(type){
        n_d1 = normalCDF(d1);
        n_d2 = normalCDF(d2);
        price = (stock_price * n_d1) - strike_price * (exp(-1 * risk_free_rate * time)) * n_d2;
    }
    //put
    else{
        n_d1 = normalCDF(-1 * d1);
        n_d2 = normalCDF(-1 * d2);
        price = (strike_price * (exp(-1 * risk_free_rate * time)) * n_d2) - (stock_price * n_d1);
    }

    //greeks
    double N1d1 = exp(-.5 * d1 * d1)/(sqrt(2 * M_PI));
    if(type){
        delta = n_d1;
    }
    else{
        delta = normalCDF(d1) - 1;
    }

    //calculate gamma
    gamma = N1d1/(stock_price * vol * sqrt(time));

    //calculate theta
    if(type){
        theta = ((-1 * (stock_price * N1d1 * vol)) / (2 * sqrt(time))) - (risk_free_rate *
                strike_price * exp(-1 * risk_free_rate * time) * n_d2);
        theta /= 365;
    }
    else{
        theta = ((-1 * (stock_price * N1d1 * vol)) / (2 * sqrt(time))) + (risk_free_rate *
                strike_price * exp(-1 * risk_free_rate * time) * n_d2);
        theta /= 365;
    }

    //calculate vega
    vega = .01 * (stock_price * sqrt(time) * N1d1);

    //calculate rho
    if(type){
        rho = .01 * (strike_price * time * exp(-1 * risk_free_rate * time) * n_d2);
    }
    else{
        rho = .01 * (-1 * strike_price * time * exp(-1 * risk_free_rate * time) * n_d2);
    }

}

void BlackScholes::print(){
    cout << "\nPrice: " << price << "\n";
    cout << "Delta: " << delta << "\n";
    cout << "Gamma: " << gamma << "\n";
    cout << "Theta: " << theta << "\n";
    cout << "Vega: " << vega << "\n";
    cout << "Rho: " << rho << "\n";
}

double BlackScholes::normalCDF(double value)
{
    return 0.5 * erfc(-value * M_SQRT1_2);
}

