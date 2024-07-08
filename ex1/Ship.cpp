#include "../AVLTree_boaz.h"
#include <iostream>
#include "Pirate.h"
#include "Ship.h"
#include "wet1util.h"
class Pirate; // Forward declaration of the Pirate class

class Ship{

private:
    int m_shipId;
    int m_cannons;
    int m_treasureBonus;
    int crewSize;
    AVLTree<Pirate*> m_pirates;
    Pirate* m_richestPirate;
    Pirate* m_pirateWithMostTimeServed;
    Pirate* m_pirateWithLeastTimeServed;
    AVLTree<Pirate*>* m_piratesOrderdById;
    AVLTree<Pirate*>* m_piratesOrderdByTreasure;


public:
    Ship(int shipId, int cannons,AVLTree<Pirate*>* piratesOrderdById, AVLTree<Pirate*>* piratesOrderdByTreasure){
        m_shipId = shipId;
        m_cannons = cannons;
        m_treasureBonus = 0;
        crewSize = 0;
        m_richestPirate = nullptr;
        m_pirateWithMostTimeServed = nullptr;
        m_pirateWithLeastTimeServed = nullptr;
        m_piratesOrderdById = piratesOrderdById;
        m_piratesOrderdByTreasure = piratesOrderdByTreasure;
    }
    ~Ship(){
    
    }
    StatusType add_pirate(Pirate* pirate){
        m_pirates.insert(pirate);
        if(crewSize == 0 || pirate->getTreasure() > m_richestPirate->getTreasure()){
            m_richestPirate = pirate;
        }
        if(crewSize == 0){
            m_pirateWithMostTimeServed = pirate;
            m_pirateWithLeastTimeServed = pirate;
        }
        else{
            m_pirateWithLeastTimeServed->setNext(pirate);
            m_pirateWithLeastTimeServed = pirate;
        }
        crewSize++;
        return StatusType::SUCCESS;
    }
    StatusType remove_pirate(Pirate* pirate){
        if(crewSize == 0){
            return StatusType::FAILURE;
        }
        if(pirate == m_pirateWithMostTimeServed){
            m_pirateWithMostTimeServed = pirate->getNext();
        }
        else{
            pirate->getPrev()->setNext(pirate->getNext());        
        }
        m_pirates.remove(pirate);
        if(m_richestPirate == pirate){
            m_richestPirate = nullptr;
            if(!m_pirates.isEmpty()){
                m_richestPirate = m_pirates.findMaxNode()->getData();
            }
        }

        crewSize--;
        return StatusType::SUCCESS;

    }
    StatusType treason(int sourceShipId, int destShipId){

    }
    StatusType update_pirate_treasure(Pirate* pirate , int change){
        
    }

    int getShipId(){
        return m_shipId;
    }
    int getCannons(){
        return m_cannons;
    }
    int treasureBonus(){
        return m_treasureBonus;
    }
    Pirate* getRichestPirate(){
        return m_richestPirate;
    }
    AVLTree<Pirate*> getPirates(){
        return m_pirates;
    }




};