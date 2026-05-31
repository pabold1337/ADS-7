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

    Car* cur = first;
    bool hasLight = false;
    do {
        if (cur->light) {
            hasLight = true;
            break;
        }
        cur = cur->next;
        countOp++; // переход
    } while (cur != first);

    // Случай 1: все лампочки выключены
    if (!hasLight) {
        int len = 0;
        cur = first;
        do {
            cur->light = true;
            countOp++;
            len++;
            cur = cur->next;
            if (cur != first) countOp++;
        } while (cur != first);
        return len;
    }

    if (first->light) {
        first->light = false;
        countOp++;
    }
    Car* current = first->next;
    countOp++;
    int steps = 1;

    while (!current->light) {
        current = current->next;
        countOp++;
        steps++;
    }

    Car* marker = current;
    int length = 1;

    marker->light = false;
    countOp++;

    current = marker->next;
    countOp++;
    while (current != marker) {
        length++;
        current = current->next;
        countOp++;
    }

    return length;
}

int Train::getOpCount() {
    return countOp;
}
