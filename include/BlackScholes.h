// Black Scholes Header File
// Zachary Gruber
// Vanderbilt University
// 07/13/2022

#ifndef CS_BLACKSCHOLES_H
#define CS_BLACKSCHOLES_H

using namespace std;

class BlackScholes{

public:

    /**
     * Constructs a new BlackScholes object to calculate price
     *
     * @param stock - current stock price from inputted by user
     * @param strike - desired strike inputted by user
     * @param rf_rate - risk free rate
     * @param vol - implied vol measured in standard deviations
     * @param time - the time till expiry (arbitrary units)
     * @patam type
     * @return address of obj
     */
    BlackScholes(double stock, double strike, double rf_rate, double vol, double time, bool type);

    /**
     * Prints delta gamma, theta, vega, and rho
     *
     * @param none
     * @return none
     */
    void Greeks();

    /**
     * Simple CDF for standard normal distribution using the error function
     *
     * @param value - the end point of the cumulative area on the normal distribution
     * @return the left tail area
     */
    double normalCDF(double value);

    /**
     * Prints the calculated option price
     *
     * @param none
     * @return none
     */
    void print();

private:
    double stock_price, strike_price, risk_free_rate, vol, time, price;
    bool type;
};
#endif //CS_BLACKSCHOLES_H
