#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef> // For size_t
#include <iostream> // For std::cout, std::endl
#include "DynamicArray.h"


struct IntHash {
    size_t operator()(int key, size_t i, int m) const {
        size_t h1 = key % m;          // Primary hash function
        size_t h2 = 1 + (key % (m-1)); // Secondary hash function for step size
        return (h1 + i * h2) % m;
    }
};

int closestPrime(int n) {
    for (int i = n + 1;; ++i) {
        bool isPrime = true;
        for (int j = 2; j <= std::sqrt(i); ++j) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            return i;
        }
    }
}

/**
 * @brief A hash table implementation that maps keys to unique values using double hashing.
 * 
 * This hash table uses open addressing with double hashing for collision resolution and supports dynamic resizing.
 */
template <typename KeyType, typename ValueType, typename HashFunc = IntHash>
class HashTable {
private:
    struct HashEntry {
        KeyType key;    ///< Key stored in the hash table
        ValueType value; ///< Value stored in the hash table
        bool isOccupied; ///< Flag to indicate if the slot is occupied
        bool isDeleted; ///< Flag to indicate if the slot is deleted

        HashEntry() : isOccupied(false), isDeleted(false) {}
        HashEntry(const KeyType& key, const ValueType& value) : key(key), value(value), isOccupied(true), isDeleted(false) {}
    };

    DynamicArray<HashEntry> table; ///< Dynamic array storing hash table entries
    size_t size;       ///< The current number of elements in the hash table
    HashFunc hashFunc; ///< The custom hash function sequence
    float loadFactorThreshold; ///< Threshold for resizing the hash table
    static constexpr int INITIAL_CAPACITY = 101; ///< Initial capacity of the hash table, CANNOT BE CHANGED TO CONST

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
    HashTable(size_t initialCapacity = 101 ,HashFunc hashFunc = HashFunc(), float loadFactorThreshold = 0.75f);

    /**
     * @brief Destroys the HashTable, freeing allocated memory.
     */
    ~HashTable() = default;

    /**
     * @brief Inserts a key-value pair into the hash table.
     * 
     * If the key already exists, this function does nothing.
     * 
     * @param key The key to insert.
     * @param value The value to insert.
     * @return True if the key was inserted, false if the key already exists.
     */
    bool insert(const KeyType& key, const ValueType& value);

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
     * @brief Gets the value associated with a key.
     * 
     * @param key The key to find.
     * @return The value associated with the key.
     */
    ValueType get(const KeyType& key) const;

    /**
     * @brief Prints the hash table for debugging purposes.
     */
    void printTable() const;
};

// Implementation of HashTable

// Constructor
template <typename KeyType, typename ValueType, typename HashFunc>
HashTable<KeyType, ValueType, HashFunc>::HashTable(size_t initialCapacity, HashFunc hashFunc, float loadFactorThreshold)
    : table(initialCapacity), size(0), hashFunc(hashFunc), loadFactorThreshold(loadFactorThreshold) {}


// Computes the hash index for a given key
template <typename KeyType, typename ValueType, typename HashFunc>
size_t HashTable<KeyType, ValueType, HashFunc>::hash(const KeyType& key, size_t i) const {
    // Use two hash functions: h1 and h2, represented by hashFunc
    // h1 determines the starting slot, h2 determines the step size
    return (hashFunc(key, 0, table.getCapacity()) + i * hashFunc(key, 1, table.getCapacity())) % table.getCapacity();
}

// Resize the hash table when load factor exceeds the threshold
template <typename KeyType, typename ValueType, typename HashFunc>
void HashTable<KeyType, ValueType, HashFunc>::resize() {
    size_t newCapacity = closestPrime(table.getCapacity() * 2);
    DynamicArray<HashEntry> newTable(newCapacity);

    // Rehash all existing keys
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        if (table.isOccupied(i) && !table.get(i).isDeleted) {
            KeyType key = table.get(i).key;
            ValueType value = table.get(i).value;
            for (size_t j = 0; j < newCapacity; ++j) {
                size_t index = (hashFunc(key, 0, table.getCapacity()) + j * hashFunc(key, 1, table.getCapacity())) % newCapacity;
                if (!newTable.isOccupied(index)) {
                    newTable.addAt(HashEntry(key, value), index);
                    break;
                }
            }
        }
    }

    table = std::move(newTable);
}

// Insert a key-value pair into the hash table
template <typename KeyType, typename ValueType, typename HashFunc>
bool HashTable<KeyType, ValueType, HashFunc>::insert(const KeyType& key, const ValueType& value) {
    if (static_cast<float>(size) / table.getCapacity() >= loadFactorThreshold) {
        resize();
    }

    for (size_t i = 0; i < table.getCapacity(); ++i) {
        size_t index = hash(key, i);
        if (index >= table.getSize()) {
            table.addAt(HashEntry(key, value), index);
            ++size;
            return true;
        }

        HashEntry& entry = table.get(index);
        if (!entry.isOccupied || entry.isDeleted) {
            entry.key = key;
            entry.value = value;
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
template <typename KeyType, typename ValueType, typename HashFunc>
bool HashTable<KeyType, ValueType, HashFunc>::remove(const KeyType& key) {
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        size_t index = hash(key, i);
        HashEntry& entry = table.get(index);
        if (entry.isOccupied && entry.key == key) {
            entry.isDeleted = true;
            entry.isOccupied = false;
            table.removeAt(index);
            --size;
            return true; // Key removed
        } else if (!entry.isOccupied && !entry.isDeleted) {
            return false; // Slot is empty, key not found
        }
    }
    return false; // Key not found after full probe
}

// Check if a key exists in the hash table
template <typename KeyType, typename ValueType, typename HashFunc>
bool HashTable<KeyType, ValueType, HashFunc>::contains(const KeyType& key) const {
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        size_t index = hash(key, i);
        if (index >= table.getCapacity()) {
            return false;
        }
        const HashEntry& entry = table.get(index);
        if (entry.isOccupied && entry.key == key) {
            return true; // Key found
        } else if (!entry.isOccupied) {
            return false; // Slot is empty, key not found
        }
    }
    return false; // Key not found after full probe
}

// Get the value associated with a key
template <typename KeyType, typename ValueType, typename HashFunc>
ValueType HashTable<KeyType, ValueType, HashFunc>::get(const KeyType& key) const {
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        size_t index = hash(key, i);
        const HashEntry& entry = table.get(index);
        if (entry.isOccupied && entry.key == key) {
            return entry.value; // Return the associated value
        } else if (!entry.isOccupied) {
            throw std::out_of_range("Key not found in hash table.");
        }
    }
    throw std::out_of_range("Key not found in hash table."); // Key not found after full probe
}

// Print the hash table
template <typename KeyType, typename ValueType, typename HashFunc>
void HashTable<KeyType, ValueType, HashFunc>::printTable() const {
    for (size_t i = 0; i < table.getCapacity(); ++i) {
        const HashEntry& entry = table.get(i);
        if (entry.isOccupied && !entry.isDeleted) {
            std::cout << "Slot " << i << ": " << entry.key << std::endl;
        } else {
            std::cout << "Slot " << i << ": empty" << std::endl;
        }
    }
}

#endif // HASHTABLE_H