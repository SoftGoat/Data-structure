#include "UpTree.h"

// Constructor
template <typename T>
UpTree<T>::UpTree(size_t n) : capacity(n) {
    nodes = new UpTreeNode<T>[capacity];

    for (size_t i = 0; i < capacity; ++i) {
        nodes[i] = UpTreeNode<T>(i); // Initialize each node as its own parent
    }
}

// Destructor
template <typename T>
UpTree<T>::~UpTree() {
    delete[] nodes;
}

// Find with path compression
template <typename T>
T UpTree<T>::find(T x) {
    if (nodes[x].parent != x) {
        nodes[x].parent = find(nodes[x].parent); // Path compression
    }
    return nodes[x].parent;
}

// Union by size
template <typename T>
void UpTree<T>::unite(T x, T y) {
    T rootX = find(x);
    T rootY = find(y);

    if (rootX != rootY) {
        // Attach the smaller tree under the larger tree's root
        if (nodes[rootX].size < nodes[rootY].size) {
            nodes[rootX].parent = rootY;
            nodes[rootY].size += nodes[rootX].size; // Update size of rootY
        } else {
            nodes[rootY].parent = rootX;
            nodes[rootX].size += nodes[rootY].size; // Update size of rootX
        }
    }
}

// Check if two elements are in the same set
template <typename T>
bool UpTree<T>::connected(T x, T y) {
    return find(x) == find(y);
}
