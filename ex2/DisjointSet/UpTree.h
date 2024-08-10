#ifndef UPTREE_H
#define UPTREE_H

#include "UpTreeNode.h"
#include <memory>

template <typename T>
class UpTree {
private:
    std::shared_ptr<Node<T>> find(std::shared_ptr<Node<T>> node) const;

public:
    /**
     * @brief Constructs a new UpTree object.
     * 
     * Initializes an empty UpTree structure.
     */
    UpTree();

    /**
     * @brief Destroys the UpTree object.
     * 
     * Handles cleanup of resources used by the UpTree.
     */
    ~UpTree();

    /**
     * @brief Unites two disjoint sets containing the given nodes.
     * 
     * Attaches the tree with a lower rank under the root of the tree with a higher rank.
     * 
     * @param x The first node (root of the first set).
     * @param y The second node (root of the second set).
     * @param Xrank The rank of the first node's set.
     * @param Yrank The rank of the second node's set.
     */
    void unite(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y, int Xrank, int Yrank);

    /**
     * @brief Checks if two nodes are in the same set.
     * 
     * Determines whether the two nodes belong to the same connected component in the UpTree.
     * 
     * @param x The first node to check.
     * @param y The second node to check.
     * @return True if both nodes are in the same set, false otherwise.
     */
    bool connected(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y) const;

    /**
     * @brief Gets the rank of the set containing the given node.
     * 
     * This function retrieves the rank of the set that contains the given node.
     * 
     * @param x The node whose set rank is queried.
     * @return The rank of the set containing the node.
     */
    int getRank(std::shared_ptr<Node<T>> x) const;

    /**
     * @brief Finds the representative of the set containing the given node.
     * 
     * Uses path compression to find the root of the tree containing the node, optimizing future queries.
     * 
     * @param node The node to find the set representative for.
     * @return A shared pointer to the root node of the set containing the given node.
     */
    std::shared_ptr<Node<T>> findExternal(std::shared_ptr<Node<T>> node) const;
};

// Implementation of UpTree

template <typename T>
UpTree<T>::UpTree() {}

template <typename T>
UpTree<T>::~UpTree() {}

template <typename T>
std::shared_ptr<Node<T>> UpTree<T>::find(std::shared_ptr<Node<T>> node) const {
    if (node->parent != node) {
        if (node->parent->parent != node->parent) {
            node->rank += node->parent->rank;
        }
        node->parent = find(node->parent);
    }
    return node->parent;
}

template <typename T>
std::shared_ptr<Node<T>> UpTree<T>::findExternal(std::shared_ptr<Node<T>> node) const {
    return find(node);
}

template <typename T>
void UpTree<T>::unite(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y, int Xrank, int Yrank) {
    auto rootX = find(x);
    auto rootY = find(y);

    if (rootX == rootY) {
        return;
    }

    if (rootX->size < rootY->size) {
        rootX->parent = rootY;
        if (Xrank < Yrank) {
            rootX->rank += rootY->size - 1;
        } else {
            rootY->rank += rootX->size - 1;
        }
        rootY->size += rootX->size;
    } else {
        rootY->parent = rootX;
        if (Xrank < Yrank) {
            rootX->rank += rootY->size - 1;
        } else {
            rootY->rank += rootX->size - 1;
        }
        rootX->size += rootY->size;
    }
}

template <typename T>
bool UpTree<T>::connected(std::shared_ptr<Node<T>> x, std::shared_ptr<Node<T>> y) const {
    return find(x) == find(y);
}

template <typename T>
int UpTree<T>::getRank(std::shared_ptr<Node<T>> x) const {
    int realRank = 1;
    find(x);
    while (x->parent != x) {
        realRank += x->rank;
        x = x->parent;
    }
    return realRank;
}

#endif // UPTREE_H