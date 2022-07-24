// Binomial Tree Header File
// Zachary Gruber
// Vanderbilt University
// 07/13/2022

#ifndef CS_TREE_H
#define CS_TREE_H

#include <cstdint>

using namespace std;

struct Node{
    double stock_price,exercise_value,payoff_value,alive_value,final_value,
            time;
};

class Tree{

public:

    Tree(double stock_price, double strike_price, double risk_free_rate,
         double vol, double time, uint32_t height, bool type);

    ~Tree();

    void calculateAlives(double rrf, double up, double down, double tstep, uint32_t alive);

    void print();

    static double max(double one, double two);

private:
    Node** tree;
    uint32_t cols;
};

#endif //CS_TREE_H

