#include "Ship.h"
#include "Pirate.h"

Ship::Ship(int shipId, int cannons)
    : m_shipId(shipId), m_cannons(cannons), m_treasureBonus(0), m_crewSize(0), 
      m_richestPirate(nullptr), m_pirateWithMostTimeServed(nullptr), m_pirateWithLeastTimeServed(nullptr), 
      m_piratesOrderdById(new AVLTree<Pirate*, Pirate::IdComparator>()),
      m_piratesOrderdByTreasure(new AVLTree<Pirate*, Pirate::TreasureComparator>()) {}

Ship::~Ship() {
    // Deleteing the tree without freeing the pirates memory.
    m_piratesOrderdById->clearTree(false);
    m_piratesOrderdByTreasure->clearTree(false);
    delete m_piratesOrderdById;
    delete m_piratesOrderdByTreasure;
}

bool Ship::add_pirate(Pirate* pirate) {
    if(pirate == nullptr){
        return false;
    }

    // Removing the cuurent treasureBonus so that when we remove the pirate from the ship -
    // we will add the treasureBonus.
    pirate->setTreasure(pirate->getTreasure() - m_treasureBonus);

    // Insert new pirate to both trees.
    if (m_piratesOrderdById->insert(pirate) == nullptr) {
        return false;
    }
    if (m_piratesOrderdByTreasure->insert(pirate) == nullptr) {
        m_piratesOrderdById->remove(pirate); // Remove from Id tree, without deleting the memory.
        return false;
    }

    if (m_crewSize == 0) {
        m_pirateWithMostTimeServed = pirate;
        m_pirateWithLeastTimeServed = pirate;
        m_richestPirate = pirate;
    } else {
        m_pirateWithLeastTimeServed->setNext(pirate);
        pirate->setPrev(m_pirateWithLeastTimeServed);
        m_pirateWithLeastTimeServed = pirate;
    }
    // Update richest pirate if needed. 
    if (pirate->getTreasure() > m_richestPirate->getTreasure()) {
        m_richestPirate = pirate;
    }
    m_crewSize++;
    return true;
}
 
/*
    This function removes the pirate from the ship only.
    It DO NOT deletes the pirate memory!
*/
bool Ship::remove_pirate(Pirate* pirate) {
    // Check if the pirate is in the ship.
    if(m_piratesOrderdById->search(pirate) == nullptr || m_piratesOrderdById->search(pirate) == nullptr){
        return false;
    }
    // The pirate is in the ship.
    // We will remove him from the ship's pirate trees and update the relevant fields accordingly.

    m_piratesOrderdById->remove(pirate);
    m_piratesOrderdByTreasure->remove(pirate);

    // Update the Id tree so that it will keep the insert order correct.
    Pirate* next_pirate = pirate->getNext();
    Pirate* prev_pirate = pirate->getPrev();
    if(next_pirate == nullptr){
        // The pirate is the pirate with the least time served!
        m_pirateWithLeastTimeServed = prev_pirate; // Set to the pirate inserted before pirate 
        prev_pirate->setNext(nullptr);
    }
    if(prev_pirate == nullptr){
        // The pirate is the pirate with the most time served!
        m_pirateWithMostTimeServed = next_pirate;
        next_pirate->setPrev(nullptr);
    }

    m_richestPirate = m_piratesOrderdByTreasure->findMaxVal();
    m_crewSize--;

    // Dispatch the pirate from the ship.
    pirate->setNext(nullptr);
    pirate->setPrev(nullptr);
    pirate->setShip(nullptr);
    pirate->setTreasure(pirate->getTreasure() + m_treasureBonus);

    return true;
}

bool Ship::treason(Ship* other) {
    // We are assuming that the ship is not empty.

    Pirate* temp = m_pirateWithMostTimeServed;
    if (!this->remove_pirate(temp)) {
        return false;
    }
    if (!other->add_pirate(temp)) {
        this->add_pirate(temp);
        return false;
    }
    return true;
}

int Ship::getId() const {
    return m_shipId;
}

int Ship::getCannons() const {
    return m_cannons;
}

Pirate* Ship::getRichestPirate() const {
    return m_richestPirate;
}

AVLTree<Pirate*, Pirate::IdComparator>* Ship::getPiratesOrderdById() {
    return m_piratesOrderdById;
}

bool Ship::empty() const {
    return m_crewSize == 0;
}

int Ship::getCrewSize() const {
    return m_crewSize;
}

int Ship::getTreasureBonus() const {
    return m_treasureBonus;
}

void Ship::setTreasureBonus(int treasure) {
    m_treasureBonus = treasure;
}

bool Ship::setPirateTreasure(Pirate* pirate, int treasure) {
    // We will remove the pirate, update it treasure and then insert it.
    // This will promise that all the ship fields will be correct.

    if(this->remove_pirate(pirate) == false){ // The pirate is not in the ship
        return false;
    }

    pirate->setTreasure(treasure + m_treasureBonus);

    this->add_pirate(pirate);
    return true;
}

int Ship::getShipId() const{
    return m_shipId;
}

Pirate* Ship::getPirateWithMostTimeServed() const{
    return m_pirateWithMostTimeServed;
}

Pirate* Ship::getPirateWithLeastTimeServed() const{
    return m_pirateWithLeastTimeServed;
}

int Ship::getPirateTreasure(Pirate* pirate) const {
    return pirate->getTreasure() + this->m_treasureBonus;
}

// int Ship::getPirateTreasure(int pirateId) const{
//     return getPirateTreasure();
// }

BattleResult Ship::battle(Ship* other) {
    if (std::min(m_crewSize, m_cannons) > std::min(other->m_crewSize, other->m_cannons)) {
        other->setTreasureBonus(other->getTreasureBonus() - this->getCrewSize());
        this->setTreasureBonus(this->getTreasureBonus() + other->getCrewSize());
        return BattleResult::WIN;
    }
    if (std::min(m_crewSize, m_cannons) < std::min(other->m_crewSize, other->m_cannons)) {
        this->setTreasureBonus(this->getTreasureBonus() - other->getCrewSize());
        other->setTreasureBonus(other->getTreasureBonus() + this->getCrewSize());
        return BattleResult::LOSS;
    }
    return BattleResult::TIE;
}