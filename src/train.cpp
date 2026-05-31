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

    Car* start = first;
    while (start->light) {
        start = start->next;
        countOp++;
    }

    start->light = true;
    countOp++;

    Car* current = start->next;
    countOp++;
    int length = 1;

    while (current != start) {
        if (current->light) {
            current->light = false;
            countOp++;
            length++;
        }
        current = current->next;
        countOp++;
    }

    start->light = false;
    countOp++;

    return length;
}

int Train::getOpCount() {
    return countOp;
}
