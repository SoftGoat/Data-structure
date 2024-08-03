#ifndef UPTREENODE_H
#define UPTREENODE_H

/**
 * @brief Node structure for the up-tree, representing an element in the union-find structure.
 * 
 * This structure encapsulates the data, a pointer to the parent node, and size information.
 */
template <typename T>
struct Node {
    T data;         ///< Data stored in the node
    Node* parent;   ///< Pointer to the parent node
    int size;       ///< Size of the tree if this node is a root

    /**
     * @brief Constructs a new Node object.
     * 
     * @param value The data to be stored in the node.
     */
    Node(const T& value) : data(value), parent(this), size(1) {}
};

#endif // UPTREENODE_H
