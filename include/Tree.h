// Binomial Tree Header File
// Zachary Gruber
// Vanderbilt University
// 07/13/2022

#ifndef CS_TREE_H
#define CS_TREE_H

#include <cstdint>

using namespace std;
//Node in the binomial tree holds the below values
struct Node{
    double stock_price,exercise_value,payoff_value,alive_value,final_value,
            time;
};

class Tree{

public:

    /**
     * Constructs a new tree object to calculate price (dynamically allocated)
     * Calculates all the exercise values for the nodes (i.e. payoff if the user decides to
     * exercise the option). Exercise defaults to 0 if the payoff is 0.
     *
     * @param stock_price - current stock price from inputted by user
     * @param strike_price - desired strike inputted by user
     * @param risk_free_rate - risk free rate inputted by user
     * @param vol - implied vol measured in standard deviations inputted by user
     * @param time - the time to expiry (arbitrary units) inputted by user
     * @param height - levels of tree (inputted by user)
     * @param type - 1 for call 0 for put inputted by user
     * @return address of obj
     */
    Tree(double stock_price, double strike_price, double risk_free_rate,
         double vol, double time, uint32_t height, bool type);

    /**
     * Destructs the tree object
     *
     * @param none
     * @return none
     */
    ~Tree();

    /**
     * Calculates and inserts the correct alive values left in the option.
     * Concludes with derivation of intrinsic value from max(exercise value, alive value) for all
     * nodes. Intuitively, the last nodes have no time value.
     *
     * @param rrf - risk free rate passed in from constructor
     * @param up - the multiplication factor from an up movement; proportional to volatility
     * @param down - the multiplication factor from a down movement; proportional to volatility
     * @param tstep - the time step from one branch to the next.
     * @param type - 1 for call 0 for put
     * @return none
     */
    void calculateAlives(double rrf, double up, double down, double tstep, uint32_t height);

     /**
     * Prints the entire binomial tree structure. Displays permutations of stock price with the
     * derived
     * intrinsic value. Displayed in highest stock price to lowest.
     *
     * @param none
     * @return none
     */
    void print();

    /**
    * Calculates the max between two values
    *
    * @param none
    * @return none
    */
    static double max(double one, double two);

private:
    Node** tree;
    uint32_t cols;
};

#endif //CS_TREE_H

