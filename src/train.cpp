// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (first == nullptr) {
        first = newCar;
        newCar->next = newCar;
        newCar->prev = newCar;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (first == nullptr) return 0;

    countOp = 0;

    bool firstLight = first->light;

    first->light = false;
    countOp++;

    Car* current = first->next;
    countOp++;
    int steps = 1;

    while (current != first) {
        if (current->light) {
            current->light = false;
            countOp++;
        }
        current = current->next;
        countOp++;
        steps++;
    }

    first->light = firstLight;
    countOp++;

    return steps;
}

int Train::getOpCount() {
    return countOp;
}
