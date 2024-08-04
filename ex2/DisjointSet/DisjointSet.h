#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include "HashTable.h"
#include "UpTreeNode.h"
#include "UpTree.h"
#include <stdexcept>

/**
 * @brief Default hash function for integers using double hashing.
 */
struct IntHash {
    size_t operator()(int key, size_t i, int m) const {
        size_t h1 = key % m;          // Primary hash function
        size_t h2 = 1 + (key % (m-1)); // Secondary hash function for step size
        return (h1 + i * h2) % m;
    }
};

/**
 * @brief A disjoint set data structure using a hash table and up-trees.
 * 
 * This structure allows efficient union and find operations, using a hash table for fast element lookup.
 */
template <typename T, typename HashFunc = IntHash>
class DisjointSet {
private:
    HashTable<T, Node<T>*, HashFunc> elementMap; ///< Hash table mapping elements to up-tree nodes
    UpTree<T> upTree; ///< UpTree structure to manage the disjoint set


public:
    /**
     * @brief Constructs a new DisjointSet object with a given initial capacity.
     * 
     * @param initialCapacity The initial capacity for the hash table.
     * @param hashFunc The custom hash function for the hash table.
     */
    DisjointSet(size_t initialCapacity, HashFunc hashFunc = HashFunc());

    /**
     * @brief Adds an element to the disjoint set.
     * 
     * Initializes the element as its own set.
     * 
     * @param element The element to add.
     */
    void makeSet(const T& element);

    /**
     * @brief Finds the representative of the set containing the element.
     * 
     * Uses path compression to optimize future queries.
     * 
     * @param element The element to find.
     * @return The representative element of the set containing the element.
     */
    T find(const T& element);

    /**
     * @brief Unites the sets containing two elements.
     * 
     * Attaches the smaller tree under the larger tree's root.
     * 
     * @param element1 The first element.
     * @param element2 The second element.
     */
    void unite(const T& element1, const T& element2);

    /**
     * @brief Checks if two elements are in the same set.
     * 
     * @param element1 The first element to check.
     * @param element2 The second element to check.
     * @return True if both elements are in the same set, false otherwise.
     */
    bool connected(const T& element1, const T& element2);

    /**
     * @brief Gets the size of the set containing the element.
     * 
     * @param element The element to check.
     * @return The size of the set containing the element.
     */
    int getSize(int element);

    /**
     * @brief Gets the rank of the set containing the element.
     * 
     * @param element The element to check.
     * @return The rank of the set containing the element.
     */
    int getRank(const T& element);
};

// Implementation of DisjointSet

// Constructor
template <typename T, typename HashFunc>
DisjointSet<T, HashFunc>::DisjointSet(size_t initialCapacity, HashFunc hashFunc)
    : elementMap(initialCapacity, hashFunc) {}

// Adds an element to the disjoint set
template <typename T, typename HashFunc>
void DisjointSet<T, HashFunc>::makeSet(const T& element) {
    if (elementMap.contains(element)) {
        throw std::invalid_argument("Element already exists in the disjoint set.");
    }

    Node<T>* newNode = new Node<T>(element);
    elementMap.insert(element, newNode); // Use element as key, newNode as value
}

// Finds the representative of the set containing the element
template <typename T, typename HashFunc>
T DisjointSet<T, HashFunc>::find(const T& element) {
    Node<T>* node = nullptr;
    if (!elementMap.contains(element) || !(node = elementMap.get(element))) {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }

    return upTree.findExternal(node)->data; // Return the data of the root node and not the node itself, also path compression
}

// Unites the sets containing two elements
template <typename T, typename HashFunc>
void DisjointSet<T, HashFunc>::unite(const T& element1, const T& element2) {
    Node<T>* node1 = nullptr;
    Node<T>* node2 = nullptr;

    if (!(elementMap.contains(element1) && elementMap.contains(element2))) {
        throw std::invalid_argument("One or both elements not found in the disjoint set.");
    }

    node1 = elementMap.get(element1);
    node2 = elementMap.get(element2);
    upTree.unite(node1, node2);
}

// Checks if two elements are in the same set
template <typename T, typename HashFunc>
bool DisjointSet<T, HashFunc>::connected(const T& element1, const T& element2) {
    Node<T>* node1 = nullptr;
    Node<T>* node2 = nullptr;

    if (!elementMap.contains(element1) || !elementMap.contains(element2)) {
        return false;
    }

    node1 = elementMap.get(element1);
    node2 = elementMap.get(element2);
    Node<T>* root1 = upTree.findExternal(node1); // Find the root of the set containing node1, also path compression
    Node<T>* root2 = upTree.findExternal(node2); // Find the root of the set containing node2, also path compression

    return root1 == root2;
}
template <typename T, typename HashFunc>
    int DisjointSet<T, HashFunc>::getSize(int element) {
        Node<T>* node = nullptr;
        if (!elementMap.contains(element) || !(node = elementMap.get(element))) {
            throw std::invalid_argument("Element not found in the disjoint set.");
        }

        return upTree.findExternal(node)->size; // Return the size of the set, also path compression
}

// Gets the rank of the set containing the element
template <typename T, typename HashFunc>
int DisjointSet<T, HashFunc>::getRank(const T& element) {
    Node<T>* node = nullptr;
    if (!elementMap.contains(element) || !(node = elementMap.get(element))) {
        throw std::invalid_argument("Element not found in the disjoint set.");
    }

    return upTree.getRank(node);
}

#endif // DISJOINTSET_H
