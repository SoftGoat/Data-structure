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
    bool add_pirate(Pirate* pirate){
        if(m_pirates.insert(pirate)){
            return false;
        }
        pirate->setTreasure(pirate->getTreasure() + m_treasureBonus);
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
        return true;
    }
    bool remove_pirate(Pirate* pirate){
        if(crewSize == 0){
            return false;
        }
        if(pirate == m_pirateWithMostTimeServed){
            m_pirateWithMostTimeServed = pirate->getNext();
        }
        else{
            pirate->getPrev()->setNext(pirate->getNext());        
        }
        pirate->setTreasure(pirate->getTreasure() + m_treasureBonus); // return the treasure to the pirate
        m_pirates.remove(pirate);
        if(m_richestPirate == pirate){
            m_richestPirate = nullptr;
            if(!m_pirates.isEmpty()){
                m_richestPirate = m_pirates.findMaxNode()->getData();
            }
        }

        crewSize--;
        return true;

    }
    bool treason(Ship* other){
        if(crewSize == 0){
            return false;
        }
        m_pirateWithMostTimeServed->setTreasure(m_pirateWithMostTimeServed->getTreasure() + m_treasureBonus-other->treasureBonus());
        other->add_pirate(m_pirateWithMostTimeServed);
        remove_pirate(m_pirateWithMostTimeServed);
        return true;

    }
    bool update_pirate_treasure(Pirate* pirate , int change){
        if(m_pirates.search(pirate)==nullptr){
            return false;
        }
        m_pirates.search(pirate)->getData()->setTreasure(pirate->getTreasure() + change);
        return true;
    }

    int getId(){
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

    bool empty(){
        return crewSize == 0;
    }

    int getCrewSize(){
        return crewSize;
    }

    void setTreasureBonus(int treasure){
        m_treasureBonus = treasure;
    }
    BattleResult battle(Ship* other){
        if(std::min(crewSize,m_cannons) > std::min(other->crewSize,other->m_cannons)){
            other->setTreasureBonus(other->treasureBonus() - this->getCrewSize());
            this->setTreasureBonus(this->treasureBonus() + other->getCrewSize());
            return BattleResult::WIN;
        }
        if(std::min(crewSize,m_cannons) < std::min(other->crewSize,other->m_cannons)){
            this->setTreasureBonus(this->treasureBonus() - other->getCrewSize());
            other->setTreasureBonus(other->treasureBonus() + this->getCrewSize());
            return BattleResult::LOSS;
        }
        return BattleResult::TIE;
    }

};