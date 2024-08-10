#ifndef UPTREENODE_H
#define UPTREENODE_H

#include <memory>

/**
 * @brief Node structure for the up-tree, representing an element in the union-find structure.
 * 
 * This structure encapsulates the data, a shared pointer to the parent node, and size information.
 */
template <typename T>
struct Node {
    T data;                           ///< Data stored in the node
    std::shared_ptr<Node> parent;     ///< Shared pointer to the parent node
    int size;                         ///< Size of the tree if this node is a root
    int rank;                         ///< Rank of the node
    int abs_rank;                     ///< Absolute rank of the node

    /**
     * @brief Constructs a new Node object.
     * 
     * @param value The data to be stored in the node.
     */
    Node(const T& value) : data(value), size(1), rank(1), abs_rank(1) {
        parent = std::shared_ptr<Node>(this, [](Node*){});  // Create a non-owning shared_ptr to this
    }
};

#endif // UPTREENODE_H