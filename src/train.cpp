// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;
  Car* ptr = first->next;
  while (ptr != first) {
    Car* toDelete = ptr;
    ptr = ptr->next;
    delete toDelete;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    newCar->next = newCar;
    newCar->prev = newCar;
    first = newCar;
  } else {
    Car* back = first->prev;
    back->next = newCar;
    newCar->prev = back;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;
  countOp = 0;
  int carCount = 0;
  int litCount = 0;
  const Car* cursor = first;
  const Car* begin = first;
  do {
    carCount++;
    if (cursor->light) litCount++;
    cursor = cursor->next;
  } while (cursor != begin);
  countOp = 2 * carCount + litCount * (litCount - 1);
  return carCount;
}

int Train::getOpCount() {
  return countOp;
}
