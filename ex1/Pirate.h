#include "Pirate.h"
#include "Ship.h"

// Class representing a Pirate
class Pirate {
public:
    /**
     * Constructor to initialize a Pirate object.
     * @param pirateId - The unique ID of the pirate.
     * @param treasure - The amount of treasure the pirate possesses.
     * Note: The shipId is not used in the Pirate class.
     *       The caller to the constructor will update the Pirate->ship field.
     */
    Pirate(int pirateId, int treasure) 
        : id(pirateId), treasure(treasure), ship(nullptr), prev_pirate(nullptr), next_pirate(nullptr) {}

    /**
     * Sets the amount of treasure the pirate possesses.
     * @param treasure - The new amount of treasure.
     */
    void setTreasure(int treasure);

    /**
     * Gets the amount of treasure the pirate possesses.
     * @return The amount of treasure.
     */
    int getTreasure() const;

    /**
     * Sets the ship the pirate is associated with.
     * @param ship - Pointer to the AVLNode containing the ship.
     */
    void setShip(AVLNode<Ship>* ship);

    /**
     * Gets the ship the pirate is associated with.
     * @return Pointer to the AVLNode containing the ship.
     */
    AVLNode<Ship>* getShip() const;

    /**
     * Sets the next pirate in the linked list.
     * @param next_pirate - Pointer to the next pirate.
     */
    void setNext(Pirate* next_pirate);

    /**
     * Gets the next pirate in the linked list.
     * @return Pointer to the next pirate.
     */
    Pirate* getNext() const;

    /**
     * Sets the previous pirate in the linked list.
     * @param prev_pirate - Pointer to the previous pirate.
     */
    void setPrev(Pirate* prev_pirate);

    /**
     * Gets the previous pirate in the linked list.
     * @return Pointer to the previous pirate.
     */
    Pirate* getPrev() const;

private:
    int id;                    ///< The unique ID of the pirate.
    int treasure;              ///< The amount of treasure the pirate possesses.
    AVLNode<Ship>* ship;       ///< Pointer to the AVLNode containing the ship the pirate is associated with.
    Pirate* next_pirate;       ///< Pointer to the next pirate in the linked list.
    Pirate* prev_pirate;       ///< Pointer to the previous pirate in the linked list.
};
