#ifndef SHIP_H
#define SHIP_H


#include "../AVLTree.h"
#include <iostream>
#include "wet1util.h"
#include "Pirate.h"


enum struct BattleResult {
	WIN = 0,
    LOSS = 1,
    TIE = 2
};


/**
 * @class Ship
 * @brief This class represents a ship that can hold pirates and manage their treasures.
 */
class Ship {
private:
    int m_shipId; // Unique identifier for the ship.
    int m_cannons; // Number of cannons on the ship.
    int m_treasureBonus; // Bonus treasure for the ship.
    int m_crewSize; // Number of pirates on the ship.
    AVLTree<Pirate*,Pirate::Comparator> m_pirates; // AVL tree of pirates on the ship.
    Pirate* m_richestPirate; // Pointer to the richest pirate on the ship.
    Pirate* m_pirateWithMostTimeServed; // Pointer to the pirate with the most time served on the ship.
    Pirate* m_pirateWithLeastTimeServed; // Pointer to the pirate with the least time served on the ship.
    AVLTree<Pirate*,Pirate::Comparator>* m_piratesOrderdById; // AVL tree of pirates on the ship ordered by ID.
    AVLTree<Pirate*,Pirate::Comparator>* m_piratesOrderdByTreasure; // AVL tree of pirates on the ship ordered by treasure.
    bool richPirateChange (Pirate* pirate); // check if the richest pirate need to be updated, true mean swap is happened false otherwise

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
     * @brief Gets the pirate with the most time served on the ship.
     * @return Pointer to the pirate with the most time served on the ship.
     */
    Pirate* getPirateWithMostTimeServed() const;

    /**
     * @brief Gets the pirate with the least time served on the ship.
     * @return Pointer to the pirate with the least time served on the ship.
     */
    Pirate* getPirateWithLeastTimeServed() const;

    /**
     * @brief Gets the ship's unique identifier.
     * @return The unique identifier of the ship.
     */
    int getShipId() const;

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
     * @brief Sets the pirate treasure.
     * @param pirate Pointer to the pirate.
     * @param treasure The new amount of treasure.
     * @return true if the operation was successful, false otherwise.
     */
    bool setPirateTreasure(Pirate* pirate, int treasure);
    /**
     * @brief Gets pirate treasure.
     * @return The amount of treasure the pirate has.
     */
    int getPirateTreasure(Pirate* pirate) const;

    /**
     * @brief Battle between two ships.
     * @param other Pointer to the ship to battle with.
     * @return BattleResult indicating the outcome of the battle.
     */
    BattleResult battle(Ship* other);

    /**
     * @brief Destructor for the Ship class.
     */
    ~Ship();

    /**
     * @brief Sets the treasure bonus of the ship.
     * @param treasure The new treasure bonus.
     */
    void setTreasureBonus(int treasure);

    /**
     * @brief Gets the AVL tree of pirates on the ship.
     * @return Pointer to the AVL tree of pirates on the ship.
     */
    AVLTree<Pirate*,Pirate::Comparator>* getPirates();

    /**
     * @brief Gets the AVL tree of pirates on the ship ordered by ID.
     * @return Pointer to the AVL tree of pirates on the ship ordered by ID.
     */
    AVLTree<Pirate*,Pirate::Comparator>* getPiratesOrderdById();

    struct Comparator {
        bool operator()(const Ship* lhs, const Ship* rhs) const {
            return lhs->getId() < rhs->getId();
        }
    };
};


#endif 
