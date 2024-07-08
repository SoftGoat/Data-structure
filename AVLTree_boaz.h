#include "AVLNode_boaz.h"

template<class T>
class AVLTree {
public:
    // Constructor to initialize the AVL tree
    AVLTree() : root(nullptr), size(0) {};

    // Getter for the root node
    AVLNode<T>* getRoot() { return root; }

    // Public methods for inserting, removing, searching, and printing the tree
    AVLNode<T>* insert(const T& val);
    void remove(const T& val);
    AVLNode<T>* search(const T& val) const;
    void print() const;
    bool isEmpty() const;
    AVLNode<T>* findMinNode() const;
    AVLNode<T>* findMaxVal() const;
    T& findMinVal() const;
    T& findMaxVal() const;

private:
    // Private methods for various operations
    AVLNode<T>* BSTRemove(const T& val);          // Binary Search Tree removal
    void removeRotations(AVLNode<T>* node);       // Adjust tree rotations after removal
    void print(AVLNode<T>* node) const;           // Recursive print function
    AVLNode<T>* search(const T& val, AVLNode<T>* node) const; // Recursive search function
    AVLNode<T>* BSTInsert(const T& val, AVLNode<T>* node);    // Binary Search Tree insertion
    void rotate(AVLNode<T>* node);                // Determine and apply the correct rotation
    void rotateLL(AVLNode<T>* node);              // Left-Left rotation
    void rotateLR(AVLNode<T>* node);              // Left-Right rotation
    void rotateRR(AVLNode<T>* node);              // Right-Right rotation
    void rotateRL(AVLNode<T>* node);              // Right-Left rotation

    // Member variables
    AVLNode<T>* root;                             // Root node of the AVL tree
    int size;                                     // Number of nodes in the tree
};

template<class T>
void AVLTree<T>::isEmpty() const{
    if(size == 0){
        return true;
    }
    return false;
}

/*
 * Public print method: calls the private recursive print method.
 */
template<class T>
void AVLTree<T>::print() const {
    this->print(root);
}

/*
 * Private recursive print method: performs an in-order traversal.
 */
template<class T>
void AVLTree<T>::print(AVLNode<T>* node) const {
    if (node == nullptr) {
        return;
    }
    print(node->getLeft());
    print(node->getRight());
    std::cout << node->getData() << std::endl;
}

/*
 * Private Binary Search Tree style insert method.
 * Returns a pointer to the newly inserted node.
 */
template<class T>
AVLNode<T>* AVLTree<T>::BSTInsert(const T& val, AVLNode<T>* node) {
    if (node == nullptr) { // The tree is empty, add val to root.
        AVLNode<T>* new_root = new AVLNode<T>(val);
        root = new_root;
        return root;
    }

    if (val < node->getData()) {
        if (node->getLeft() == nullptr) { // Create a new node and add it as the left child.
            AVLNode<T>* new_node = new AVLNode<T>(val);
            node->setLeft(new_node);
            return new_node;
        }
        return BSTInsert(val, node->getLeft()); // Continue recursion.
    } else if (val > node->getData()) {
        if (node->getRight() == nullptr) {
            AVLNode<T>* new_node = new AVLNode<T>(val);
            node->setRight(new_node);
            return new_node;
        }
        return BSTInsert(val, node->getRight());
    }

    return nullptr; // Do not add the same node twice.
}

/*
 * Public AVL Tree style insert method.
 * Returns a pointer to the newly inserted node.
 */
template<class T>
AVLNode<T>* AVLTree<T>::insert(const T& val) {
    AVLNode<T>* new_node;
    this->size++;
    new_node = BSTInsert(val, root);
    if (!new_node) { // If the node is already in the tree, do not insert it!
        this->size--; // Keep the size of the tree the same.
        return nullptr;
    }
    // Value added to tree as a normal Binary Search Tree.
    // Do the necessary adjustments for an AVL tree.
    AVLNode<T>* v = new_node;
    AVLNode<T>* p;
    int p_BF = 0;
    while (v != root) {
        p = v->getParent(); // v != root so v->getParent() != nullptr
        if (p->getHeight() > v->getHeight()) {
            return new_node; // Finish the program, return a pointer to the new node.
        }
        p->setHeight(1 + v->getHeight());
        p_BF = p->getBF();
        if (p_BF <= -2 || p_BF >= 2) {
            rotate(p);
            return new_node;
        }
        v = p; // Continue to go up the tree.
    }
    // Went through the whole tree, which means that the basic BST insert was fine.
    return new_node;
}

