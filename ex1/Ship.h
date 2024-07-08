#ifndef SHIP_H
#define SHIP_H

#include "../AVLTree_boaz.h"
#include <iostream>
#include "wet1util.h"

// Forward declaration of the Pirate class
class Pirate;

/**
 * @class Ship
 * @brief This class represents a ship that can hold pirates and manage their treasures.
 */
class Ship {
private:
    int m_shipId;                /**< @brief Unique identifier for the ship */
    int m_cannons;               /**< @brief Number of cannons on the ship */
    int m_treasure;              /**< @brief Total treasure on the ship */
    AVLTree<Pirate> m_pirates;   /**< @brief AVL tree of pirates on the ship */
    Pirate* m_richestPirate;     /**< @brief Pointer to the richest pirate on the ship */

public:
    /**
     * @brief Constructor for the Ship class.
     * @param shipId Unique identifier for the ship.
     * @param cannons Number of cannons on the ship.
     */
    Ship(int shipId, int cannons);


    /**
     * @brief Adds a pirate to the ship.
     * @param pirateId Unique identifier for the pirate.
     * @param shipId Unique identifier for the ship.
     * @param treasure Initial amount of treasure for the pirate.
     * @return StatusType indicating the success or failure of the operation.
     */
    StatusType add_pirate(int pirateId, int shipId, int treasure);

    /**
     * @brief Removes a pirate from the ship.
     * @param pirateId Unique identifier for the pirate to be removed.
     * @return StatusType indicating the success or failure of the operation.
     */
    StatusType remove_pirate(int pirateId);

    /**
     * @brief Handles treason between two ships.
     * @param sourceShipId Unique identifier for the source ship.
     * @param destShipId Unique identifier for the destination ship.
     * @return StatusType indicating the success or failure of the operation.
     */
    StatusType treason(int sourceShipId, int destShipId);

    /**
     * @brief Updates the treasure of a pirate.
     * @param pirateId Unique identifier for the pirate.
     * @param change Amount to change the pirate's treasure by.
     * @return StatusType indicating the success or failure of the operation.
     */
    StatusType update_pirate_treasure(int pirateId, int change);

    // Additional member functions for managing the ship and pirates can be added here
};

#endif // SHIP_H
