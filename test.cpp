#include <iostream>
#include "AVLTree.cpp" // Assuming the AVLTree class is defined in this header file

template<typename T>
void inOrder(AVLNode<T>* root) {
    if (root != nullptr) {
        inOrder(root->m_left);
        std::cout << root->m_key << " ";
        inOrder(root->m_right);
    }
}

int main() {
    AVLTree<int> tree;

    // Insert nodes
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // Print in-order traversal of the AVL tree
    std::cout << "In-order traversal of the constructed AVL tree is: \n"<<std::endl;
    tree.treePrint(tree.getRoot(),4);
    std::cout << std::endl;

    return 0;
}
