// Binomial Tree Header File
// Zachary Gruber
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

    double dumpSells(uint32_t time);

    double getOptimalSell(uint32_t time);

    void print();

    static double max(double one, double two);

private:
    Node** tree[5];
};

#endif //CS_TREE_H

