// Black Scholes Header File
// Zachary Gruber
// Vanderbilt University
// 07/13/2022

#ifndef CS_BLACKSCHOLES_H
#define CS_BLACKSCHOLES_H

using namespace std;

class BlackScholes{

public:

    BlackScholes(double stock, double strike, double rf_rate, double vol, double time, bool type);

    void Greeks();

    double normalCDF(double value);

    void print();

private:
    double stock_price, strike_price, risk_free_rate, vol, time, price;
    bool type;
};
#endif //CS_BLACKSCHOLES_H
