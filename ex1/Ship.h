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
     * @param pirate Pointer to the pirate to be added.
     * @return StatusType indicating the success or failure of the operation.
     */
    bool add_pirate(Pirate* pirate);

    /**
     * @brief Gets the cannons of the ship.
     * @return The number of cannons on the ship.
     */
    int getCannons() const;

    /**
     * @brief Gets the richest pirate on the ship.
     * @return Pointer to the richest pirate on the ship.
     */
    Pirate* getRichestPirate() const;

    /**
     * @brief Gets the treasure of a pirate.
     * @param pirateId Unique identifier for the pirate.
     * @return The amount of treasure the pirate has.
     */
    int getPirateTreasure(int pirateId) const;

    /**
     * @brief ship is empty.
     * @return true if the ship is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Gets the treasure of the ship.
     * @return The total treasure on the ship.
     */
    int getTreasureBonus() const;

    /**
     * @brief Gets the unique identifier of the ship.
     * @return The unique identifier of the ship.
     */
    int getId() const;

    /**
     * @brief Removes a pirate from the ship.
     * @param pirate Pointer to the pirate to be removed.
     * @return true if the pirate was removed successfully, false otherwise.
     */
    bool remove_pirate(Pirate* pirate);

    /**
     * @brief Handles treason between two ships.
     * @param other Pointer to the ship to commit treason with.
     * @return true if the operation was successful, false otherwise.
     */
    bool treason(Ship* other);

    /**
     * @brief Updates the treasure of a pirate.
     * @param pirate Pointer to the pirate to update.
     * @param change Amount to change the pirate's treasure by.
     * @return true if the operation was successful, false otherwise.
     */
    bool update_pirate_treasure(Pirate* pirate, int change);

    /**
     * @brief Gets the number of pirates on the ship.
     * @return The number of pirates on the ship.
     */
    int getCrewSize() const;

    /**
     * @brief Battle between two ships.
     * @param other Pointer to the ship to battle with.
     * @return BattleResult indicating the outcome of the battle.
     */
    BattleResult battle(Ship* other);
};

enum struct BattleResult {
	WIN = 0,
    LOSS = 1,
    TIE = 2
};
#endif 
