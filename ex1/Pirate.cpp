#include "Pirate.h"

class Pirate {
public:
    Pirate(int pirateId, int treasure) 
        : id(pirateId), treasure(treasure), ship(nullptr), prev_pirate(nullptr), next_pirate(nullptr) {}
    void setTreasure(int treasure) { this->treasure = treasure;}
    int getTreasure() const { return treasure;}
    void setShip(AVLNode<Ship>* ship) {this->ship = ship;}
    AVLNode<Ship>* getShip() const {return ship;}
    void setNext(Pirate* next_pirate) {this->next_pirate = next_pirate;}
    Pirate* getNext() const {return next_pirate;}
    void setPrev(Pirate* prev_pirate) {this->prev_pirate = prev_pirate;}
    Pirate* getPrev() const { return prev_pirate;}

private:
    int id;
    int treasure;
    AVLNode<Ship>* ship;
    Pirate* next_pirate;
    Pirate* prev_pirate;
};
