#include "Pirate.h"

Pirate::Pirate(int pirateId, int treasure)
    : id(pirateId), treasure(treasure), ship(nullptr), next_pirate(nullptr), prev_pirate(nullptr) {}

void Pirate::setTreasure(int treasure) {
    this->treasure = treasure;
}

int Pirate::getTreasure() const {
    return treasure;
}

void Pirate::setShip(AVLNode<Ship*>* ship) {
    this->ship = ship;
}

AVLNode<Ship*>* Pirate::getShip() const {
    return ship;
}

void Pirate::setNext(Pirate* next_pirate) {
    this->next_pirate = next_pirate;
}

Pirate* Pirate::getNext() const {
    return next_pirate;
}

void Pirate::setPrev(Pirate* prev_pirate) {
    this->prev_pirate = prev_pirate;
}

Pirate* Pirate::getPrev() const {
    return prev_pirate;
}
