#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include "HashTable.h"
#include "UpTreeNode.h"
#include "UpTree.h"
#include <stdexcept>





/**
 * @brief A disjoint set data structure using a hash table and up-trees.
 * 
 * This structure allows efficient union and find operations using a hash table for fast element lookup.
 */
template <typename ValueType, typename KeyType = int, typename HashFunc = IntHash>
class DisjointSet {
private:
    HashTable<KeyType, Node<ValueType>*, HashFunc> elementMap; ///< Hash table mapping keys to up-tree nodes
    UpTree<ValueType> upTree; ///< UpTree structure to manage the disjoint set



public:
    /**
     * @brief Constructs a new DisjointSet object with a given initial capacity.
     * 
     * @param initialCapacity The initial capacity for the hash table.
     */
    DisjointSet(size_t initialCapacity = 101);

    /**
     * @brief Adds an element to the disjoint set.
     * 
     * Initializes the element as its own set.
     * 
     * @param element The element to add.
     */
    void makeSet(const ValueType& element);

    /**
     * @brief Finds the representative of the set containing the element.
     * 
     * Uses path compression to optimize future queries.
     * 
     * @param element The element to find.
     * @return The representative element of the set containing the element.
     */
    ValueType& find(const KeyType& element);

    /**
     * @brief Unites the sets containing two elements.
     * 
     * Attaches the smaller tree under the larger tree's root.
     * 
     * @param element1 The first element.
     * @param element2 The second element.
     */
    void unite(const KeyType& element1, const KeyType& element2);

    /**
     * @brief Checks if two elements are in the same set.
     * 
     * @param element1 The first element to check.
     * @param element2 The second element to check.
     * @return True if both elements are in the same set, false otherwise.
     */
    bool connected(const KeyType& element1, const KeyType& element2) const;

    /**
     * @brief Gets the size of the set containing an element.
     * 
     * @param element The element whose set size is queried.
     * @return The size of the set containing the element.
     */
    int getSize(const KeyType& element) const;

    /**
     * @brief Gets the rank of the set containing an element.
     * 
     * @param element The element whose set rank is queried.
     * @return The rank of the set containing the element.
     */
    int getRank(const KeyType& element) const;
};

// Implementation of DisjointSet

// Constructor with default hash function and load factor threshold
template <typename ValueType, typename KeyType, typename HashFunc>
DisjointSet<ValueType, KeyType, HashFunc>::DisjointSet(size_t initialCapacity)
    : elementMap(initialCapacity, HashFunc()) { // Providing default values
}


// Adds an element to the disjoint set
template <typename ValueType, typename KeyType, typename HashFunc>
void DisjointSet<ValueType, KeyType, HashFunc>::makeSet(const ValueType& element) {
    KeyType key = element.get_key(); // Assume ValueType has a get_key() method
    if (elementMap.contains(key)) {
        throw std::invalid_argument("Element already exists in the disjoint set.");
    }

    Node<ValueType>* newNode = new Node<ValueType>(element);
    elementMap.insert(key, newNode); // Use key as the hash key, newNode as value
}

// Finds the representative of the set containing the element
template <typename ValueType, typename KeyType, typename HashFunc>
ValueType& DisjointSet<ValueType, KeyType, HashFunc>::find(const KeyType& element) {
    Node<ValueType>* node = nullptr;
    if (!elementMap.contains(element) || !(node = elementMap.get(element))) {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }

    return upTree.findExternal(node)->data;
}

// Unites the sets containing two elements
template <typename ValueType, typename KeyType, typename HashFunc>
void DisjointSet<ValueType, KeyType, HashFunc>::unite(const KeyType& element1, const KeyType& element2) {
    Node<ValueType>* node1 = nullptr;
    Node<ValueType>* node2 = nullptr;

    if (!elementMap.contains(element1) || !elementMap.contains(element2)) {
        throw std::invalid_argument("One or both elements not found in the disjoint set.");
    }

    node1 = elementMap.get(element1);
    node2 = elementMap.get(element2);
    upTree.unite(node1, node2);
}

// Checks if two elements are in the same set
template <typename ValueType, typename KeyType, typename HashFunc>
bool DisjointSet<ValueType, KeyType, HashFunc>::connected(const KeyType& element1, const KeyType& element2) const {
    Node<ValueType>* node1 = elementMap.get(element1);
    Node<ValueType>* node2 = elementMap.get(element2);
    Node<ValueType>* root1 = upTree.findExternal(node1); // Find the root of the set containing node1, also path compression
    Node<ValueType>* root2 = upTree.findExternal(node2); // Find the root of the set containing node2, also path compression

    return root1 == root2;
}

// Gets the size of the set containing an element
template <typename ValueType, typename KeyType, typename HashFunc>
int DisjointSet<ValueType, KeyType, HashFunc>::getSize(const KeyType& element) const {
    Node<ValueType>* node = elementMap.get(element);
    return upTree.findExternal(node)->size; // Return the size of the set, also path compression
}

// Gets the rank of the set containing an element
template <typename ValueType, typename KeyType, typename HashFunc>
int DisjointSet<ValueType, KeyType, HashFunc>::getRank(const KeyType& element) const {
    Node<ValueType>* node = elementMap.get(element);
    return upTree.getRank(node);
}

#endif // DISJOINTSET_H