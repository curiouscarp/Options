//Generate CSV file used by python tool

#include <fstream>
#include <iostream>
#include "../include/generateData.h"
#include "../include/BlackScholes.h"

using namespace std;

int generate(int price){
    int strike = price;
    //yaxis volatility (.1 to 3) increment by .1 (30 range)
    //xaxis underlying price -20 to +20 from strike (21 range)
    double arr[630][9];
    for(int i = 10; i < 301; i+=10){
        for(int k = (strike-10); k < (strike+11); ++k){
            double volatility = i;
            volatility /= 100;
            auto* b = new BlackScholes(k,strike,.05,volatility,1,true);
            arr[k-strike+10+(21*((i/10)-1))][0] = volatility;
            arr[k-strike+10+(21*((i/10)-1))][1] = k;
            arr[k-strike+10+(21*((i/10)-1))][2] = strike;
            arr[k-strike+10+(21*((i/10)-1))][3] = b->getPrice();
            arr[k-strike+10+(21*((i/10)-1))][4] = b->getDelta();
            arr[k-strike+10+(21*((i/10)-1))][5] = b->getGamma();
            arr[k-strike+10+(21*((i/10)-1))][6] = b->getTheta();
            arr[k-strike+10+(21*((i/10)-1))][7] = b->getVega();
            arr[k-strike+10+(21*((i/10)-1))][8] = b->getRho();
        }
    }
    ofstream outfile;
    outfile.open("../Output/optionsData.csv",
                 ios::out);
    if(!outfile){
        cout << "failed to open output file";
    }
    else{
        write_csv(arr[0],630,9,outfile);
        outfile.close();
    }
    return 0;
}


void write_csv(double *a, int nrows, int ncols, ofstream &outs)
{
    //generate proper column headers
    outs << "volatility";
    outs << ',';
    outs << "underlying_price";
    outs << ',';
    outs << "strike_price";
    outs << ',';
    outs << "option_price";
    outs << ',';
    outs << "delta";
    outs << ',';
    outs << "gamma";
    outs << ',';
    outs << "theta";
    outs << ',';
    outs << "vega";
    outs << ',';
    outs << "rho";
    outs << endl;
    for (int row = 0; row < nrows; row++){
        for (int col = 0; col < ncols; col++){
            outs << *a;
            if (col < ncols-1)
                outs << ", ";
            a++;
        }
        outs << endl;
    }
}