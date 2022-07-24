// Binomial Tree Implementation
// Zachary Gruber
// Vanderbilt University
// 07/13/2022

#include "iostream"
#include "cmath"
#include "../include/Tree.h"

Tree::Tree(double sp, double strike, double risk_free_rate,
           double vol, double time, uint32_t height, bool call){

    cols = height;
    //set up time step
    double step = time/(height-1);

    //allocate memory and setup tree structure
    tree = new Node* [height];
    for(int i = 0; i<height; ++i) {
        tree[i] = new Node [i + 1];
    }
    //set up the up/down values
    double uptick = exp(vol*sqrt(step));
    double downtick = exp(-1 * vol * sqrt(step));

    //set up the first node in the list
    tree[0][0].stock_price = sp;
    tree[0][0].time = 0;

    //call
    if(call){
        tree[0][0].payoff_value = sp - strike;
    }
    //put
    else{
        tree[0][0].payoff_value = strike - sp;
    }

    //do the rest of the nodes
    double tmptime = 0.0;
    for(int j = 1; j<height; ++j){
        tmptime += step;
        for(int k = 0; k<=j; ++k){
            tree[j][k].time = tmptime;
            int num_upticks = j-k;
            int num_downticks = j-num_upticks;
            tree[j][k].stock_price = sp * (pow(uptick,num_upticks)) * (pow(downtick,
                                                                            num_downticks));
            if(call){
                tree[j][k].payoff_value = tree[j][k].stock_price - strike;
            }
            else{
                tree[j][k].payoff_value = strike - tree[j][k].stock_price;
            }
            //populate the exercise values
            //essentially just the same as payoffs without the negative values.
            tree[j][k].exercise_value = max(0,tree[j][k].payoff_value);

            //alive value of the last column is 0 since the option is at expiry
            if(j==(height-1)){
                tree[j][k].alive_value = 0;
                tree[j][k].final_value = tree[j][k].exercise_value;
            }
        }
    }
    calculateAlives(risk_free_rate, uptick, downtick, step, height);
}

Tree::~Tree(){
    for(int i = 0; i<cols; ++i) {
        delete [] tree[i];
    }
}

void Tree::calculateAlives(double rrf, double up, double down, double step, uint32_t height){
    //assumes 0 for div yield and risk neutral probability, p
    double p = (exp(rrf*step) - down) / (up - down);
    //calculates alive values for all but last column
    for(int i = height-2; i>=0; --i){
        for(uint32_t j = 0; j<=i; ++j){
            tree[i][j].alive_value = (1/(1+rrf))*(p*tree[i+1][j].final_value + (1-p)
                    *tree[i+1][j+1].final_value);
            tree[i][j].final_value = max(tree[i][j].alive_value,tree[i]
            [j].exercise_value);
        }
    }
}

void Tree::print(){
    cout << "Binomial Prices:";
    for(int i = 0; i<cols; ++i){
        cout << "\n[Time: " << tree[i][0].time << "]";
        for(int j = 0; j<=i; ++j){
            cout << "\n\tStock price: " << tree[i][j].stock_price;
            cout << "\n\tOption Value: " << tree[i][j].final_value;
        }
        cout << "\n";
    }
}

double Tree::max(double one, double two){
    if(one >= two){
        return one;
    }
    else
        return two;
}


