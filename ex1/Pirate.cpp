#include "Pirate.h"

class Pirate {
public:
    Pirate(int pirateId, int treasure) 
        : id(pirateId), treasure(treasure), ship(nullptr), prev_pirate(nullptr), next_pirate(nullptr) {}
    void setTreasure(int treasure) { this->treasure = treasure;}
    int getTreasure() const { return treasure;}
    void setShip(AVLNode<Ship*>* ship) {this->ship = ship;} //zohar - changed from AVLNode<Ship> to AVLNode<Ship*>
    AVLNode<Ship*>* getShip() const {return ship;} //zohar - changed from AVLNode<Ship> to AVLNode<Ship*>
    void setNext(Pirate* next_pirate) {this->next_pirate = next_pirate;}
    Pirate* getNext() const {return next_pirate;}
    void setPrev(Pirate* prev_pirate) {this->prev_pirate = prev_pirate;}
    Pirate* getPrev() const { return prev_pirate;}
    int getId() const {return id;}

private:
    int id;
    int treasure;
    AVLNode<Ship*>* ship; //zohar - changed from AVLNode<Ship> to AVLNode<Ship*>
    Pirate* next_pirate;
    Pirate* prev_pirate;
};
