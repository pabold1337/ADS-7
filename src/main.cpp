// Copyright 2022 NNTU-CS
#include "train.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> dist(0, 1);

Train createTrain(int n, int mode) {
    Train train;
    if (mode == 0) {
        for (int i = 0; i < n; ++i) train.addCar(false);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) train.addCar(true);
    } else {
        for (int i = 0; i < n; ++i) train.addCar(dist(rng) == 1);
    }
    return train;
}

void runExperiment(int maxN, const std::string& fileOff, 
                   const std::string& fileOn, const std::string& fileRand) {
    std::ofstream fOff(fileOff), fOn(fileOn), fRand(fileRand);
    fOff << "n,ops\n"; fOn << "n,ops\n"; fRand << "n,ops\n";
    
    for (int n = 2; n <= maxN; ++n) {
        Train tOff = createTrain(n, 0);
        tOff.getLength();
        fOff << n << "," << tOff.getOpCount() << "\n";
        
        Train tOn = createTrain(n, 1);
        tOn.getLength();
        fOn << n << "," << tOn.getOpCount() << "\n";
        
        Train tRand = createTrain(n, 2);
        tRand.getLength();
        fRand << n << "," << tRand.getOpCount() << "\n";
    }
}

void generateGnuplotScript() {
    std::ofstream gp("plot.gp");
    gp << "set terminal png size 1024,768\n";
    gp << "set output 'result/plot.png'\n";
    gp << "set title 'Dependency of operations on train length'\n";
    gp << "set xlabel 'Number of cars n'\n";
    gp << "set ylabel 'Number of operations countOp'\n";
    gp << "set grid\n";
    gp << "set key left top\n";
    gp << "f_off(x) = a_off*x*x + b_off*x + c_off\n";
    gp << "fit f_off(x) 'data_off.csv' using 1:2 via a_off,b_off,c_off\n";
    gp << "f_on(x) = a_on*x*x + b_on*x + c_on\n";
    gp << "fit f_on(x) 'data_on.csv' using 1:2 via a_on,b_on,c_on\n";
    gp << "f_rand(x) = a_rand*x*x + b_rand*x + c_rand\n";
    gp << "fit f_rand(x) 'data_random.csv' using 1:2 via a_rand,b_rand,c_rand\n";
    gp << "plot 'data_off.csv' using 1:2 title 'All lights off' with points pt 7, \\\n";
    gp << "     f_off(x) title 'Trend (off) ~ n^2' with lines, \\\n";
    gp << "     'data_on.csv' using 1:2 title 'All lights on' with points pt 9, \\\n";
    gp << "     f_on(x) title 'Trend (on) ~ n^2' with lines, \\\n";
    gp << "     'data_random.csv' using 1:2 title 'Random' with points pt 5, \\\n";
    gp << "     f_rand(x) title 'Trend (random) ~ n^2' with lines\n";
    gp.close();
    system("gnuplot plot.gp");
}

int main() {
    int maxN = 150;
    runExperiment(maxN, "data_off.csv", "data_on.csv", "data_random.csv");
    generateGnuplotScript();
    return 0;
}
