#ifndef UPTREE_H
#define UPTREE_H

#include "UpTreeNode.h"

/**
 * @brief A union-find data structure using up-trees with template nodes.
 * 
 * This structure allows for efficient union and find operations.
 * The union operation attaches the smaller tree to the root of the larger tree.
 */
template <typename T>
class UpTree {
private:
    /**
     * @brief Finds the root of the node with path compression.
     * 
     * This operation returns the root node of the set containing the given node.
     * 
     * @param node The node whose root is to be found.
     * @return The root node of the set containing the given node.
     */
    Node<T>* find(Node<T>* node);

public:
    /**
     * @brief Constructs a new UpTree object.
     */
    UpTree();

    /**
     * @brief Destroys the UpTree, freeing allocated memory.
     */
    ~UpTree();

    /**
     * @brief Unites the sets containing elements x and y.
     * 
     * The smaller tree is attached to the root of the larger tree.
     * The root of the larger tree becomes the new root.
     * 
     * @param x An element in the first set.
     * @param y An element in the second set.
     */
    void unite(Node<T>* x, Node<T>* y);

    /**
     * @brief Checks if two elements are in the same set.
     * 
     * @param x The first element to check.
     * @param y The second element to check.
     * @return True if x and y are in the same set, false otherwise.
     */
    bool connected(Node<T>* x, Node<T>* y);

    // Expose find method for external use
    Node<T>* findExternal(Node<T>* node);
};

// Implementation of UpTree

// Constructor
template <typename T>
UpTree<T>::UpTree() {
    // Initialization if needed
}

// Destructor
template <typename T>
UpTree<T>::~UpTree() {
    // Free resources if necessary
}

// Find with path compression
template <typename T>
Node<T>* UpTree<T>::find(Node<T>* node) {
    if (node->parent != node) {
        node->parent = find(node->parent); // Path compression
    }
    return node->parent;
}

// Expose find method for external use
template <typename T>
Node<T>* UpTree<T>::findExternal(Node<T>* node) {
    return find(node);
}

// Union by size
template <typename T>
void UpTree<T>::unite(Node<T>* x, Node<T>* y) {
    Node<T>* rootX = find(x);
    Node<T>* rootY = find(y);

    if (rootX == rootY) {
        return; // Elements are already united
    }

    // Attach the smaller tree under the larger tree's root
    if (rootX->size < rootY->size) {
        rootX->parent = rootY;
        rootY->size += rootX->size;
    } else {
        rootY->parent = rootX;
        rootX->size += rootY->size;
    }
}

// Check if two elements are in the same set
template <typename T>
bool UpTree<T>::connected(Node<T>* x, Node<T>* y) {
    return find(x) == find(y);
}

#endif // UPTREE_H
