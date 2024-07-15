#include "Pirate.h"

class Ship; // Forward declaration of the Ship class

Pirate::Pirate(int pirateId, int t)
    : id(pirateId), treasure(t), ship(nullptr), next_pirate(nullptr), prev_pirate(nullptr) {}

void Pirate::setTreasure(int t) {
    this->treasure = t;
}

int Pirate::getTreasure() const {
    return treasure;
}

void Pirate::setShip(AVLNode<Ship*>* new_ship) {
    this->ship = new_ship;
}

AVLNode<Ship*>* Pirate::getShip() const {
    return ship;
}

void Pirate::setNext(Pirate* next_pirate) {
    this->next_pirate = next_pirate;
    if(next_pirate != nullptr){
        next_pirate->prev_pirate = this;
    }
}

Pirate* Pirate::getNext() const {
    return next_pirate;
}

void Pirate::setPrev(Pirate* prev_pirate) {
    this->prev_pirate = prev_pirate;
    if(prev_pirate != nullptr){
        prev_pirate->next_pirate = this;
    }
}

Pirate* Pirate::getPrev() const {
    return prev_pirate;
}

int Pirate::getId() const {
    return id;
}


