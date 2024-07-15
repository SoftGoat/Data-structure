#include "pirates24b1.h"
#include "Ship.h"
#include "Pirate.h"

Ship* idToPointer(int id, const AVLNode<Ship*>* current, const AVLTree<Ship*,Ship::Comparator>& tree);
Pirate* idToPointer(int id, const AVLNode<Pirate*>* current, const AVLTree<Pirate*,Pirate::IdComparator>& tree);

Ocean::Ocean() {
    m_shipsById = AVLTree<Ship*,Ship::Comparator>();
    m_piratesById = AVLTree<Pirate*,Pirate::IdComparator>();
}

Ocean::~Ocean() {}

StatusType Ocean::add_ship(int shipId, int cannons) {
    if(shipId <= 0 || cannons < 0){
        return StatusType::INVALID_INPUT;
    }
    Ship* newShip = nullptr;
    try{
        newShip = new Ship(shipId, cannons);
    } catch (const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    if(m_shipsById.insert(newShip) == nullptr){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Ocean::remove_ship(int shipId) {
    if(shipId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Ship* ship = idToPointer(shipId, m_shipsById.getRoot(), m_shipsById);
    if(ship == nullptr || !ship->empty() || !m_shipsById.remove(ship,true)){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Ocean::add_pirate(int pirateId, int shipId, int treasure) {
    if(pirateId <= 0 || shipId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Ship* ship = idToPointer(shipId, m_shipsById.getRoot(), m_shipsById);
    if(ship == nullptr){ // No ship with shipId.
        return StatusType::FAILURE;
    }

    Pirate* newPirate = nullptr;
    try{
        newPirate = new Pirate(pirateId, treasure);
    } catch(const std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
    
    if(!ship->add_pirate(newPirate)){ // There is already a pirate with pirateId
        delete newPirate;
        return StatusType::FAILURE;
    }
    if (m_piratesById.insert(newPirate) == nullptr){
        ship->remove_pirate(newPirate);
        return StatusType::FAILURE;
    }
    newPirate->setShip(m_shipsById.search(ship)); 
    return StatusType::SUCCESS;
}

StatusType Ocean::remove_pirate(int pirateId) {
    if(pirateId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate = idToPointer(pirateId, m_piratesById.getRoot(), m_piratesById);
    if(pirate == nullptr){ // There is not pirate with id equals to pirateId
        return StatusType::FAILURE;
    }
    
    Ship* ship = pirate->getShip()->getData();
    if(!ship->remove_pirate(pirate)){
        m_piratesById.insert(pirate); // Return the pirate.
        return StatusType::FAILURE;
    }
    m_piratesById.remove(pirate, true);
    return StatusType::SUCCESS;
}

StatusType Ocean::treason(int sourceShipId, int destShipId) {
    if (sourceShipId <= 0 || destShipId <= 0 || sourceShipId == destShipId){
        return StatusType::INVALID_INPUT;
    }
    Ship* sourceShip = idToPointer(sourceShipId, m_shipsById.getRoot(), m_shipsById);
    Ship* destShip = idToPointer(destShipId, m_shipsById.getRoot(), m_shipsById);
    if(sourceShip == nullptr || destShip == nullptr || sourceShip->empty()){
        return StatusType::FAILURE;
    }
    if(!sourceShip->treason(destShip)){
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Ocean::update_pirate_treasure(int pirateId, int change) {
    if (pirateId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate = idToPointer(pirateId, m_piratesById.getRoot(), m_piratesById);
    if(pirate == nullptr){
        return StatusType::FAILURE;
    }
    if(pirate->getShip()== nullptr){
        return StatusType::FAILURE;
    }

    // We will update the pirate treasure through his ship to ensure correct structure -
    // of the ship and correct trasure val(because of the treasure-bonus of the ship).
    Ship* ship = pirate->getShip()->getData();
    int newTreasure = ship->getPirateTreasure(pirate) + change;
    ship->setPirateTreasure(pirate, newTreasure);
    return StatusType::SUCCESS;
}

output_t<int> Ocean::get_treasure(int pirateId) {
    if (pirateId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Pirate* pirate = idToPointer(pirateId, m_piratesById.getRoot(), m_piratesById);
    if(pirate == nullptr){
        return output_t<int>(StatusType::FAILURE);
    }
    if(pirate->getShip() == nullptr){
        return output_t<int>(pirate->getTreasure());
    }
    Ship* ship = pirate->getShip()->getData();
    return output_t<int>(ship->getPirateTreasure(pirate));
}

output_t<int> Ocean::get_cannons(int shipId) {
    if (shipId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Ship* ship = idToPointer(shipId, m_shipsById.getRoot(), m_shipsById);
    if(ship == nullptr){
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(ship->getCannons());
}

output_t<int> Ocean::get_richest_pirate(int shipId) {
    if (shipId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Ship* ship = idToPointer(shipId, m_shipsById.getRoot(), m_shipsById);
    if(ship == nullptr){
        return output_t<int>(StatusType::FAILURE);
    }
    Pirate* richestPirate = ship->getRichestPirate();
    if(richestPirate == nullptr){
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(richestPirate->getId());
}

StatusType Ocean::ships_battle(int shipId1, int shipId2) {
    if (shipId1 <= 0 || shipId2 <= 0 || shipId1 == shipId2){
        return StatusType::INVALID_INPUT;
    }
    Ship* ship1 = idToPointer(shipId1, m_shipsById.getRoot(), m_shipsById);
    Ship* ship2 = idToPointer(shipId2, m_shipsById.getRoot(), m_shipsById);
    if(ship1 == nullptr || ship2 == nullptr){
        return StatusType::FAILURE;
    }
    ship2->battle(ship1);
    return StatusType::SUCCESS;
}

Pirate* idToPointer(int id, const AVLNode<Pirate*>* current, const AVLTree<Pirate*,Pirate::IdComparator>& tree) {   // Tree parameter is useless
    if(current == nullptr || current->getData() == nullptr){
        return nullptr;
    }
    if(current->getData()->getId() == id){
        return current->getData();
    }
    if(current->getData()->getId() > id){
        return idToPointer(id, current->getLeft(), tree);
    }
    return idToPointer(id, current->getRight(), tree);
}

Ship* idToPointer(int id, const AVLNode<Ship*>* current, const AVLTree<Ship*,Ship::Comparator>& tree) {         // Tree parameter is useless
    if(current == nullptr || current->getData() == nullptr) {
        return nullptr;
    }
    if(current->getData()->getId() == id) {
        return current->getData();
    }
    if(current->getData()->getId() > id) {
        return idToPointer(id, current->getLeft(), tree);
    }
    return idToPointer(id, current->getRight(), tree);
}
