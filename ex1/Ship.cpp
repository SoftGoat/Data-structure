#include "../AVLTree_boaz.h"
#include <iostream>
#include "Pirate.h"
#include "wet1util.h"
class Pirate; // Forward declaration of the Pirate class

class Ship{

private:
    int m_shipId;
    int m_cannons;
    int m_treasure;
    AVLTree<Pirate> m_pirates;
    Pirate* m_richestPirate;

public:
    StatusType add_ship(int shipId, int cannons){

    }
    StatusType remove_ship(int shipId){

    }
    StatusType add_pirate(int pirateId , int shipId, int treasure){

    }
    StatusType remove_pirate(int pirateId){

    }
    StatusType treason(int sourceShipId, int destShipId){

    }
    StatusType update_pirate_treasure(int pirateId , int change){

    }




};