/*
 * Private method to specify the correct rotation and call the appropriate function.
 */
template<class T>
void AVLTree<T>::rotate(AVLNode<T>* node) {
    // Determine the balance factor of the node and its children
    int nodeBF = node->getBF();
    AVLNode<T>* left_son = node->getLeft();
    AVLNode<T>* right_son = node->getRight();
    int leftBF = 0;
    int rightBF = 0;
    if (left_son != nullptr) {
        leftBF = left_son->getBF();
    }
    if (right_son != nullptr) {
        rightBF = right_son->getBF();
    }

    // Apply the appropriate rotation based on the balance factors
    if (nodeBF == 2 && leftBF >= 0) {
        rotateLL(node);
    } else if (nodeBF == 2) {
        rotateLR(node);
    } else if (nodeBF == -2 && rightBF <= 0) {
        rotateRR(node);
    } else if (nodeBF == -2) {
        rotateRL(node);
    }
}

/*
 * Private method for Left-Left rotation.
 */
template<class T>
void AVLTree<T>::rotateLL(AVLNode<T>* node) {
    AVLNode<T>* left_son = node->getLeft();
    AVLNode<T>* parent = node->getParent();
    if (parent != nullptr) {
        if (node == parent->getRight()) {
            parent->setRight(left_son);
        } else {
            parent->setLeft(left_son);
        }
    }
    node->setLeft(left_son->getRight());
    left_son->setRight(node);
    left_son->setParent(parent);
    // Change heights
    node->decreaseHeight();
    node->decreaseHeight();
    if (node == root) {
        root = left_son;
    }
}

/*
 * Private method for Right-Right rotation.
 */
template<class T>
void AVLTree<T>::rotateRR(AVLNode<T>* node) {
    AVLNode<T>* right_son = node->getRight();
    AVLNode<T>* parent = node->getParent();
    if (parent != nullptr) {
        if (node == parent->getRight()) {
            parent->setRight(right_son);
        } else {
            parent->setLeft(right_son);
        }
    }
    node->setRight(right_son->getLeft());
    right_son->setLeft(node);
    right_son->setParent(parent);
    // Change heights
    node->decreaseHeight();
    node->decreaseHeight();
    if (node == root) {
        root = right_son;
    }
}

/*
 * Private method for Left-Right rotation.
 */
template<class T>
void AVLTree<T>::rotateLR(AVLNode<T>* node) {
    AVLNode<T>* left_son = node->getLeft();
    rotateRR(left_son);
    rotateLL(node);
}

/*
 * Private method for Right-Left rotation.
 */
template<class T>
void AVLTree<T>::rotateRL(AVLNode<T>* node) {
    AVLNode<T>* right_son = node->getRight();
    rotateLL(right_son);
    rotateRR(node);
}

/*
 * Public search method: calls the private recursive search method.
 */
template<class T>
AVLNode<T>* AVLTree<T>::search(const T& val) const {
    return search(val, this->root);
}

/*
 * Private recursive search method.
 * Returns a pointer to the node containing the value.
 */
template<class T>
AVLNode<T>* AVLTree<T>::search(const T& val, AVLNode<T>* node) const {
    if (node == nullptr) { // The tree is empty.
        return nullptr;
    }

    if (val < node->getData()) {
        return search(val, node->getLeft()); // Continue recursion with the left child.
    } else if (val > node->getData()) {
        return search(val, node->getRight()); // Continue recursion with the right child.
    }
    return node; // val == node->getData().
}

/*
 * Private Binary Search Tree removal method.
 * Returns the parent of the removed node.
 */
