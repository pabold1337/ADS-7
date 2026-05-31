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

    if (first->light) {
        first->light = false;
        countOp++;
    }

    Car* current = first->next;
    countOp++;

    while (!current->light) {
        current = current->next;
        countOp++;
    }

    Car* marker = current;
    int length = 1;

    marker->light = false;
    countOp++;

    current = marker->next;
    countOp++;

    while (true) {
        while (!current->light) {
            current = current->next;
            countOp++;
        }

        length++;

        if (current == marker) {
            break;
        }

        current->light = false;
        countOp++;
        current = current->next;
        countOp++;
    }

    return length;
}

int Train::getOpCount() {
    return countOp;
}
