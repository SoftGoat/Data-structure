#include <iostream>
#include "../AVLTree.h"

int main() {
    AVLTree<int, std::string> avl;

    // Inserting values
    std::cout << "Inserting values...\n";
    for (int i = 1; i <= 50; ++i) {
        avl.insert(i, "Value " + std::to_string(i));
        if (i % 10 == 0) {
            std::cout << "Inserted " << i << " nodes.\n";
        }
    }

    // Checking balance and searching
    std::cout << "\nChecking balance and searching for every 5th key...\n";
    for (int i = 5; i <= 50; i += 5) {
        if (!avl.containNode(i)) {
            std::cout << "Error: Key " << i << " not found.\n";
        } else {
            std::cout << "Key " << i << " found.\n";
        }
    }

    // Removing values
    std::cout << "\nRemoving every 5th value...\n";
    for (int i = 5; i <= 50; i += 5) {
        avl.remove(i);
        if (avl.containNode(i)) {
            std::cout << "Error: Key " << i << " was not successfully removed.\n";
        } else {
            std::cout << "Key " << i << " removed successfully.\n";
        }
    }

    // Testing edge cases
    std::cout << "\nTesting edge cases...\n";
    avl.remove(100);
    avl.insert(25, "Reinserting 25");
    if (avl.containNode(25)) {
        std::cout << "Key 25 reinserted successfully.\n";
    }

    // Clearing the tree
    std::cout << "\nClearing the tree...\n";
    avl.clearTree();
    if (avl.isEmpty()) {
        std::cout << "Tree cleared successfully.\n";
    } else {
        std::cout << "Error: Tree is not empty after clearing.\n";
    }

    // Reinserting values to test clear functionality
    std::cout << "\nReinserting values after clearing...\n";
    for (int i = 1; i <= 10; ++i) {
        avl.insert(i, "Value " + std::to_string(i));
    }
    if (!avl.isEmpty()) {
        std::cout << "Values reinserted successfully.\n";
    } else {
        std::cout << "Error: Tree is empty after reinsertion.\n";
    }

    // Removing all values one by one
    std::cout << "\nRemoving all values one by one...\n";
    for (int i = 1; i <= 10; ++i) {
        avl.remove(i);
    }
    if (avl.isEmpty()) {
        std::cout << "All values removed successfully. Tree is empty.\n";
    } else {
        std::cout << "Error: Tree is not empty after removing all values.\n";
    }

    return 0;
}
