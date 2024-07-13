#include "Ship.h"
#include "Pirate.h"



    Ship::Ship(int shipId, int cannons) {
        m_shipId = shipId;
        m_cannons = cannons;
        m_treasureBonus = 0;
        m_crewSize = 0;
        m_richestPirate = nullptr;
        m_pirateWithMostTimeServed = nullptr;
        m_pirateWithLeastTimeServed = nullptr;
        m_piratesOrderdById = new AVLTree<Pirate*>();
    }
    Ship::~Ship(){
    }
    bool Ship::add_pirate(Pirate* pirate){
        if(m_pirates.insert(pirate)==nullptr){
            return false;
        }
        pirate->setTreasure(pirate->getTreasure() + m_treasureBonus);
        if(m_crewSize == 0 || pirate->getTreasure() > m_richestPirate->getTreasure()){
            m_richestPirate = pirate;
        }
        if(m_crewSize == 0){
            m_pirateWithMostTimeServed = pirate;
            m_pirateWithLeastTimeServed = pirate;
        }
        else{
            m_pirateWithLeastTimeServed->setNext(pirate);
            m_pirateWithLeastTimeServed = pirate;
        }
        m_crewSize++;
        return true;
    }
    bool Ship::remove_pirate(Pirate* pirate){
        if(m_crewSize == 0){
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

        m_crewSize--;
        return true;

    }
    bool Ship::treason(Ship* other){
        if(m_crewSize == 0){
            return false;
        }
        m_pirateWithMostTimeServed->setTreasure(m_pirateWithMostTimeServed->getTreasure() + m_treasureBonus-other->getTreasureBonus());
        other->add_pirate(m_pirateWithMostTimeServed);
        remove_pirate(m_pirateWithMostTimeServed);
        return true;

    }
    bool Ship::update_pirate_treasure(Pirate* pirate , int change){
        if(m_pirates.search(pirate)==nullptr){
            return false;
        }
        m_pirates.search(pirate)->getData()->setTreasure(pirate->getTreasure() + change);
        return true;
    }

    int Ship::getId() const {
        return m_shipId;
    }
    int Ship::getCannons() const {
        return m_cannons;
    }
    int Ship::getTreasureBonus() const {
        return m_treasureBonus;
    }
    Pirate* Ship::getRichestPirate() const {
        return m_richestPirate;
    }
    AVLTree<Pirate*>* Ship::getPirates() {
        return m_piratesOrderdById;
    }
    
    bool Ship::empty() const {
        return m_crewSize == 0;
    }
    
    int Ship::getCrewSize() const {
        return m_crewSize;
    }
    
    void Ship::setTreasureBonus(int treasure) {
        m_treasureBonus = treasure;
    }
    
    BattleResult Ship::battle(Ship* other) {
        if(std::min(m_crewSize, m_cannons) > std::min(other->m_crewSize, other->m_cannons)) {
            other->setTreasureBonus(other->getTreasureBonus() - this->getCrewSize());
            this->setTreasureBonus(this->getTreasureBonus() + other->getCrewSize());
            return BattleResult::WIN;
        }
        if(std::min(m_crewSize, m_cannons) < std::min(other->m_crewSize, other->m_cannons)) {
            this->setTreasureBonus(this->getTreasureBonus() - other->getCrewSize());
            other->setTreasureBonus(other->getTreasureBonus() + this->getCrewSize());
            return BattleResult::LOSS;
        }
        return BattleResult::TIE;
    }

