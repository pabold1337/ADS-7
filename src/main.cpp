// Copyright 2022 NNTU-CS
#include <iostream>
#include <ctime>
#include "train.h"

unsigned getRandomBit(unsigned& rnd) {
  rnd = rnd * 1664525u + 1013904223u;
  return (rnd >> 16) & 1;
}

void fillWagons(Train& train, int amount, int scenario, unsigned& seed) {
  for (int idx = 0; idx < amount; ++idx) {
    bool lampState;
    if (scenario == 0) {
      lampState = false;
    } else if (scenario == 1) {
      lampState = true;
    } else {
      lampState = getRandomBit(seed);
    }
    train.addCar(lampState);
  }
}

int main() {
  unsigned randSeed = static_cast<unsigned>(std::time(nullptr));

  std::cout << "n\tall_off\tall_on\trandom\n";

  for (int wagons = 2; wagons <= 100; wagons += 2) {
    Train trainOff;
    fillWagons(trainOff, wagons, 0, randSeed);
    trainOff.getLength();

    Train trainOn;
    fillWagons(trainOn, wagons, 1, randSeed);
    trainOn.getLength();

    Train trainRand;
    fillWagons(trainRand, wagons, 2, randSeed);
    trainRand.getLength();

    std::cout << wagons << "\t"
              << trainOff.getOpCount() << "\t"
              << trainOn.getOpCount() << "\t"
              << trainRand.getOpCount() << "\n";
  }

  return 0;
}
