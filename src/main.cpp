// Copyright 2022 NNTU-CS
#include "train.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <random>
#include <vector>

Train createTrain(int length, const std::vector<bool>& lights) {
    Train train;
    for (int i = 0; i < length; ++i) {
        train.addCar(lights[i]);
    }
    return train;
}

int runExperiment(int length, const std::vector<bool>& lights) {
    Train train = createTrain(length, lights);
    train.getLength();
    return train.getOpCount();
}

double averageExperiment(int length, const std::vector<bool>& lights,
                         int iterations) {
    long long totalOps = 0;
    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<bool> shuffledLights = lights;
        if (lights.size() > 1) {
            unsigned int seed = static_cast<unsigned int>(
                std::chrono::system_clock::now().time_since_epoch().count()
                + iter);
            std::shuffle(shuffledLights.begin(), shuffledLights.end(),
                         std::mt19937(seed));
        }
        totalOps += runExperiment(length, shuffledLights);
    }
    return static_cast<double>(totalOps) / iterations;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    std::ofstream csvFile("results.csv");
    csvFile << "Length;AllOff;AllOn;Random\n";
    for (int length = 2; length <= 1000; length += 2) {
        std::vector<bool> allOff(length, false);
        double avgOff = averageExperiment(length, allOff, 100);
        std::vector<bool> allOn(length, true);
        double avgOn = averageExperiment(length, allOn, 100);
        std::vector<bool> random(length);
        for (int i = 0; i < length; ++i) {
            random[i] = dis(gen);
        }
        double avgRandom = averageExperiment(length, random, 100);
        csvFile << length << ";" << avgOff << ";" << avgOn << ";"
                << avgRandom << "\n";
    }
    csvFile.close();
    return 0;
}
