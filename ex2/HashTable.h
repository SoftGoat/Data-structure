#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef> // For size_t
#include <iostream> // For std::cout, std::endl
#include "DynamicArray.h"

/**
 * @brief A hash table implementation that maps keys to unique values using double hashing.
 * 
 * This hash table uses open addressing with double hashing for collision resolution and supports dynamic resizing.
 */
template <typename KeyType, typename HashFunc>
class HashTable {
private:
    struct HashEntry {
        KeyType key;    ///< Key stored in the hash table
        bool isOccupied; ///< Flag to indicate if the slot is occupied
        bool isDeleted; ///< Flag to indicate if the slot is deleted

        HashEntry();
    };

    DynamicArray<HashEntry> table; ///< Dynamic array storing hash table entries
    size_t size;       ///< The current number of elements in the hash table
    HashFunc hashFunc; ///< The custom hash function sequence
    float loadFactorThreshold; ///< Threshold for resizing the hash table

    /**
     * @brief Computes the hash index for a given key using the custom hash function sequence.
     * 
     * @param key The key to hash.
     * @param i The index in the hash function sequence.
     * @return The hash index.
     */
    size_t hash(const KeyType& key, size_t i) const;

    /**
     * @brief Resizes the hash table when the load factor exceeds the threshold.
     */
    void resize();

public:
    /**
     * @brief Constructs a new HashTable object with a given capacity.
     * 
     * @param initialCapacity The initial capacity of the hash table.
     * @param hashFunc The custom hash function sequence.
     * @param loadFactorThreshold The threshold for resizing the hash table.
     */
    HashTable(size_t initialCapacity, HashFunc hashFunc, float loadFactorThreshold = 0.75f);

    /**
     * @brief Destroys the HashTable, freeing allocated memory.
     */
    ~HashTable() = default;

    /**
     * @brief Inserts a key into the hash table.
     * 
     * If the key already exists, this function does nothing.
     * 
     * @param key The key to insert.
     * @return True if the key was inserted, false if the key already exists.
     */
    bool insert(const KeyType& key);

    /**
     * @brief Removes a key from the hash table.
     * 
     * @param key The key to remove.
     * @return True if the key was removed, false if the key does not exist.
     */
    bool remove(const KeyType& key);

    /**
     * @brief Checks if a key exists in the hash table.
     * 
     * @param key The key to check.
     * @return True if the key exists, false otherwise.
     */
    bool contains(const KeyType& key) const;

    /**
     * @brief Prints the hash table for debugging purposes.
     */
    void printTable() const;
};


// Implementation of HashTable

// HashEntry constructor
template <typename KeyType, typename HashFunc>
HashTable<KeyType, HashFunc>::HashEntry::HashEntry()
    : isOccupied(false), isDeleted(false) {}

// Constructor
template <typename KeyType, typename HashFunc>
HashTable<KeyType, HashFunc>::HashTable(size_t initialCapacity, HashFunc hashFunc, float loadFactorThreshold)
    : table(initialCapacity), size(0), hashFunc(hashFunc), loadFactorThreshold(loadFactorThreshold) {}

// Computes the hash index for a given key
template <typename KeyType, typename HashFunc>
size_t HashTable<KeyType, HashFunc>::hash(const KeyType& key, size_t i) const {
    // Use two hash functions: h1 and h2, represented by hashFunc
    // h1 determines the starting slot, h2 determines the step size
    return (hashFunc(key, 0) + i * hashFunc(key, 1)) % table.getCapacity();
}

// Resize the hash table when load factor exceeds the threshold
template <typename KeyType, typename HashFunc>
void HashTable<KeyType, HashFunc>::resize() {
    size_t newCapacity = table.getCapacity() * 2;
    DynamicArray<HashEntry> newTable(newCapacity);

    // Rehash all existing keys
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        if (table.get(i).isOccupied && !table.get(i).isDeleted) {
            KeyType key = table.get(i).key;
            for (size_t j = 0; j < newCapacity; ++j) {
                size_t index = (hashFunc(key, 0) + j * hashFunc(key, 1)) % newCapacity;
                if (!newTable.get(index).isOccupied) {
                    newTable.get(index).key = key;
                    newTable.get(index).isOccupied = true;
                    break;
                }
            }
        }
    }

    table = std::move(newTable);
}

// Insert a key into the hash table
template <typename KeyType, typename HashFunc>
bool HashTable<KeyType, HashFunc>::insert(const KeyType& key) {
    if (static_cast<float>(size) / table.getCapacity() >= loadFactorThreshold) {
        resize();
    }

    for (size_t i = 0; i < table.getCapacity(); ++i) {
        size_t index = hash(key, i);
        HashEntry entry = table.get(index);
        if (!entry.isOccupied || entry.isDeleted) {
            entry.key = key;
            entry.isOccupied = true;
            entry.isDeleted = false;
            ++size;
            return true;
        } else if (entry.key == key) {
            return false; // Key already exists
        }
    }
    return false; // Should not reach here if resizing works correctly
}

// Remove a key from the hash table
template <typename KeyType, typename HashFunc>
bool HashTable<KeyType, HashFunc>::remove(const KeyType& key) {
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        size_t index = hash(key, i);
        HashEntry entry = table.get(index);
        if (entry.isOccupied && entry.key == key) {
            entry.isDeleted = true;
            --size;
            return true; // Key removed
        } else if (!entry.isOccupied) {
            return false; // Slot is empty, key not found
        }
    }
    return false; // Key not found after full probe
}

// Check if a key exists in the hash table
template <typename KeyType, typename HashFunc>
bool HashTable<KeyType, HashFunc>::contains(const KeyType& key) const {
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        size_t index = hash(key, i);
        HashEntry entry = table.get(index);
        if (entry.isOccupied && entry.key == key) {
            return true; // Key found
        } else if (!entry.isOccupied) {
            return false; // Slot is empty, key not found
        }
    }
    return false; // Key not found after full probe
}

// Print the hash table
template <typename KeyType, typename HashFunc>
void HashTable<KeyType, HashFunc>::printTable() const {
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        HashEntry entry = table.get(i);
        if (entry.isOccupied && !entry.isDeleted) {
            std::cout << "Slot " << i << ": " << entry.key << std::endl;
        } else {
            std::cout << "Slot " << i << ": empty" << std::endl;
        }
    }
}

#endif // HASHTABLE_H