template<class T>
AVLNode<T>* AVLTree<T>::BSTRemove(const T& val) {
    AVLNode<T>* rm = this->search(val);
    if (rm == nullptr) { // The value is not in the tree.
        return nullptr;
    }
    AVLNode<T>* parent = rm->getParent();
    int rm_height = rm->getHeight();
    bool is_left = false;
    if (parent != nullptr) {
        is_left = (parent->getLeft() == rm);
    }
    AVLNode<T>* right_son = rm->getRight();
    AVLNode<T>* left_son = rm->getLeft();
    delete rm;

    // Case 1: rm node is a leaf. Just delete it.
    if (left_son == nullptr && right_son == nullptr) {
        if (parent != nullptr) {
            if (is_left) {
                parent->setLeft(nullptr);
            } else {
                parent->setRight(nullptr);
            }
        }
        updateHeights(parent);
        this->size--;
        return parent;
    }
    // Case 2.1: rm node has only one child and it is the right child.
    else if (left_son == nullptr && right_son != nullptr) {
        if (parent != nullptr) {
            if (is_left) {
                parent->setLeft(right_son);
            } else {
                parent->setRight(right_son);
            }
        } else { // rm is the root
            root = right_son;
        }
        updateHeights(parent);
        this->size--;
        return parent;
    }
    // Case 2.2: rm node has only one child and it is the left child.
    else if (left_son != nullptr && right_son == nullptr) {
        if (parent != nullptr) {
            if (is_left) {
                parent->setLeft(left_son);
            } else {
                parent->setRight(left_son);
            }
        } else { // rm is the root
            root = left_son;
        }
        updateHeights(parent);
        this->size--;
        return parent;
    }
    // Case 3: rm node has two children.
    else {
        AVLNode<T>* replace_node = getSmallestSon(right_son);
        AVLNode<T>* replace_node_parent = replace_node->getParent(); // We will use this node to update the heights after the removal.
        // Update replace node as the new child of parent node.
        if (parent != nullptr) {
            if (is_left) {
                parent->setLeft(replace_node);
            } else {
                parent->setRight(replace_node);
            }
        } else { // rm is the root
            root = replace_node;
        }
        // Separate replace node from its parent only if it is not the right child of rm.
        // Update the right child of replace node only if it isn't the right child itself.
        if (replace_node != right_son) {
            (replace_node->getParent())->setLeft(nullptr);
            replace_node->setRight(right_son);
        } else {
            replace_node->setRight(nullptr);
        }
        replace_node->setParent(parent);
        replace_node->setLeft(left_son);
        // Update the heights of the affected nodes.
        if (replace_node_parent == rm) {
            // If the parent of replace_node was rm, we will just change the height of replace_node
            replace_node->setHeight(left_son->getHeight() + 1);
        } else { // If not, we will go through the tree from the node we changed upward and change each node's height.
            updateHeights(replace_node_parent);
        }
        this->size--;
        return parent;
    }
}

/*
 * Private method to update heights of the nodes.
 */
template<class T>
void updateHeights(AVLNode<T>* node) {
    if (node == nullptr) {
        return;
    }
    int left_height = -1;
    int right_height = -1;
    int new_height = 0;
    AVLNode<T>* left_son = node->getLeft();
    AVLNode<T>* right_son = node->getRight();
    if (left_son != nullptr) {
        left_height = left_son->getHeight();
    }
    if (right_son != nullptr) {
        right_height = right_son->getHeight();
    }
    new_height = (left_height > right_height) ? left_height : right_height;
    new_height++; // Update new_height
    if (new_height == node->getHeight()) {
        return; // Did not change the node height and therefore did not need to change its parent's height!
    }
    node->setHeight(new_height);
    updateHeights(node->getParent()); // Update parent height.
}

/*
 * Private method to return the smallest child of the given node.
 */
template<class T>
AVLNode<T>* getSmallestSon(AVLNode<T>* node) {
    if (node == nullptr) {
        return node;
    }
    if (node->getLeft() == nullptr) {
        return node;
    }
    return getSmallestSon(node->getLeft());
}

/*
 * Public remove method: removes a node with the given value and adjusts rotations.
 */
template<class T>
void AVLTree<T>::remove(const T& val) {
    this->removeRotations(this->BSTRemove(val));
}

/*
 * Private method to adjust tree rotations after a removal.
 */
template<class T>
void AVLTree<T>::removeRotations(AVLNode<T>* node) {
    if (node == nullptr) {
        return;
    }
    if (node->getBF() == 2 || node->getBF() == -2) {
        this->rotate(node);
    }
    removeRotations(node->getParent());
}
