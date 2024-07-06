#include <iostream>
#include <iomanip>
using namespace std;

template<typename T>
class AVLNode {
public:
    T m_key;
    AVLNode* m_left;
    AVLNode* m_right;
    int m_height;

    AVLNode(T key) : m_key(key), m_left(nullptr), m_right(nullptr), m_height(1) {};

    AVLNode& operator=(const AVLNode& other) {
        if (this == &other) {
            return *this; // handle self assignment
        }

        // Copy data members
        m_key = other.m_key;
        m_left = other.m_left;
        m_right = other.m_right;
        m_height = other.m_height;

        return *this;
    }
};

template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node) const {
        return node ? node->m_height : 0;
    }

    int getBalance(AVLNode<T>* node) const {
        return node ? height(node->m_left) - height(node->m_right) : 0;
    }

    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->m_left;
        AVLNode<T>* T2 = x->m_right;

        x->m_right = y;
        y->m_left = T2;

        y->m_height = max(height(y->m_left), height(y->m_right)) + 1;
        x->m_height = max(height(x->m_left), height(x->m_right)) + 1;

        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->m_right;
        AVLNode<T>* T2 = y->m_left;

        y->m_left = x;
        x->m_right = T2;

        x->m_height = max(height(x->m_left), height(x->m_right)) + 1;
        y->m_height = max(height(y->m_left), height(y->m_right)) + 1;

        return y;
    }

    AVLNode<T>* balance(AVLNode<T>* node) {
        if (node == nullptr) {
            return node;
        }

        node->m_height = 1 + std::max(height(node->m_left), height(node->m_right));
    
        int balance = getBalance(node);
    
        if (balance > 1 && getBalance(node->m_left) >= 0) {
            return rightRotate(node);
        }
    
        if (balance > 1 && getBalance(node->m_left) < 0) {
            node->m_left = leftRotate(node->m_left);
            return rightRotate(node);
        }
    
        if (balance < -1 && getBalance(node->m_right) <= 0) {
            return leftRotate(node);
        }
    
        if (balance < -1 && getBalance(node->m_right) > 0) {
            node->m_right = rightRotate(node->m_right);
            return leftRotate(node);
        }
    
        return node;
    }

    AVLNode<T>* insert(AVLNode<T>* node, const T& key) {
        if (node == nullptr) {
            return new AVLNode<T>(key);
        }
    
        if (key < node->m_key) {
            node->m_left = insert(node->m_left, key);
        } else if (key > node->m_key) {
            node->m_right = insert(node->m_right, key);
        } else {
            // Duplicate keys are not allowed in AVL tree
            return node;
        }
    
        return balance(node);
    }

    AVLNode<T>* minValueNode(AVLNode<T>* node) const {
        AVLNode<T>* current = node;

        while (current->m_left != nullptr) {
            current = current->m_left;
        }

        return current;
    }

    AVLNode<T>* maxValueNode(AVLNode<T>* node) const {
        AVLNode<T>* current = node;

        while (current->m_right != nullptr) {
            current = current->m_right;
        }

        return current;
    }

    AVLNode<T>* remove(AVLNode<T>* node, const T& key) {
        if (node == nullptr) {
            return node;
        }
    
        if (key < node->m_key) {
            node->m_left = remove(node->m_left, key);
        } else if (key > node->m_key) {
            node->m_right = remove(node->m_right, key);
        } else {
            if (node->m_left == nullptr || node->m_right == nullptr) { // One child or no child case
                AVLNode<T>* temp = node->m_left ? node->m_left : node->m_right;
    
                if (temp == nullptr) { // No child case
                    temp = node;
                    node = nullptr;
                } else { // One child case
                    *node = *temp;
                }
                delete temp;
            } else { // Two children case
                AVLNode<T>* temp = minValueNode(node->m_right);
                node->m_key = temp->m_key;
                node->m_right = remove(node->m_right, temp->m_key);
            }
        }
    
        return balance(node);
    }

    void inOrder(AVLNode<T>* root) const {
        if (root != nullptr) {
            inOrder(root->m_left);
            std::cout << root->m_key << " ";
            inOrder(root->m_right);
        }
    }
    
    void deleteTree(AVLNode<T>* node) {
        if (node != nullptr) {
            deleteTree(node->m_left);
            deleteTree(node->m_right);
            delete node;
        }
    }

    void treePrint(AVLNode<T>* node, int indent) const {
        if (node != nullptr) {
            if (node->m_right) {
                treePrint(node->m_right, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (node->m_right) {
                std::cout << " /\n" << std::setw(indent) << ' ';
            }
            std::cout << node->m_key << "\n ";
            if (node->m_left) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                treePrint(node->m_left, indent + 4);
            }
        }
    }

    AVLNode<T>* search(AVLNode<T>* node, const T& key) const {
        if (node == nullptr || node->m_key == key) {
            return node;
        }

        if (key < node->m_key) {
            return search(node->m_left, key);
        }

        return search(node->m_right, key);
    }

    int nodeCount(AVLNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + nodeCount(node->m_left) + nodeCount(node->m_right);
    }

    bool isBalanced(AVLNode<T>* node) const {
        if (node == nullptr) {
            return true;
        }

        int balance = getBalance(node);
        if (balance > 1 || balance < -1) {
            return false;
        }

        return isBalanced(node->m_left) && isBalanced(node->m_right);
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }

    void insert(const T& key) {
        root = insert(root, key);
    }

    void remove(const T& key) {
        root = remove(root, key);
    }

    AVLNode<T>* search(const T& key) const {
        return search(root, key);
    }

    int getHeight() const {
        return height(root);
    }

    int getNodeCount() const {
        return nodeCount(root);
    }

    bool isBalanced() const {
        return isBalanced(root);
    }

    AVLNode<T>* getMaxValueNode() const {
        return maxValueNode(root);
    }

    AVLNode<T>* getMinValueNode() const {
        return minValueNode(root);
    }

    AVLNode<T>* getRoot() const {
        return root;
    }

    void printTree() const {
        treePrint(root, 0);
    }

    void printInOrder() const {
        inOrder(root);
        std::cout << std::endl;
    }
};