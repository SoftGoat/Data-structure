#include "Ship.h"
#include "Pirate.h"

Ship::Ship(int shipId, int cannons)
    : m_shipId(shipId), m_cannons(cannons), m_treasureBonus(0), m_crewSize(0), 
      m_richestPirate(nullptr), m_pirateWithMostTimeServed(nullptr), m_pirateWithLeastTimeServed(nullptr), 
      m_piratesOrderdById(new AVLTree<Pirate*, Pirate::Comparator>()) {}

Ship::~Ship() {
    delete m_piratesOrderdById;
}

bool Ship::add_pirate(Pirate* pirate) {
    if (m_pirates.insert(pirate) == nullptr) {
        return false;
    }
    pirate->setTreasure(pirate->getTreasure() + m_treasureBonus);
    if (m_crewSize == 0) {
        m_pirateWithMostTimeServed = pirate;
        m_pirateWithLeastTimeServed = pirate;
        m_richestPirate = pirate;
    } else {
        m_pirateWithLeastTimeServed->setNext(pirate);
        m_pirateWithLeastTimeServed = pirate;
    }
    if (m_richestPirate == nullptr || pirate->getTreasure() > m_richestPirate->getTreasure()) {
        m_richestPirate = pirate;
    }
    m_crewSize++;
    return true;
}

bool Ship::remove_pirate(Pirate* pirate) {
    if (m_crewSize == 0) {
        return false;
    }
    if (pirate == m_pirateWithMostTimeServed) {
        m_pirateWithMostTimeServed = pirate->getNext();
    } else {
        if (pirate->getPrev() != nullptr) {
            pirate->getPrev()->setNext(pirate->getNext());
        }
    }
    pirate->setTreasure(pirate->getTreasure() + m_treasureBonus); // return the treasure to the pirate
    m_pirates.remove(pirate);
    if (m_richestPirate == pirate) {
        m_richestPirate = m_richestPirate->getNext(); // This line is risky. Need better way to find new richest pirate.
    }
    pirate->setNext(nullptr);
    pirate->setPrev(nullptr);
    m_crewSize--;
    return true;
}

bool Ship::treason(Ship* other) {
    if (m_crewSize == 0) {
        return false;
    }
    Pirate* temp = m_pirateWithMostTimeServed;
    temp->setTreasure(temp->getTreasure() + m_treasureBonus - other->getTreasureBonus());
    if (!other->add_pirate(temp)) {
        return false;
    }
    if (!remove_pirate(temp)) {
        other->remove_pirate(temp); // if the remove failed?
        return false;
    }
    return true;
}

bool Ship::update_pirate_treasure(Pirate* pirate, int change) {
    AVLNode<Pirate*>* node = m_pirates.search(pirate);
    if (node == nullptr) {
        return false;
    }
    node->getData()->setTreasure(pirate->getTreasure() + change);
    richPirateChange(node->getData());
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

AVLTree<Pirate*, Pirate::Comparator>* Ship::getPirates() {
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

bool Ship::setPirateTreasure(Pirate* pirate, int treasure) {
    AVLNode<Pirate*>* node = m_pirates.search(pirate);
    if (node == nullptr) {
        return false;
    }
    node->getData()->setTreasure(treasure);
    richPirateChange(node->getData());
    return true;
}

int Ship::getPirateTreasure(Pirate* pirate) const {
    return pirate->getTreasure() + m_treasureBonus;
}

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

bool Ship::richPirateChange(Pirate* pirate) {
    if (pirate == nullptr) {
        return false;
    }
    if (m_richestPirate == pirate) {
        return false;
    }
    if (pirate->getTreasure() > m_richestPirate->getTreasure()) {
        if (pirate->getNext() != nullptr) {
            pirate->getPrev()->setNext(pirate->getNext());
        } else {
            pirate->getPrev()->setNext(nullptr);
        }
        pirate->setNext(m_richestPirate);
        m_richestPirate = pirate;
    }
    return true;
}
