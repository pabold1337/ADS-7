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
    int length = 0;

    Car* current = first;
    bool allOff = true;
    do {
        if (current->light) {
            allOff = false;
            break;
        }
        current = current->next;
        countOp++;
    } while (current != first);

    if (allOff) {
        current = first;
        do {
            current->light = true;
            countOp++;
            length++;
            current = current->next;
            if (current != first) countOp++;
        } while (current != first);
        return length;
    }

    if (first->light) {
        first->light = false;
        countOp++;
    }

    current = first->next;
    countOp++;
    length = 1;

    while (!current->light) {
        current = current->next;
        countOp++;
        length++;
    }

    Car* marker = current;
    int result = 1;
    marker->light = false;
    countOp++;
    
    current = marker->next;
    countOp++;

    while (true) {
        while (!current->light) {
            current = current->next;
            countOp++;
        }
        result++;
        if (current == marker) break;
        current->light = false;
        countOp++;
        current = current->next;
        countOp++;
    }

    return result;
}

int Train::getOpCount() {
    return countOp;
}
