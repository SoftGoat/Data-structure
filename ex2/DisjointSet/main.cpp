#include "DisjointSet.h"

// Custom hash function for integers
struct IntHash {
    size_t operator()(int key, size_t i) const {
        size_t h1 = key % 10;  // Primary hash function
        size_t h2 = 1 + (key % 9); // Secondary hash function for step size
        return i == 0 ? h1 : h2;
    }
};

int main() {
    // Create a disjoint set with an initial capacity
    DisjointSet<int, IntHash> ds(10, IntHash());

    // Add elements to the disjoint set
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);

    // Unite sets
    ds.unite(1, 2);

    // Check connectivity
    std::cout << "1 and 2 connected: " << ds.connected(1, 2) << std::endl; // Should be true
    std::cout << "2 and 3 connected: " << ds.connected(2, 3) << std::endl; // Should be false

    return 0;
}
