#include "AVLTree.cpp"
#include <cassert>
#include <iostream>

void testInsertion() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "Tree after insertions:" << std::endl;
    tree.printTree();

    assert(tree.isBalanced() == true);
    assert(tree.getHeight() == 3);
}

void testDeletion() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "Tree before deletion:" << std::endl;
    tree.printTree();

    tree.remove(10);
    std::cout << "Tree after deleting 10:" << std::endl;
    tree.printTree();
    assert(tree.isBalanced() == true);

    tree.remove(20);
    std::cout << "Tree after deleting 20:" << std::endl;
    tree.printTree();
    assert(tree.isBalanced() == true);

    tree.remove(30);
    std::cout << "Tree after deleting 30:" << std::endl;
    tree.printTree();
    assert(tree.isBalanced() == true);
}

void testSearch() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    assert(tree.search(10) != nullptr);
    assert(tree.search(20) != nullptr);
    assert(tree.search(30) != nullptr);
    assert(tree.search(40) != nullptr);
    assert(tree.search(50) != nullptr);
    assert(tree.search(25) != nullptr);
    assert(tree.search(60) == nullptr);
}

void testClear() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "Tree before clearing:" << std::endl;
    tree.printTree();

    tree.clear();
    std::cout << "Tree after clearing:" << std::endl;
    tree.printTree();

    assert(tree.getHeight() == 0);
    assert(tree.getNodeCount() == 0);
}

int main() {
    testInsertion();
    testDeletion();
    testSearch();
    testClear();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
