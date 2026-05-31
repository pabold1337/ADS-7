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
    
    first->light = false;
    Car* current = first->next;
    countOp++;
    
    int steps = 1;
    bool completed = false;
    
    while (!completed) {
        while (!current->light && current != first) {
            current = current->next;
            countOp++;
            steps++;
        }
        
        if (current == first) {
            completed = true;
        } else {
            current->light = false;
            current = current->next;
            countOp++;
            steps++;
        }
    }
    
    return steps;
}

int Train::getOpCount() {
    return countOp;
}
