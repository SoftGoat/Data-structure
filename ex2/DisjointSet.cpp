#include <iostream>

template <typename T>
class DisjointSet {
private:
    T* parent;
    int* rank;
    int* heightFromGround;
    size_t size;

public:
    DisjointSet(size_t n) {
        size = n;
        parent = new T[size];
        rank = new int[size];
        heightFromGround = new int[size];

        for (size_t i = 0; i < size; ++i) {
            parent[i] = i;             // Each element is its own parent (root)
            rank[i] = 0;               // Rank is initially zero
            heightFromGround[i] = 0;   // Height from ground is initially zero
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
        delete[] heightFromGround;
    }

    // Find the representative of the set containing x with path compression
    T find(T x) {
        if (parent[x] != x) {
            T originalParent = parent[x];
            parent[x] = find(parent[x]);
            heightFromGround[x] += heightFromGround[originalParent]; // Update height
        }
        return parent[x];
    }

    // Union by rank and update the height from ground
    void unite(T x, T y) {
        T rootX = find(x);
        T rootY = find(y);

        if (rootX != rootY) {
            // Union by rank
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
                heightFromGround[rootX] = heightFromGround[y] + 1; // Update height for rootX
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
                heightFromGround[rootY] = heightFromGround[x] + 1; // Update height for rootY
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
                heightFromGround[rootY] = heightFromGround[x] + 1; // Update height for rootY
            }
        }
    }

    // Check if two elements are in the same set
    bool connected(T x, T y) {
        return find(x) == find(y);
    }

    // Get the height of a box from the ground
    int getHeight(T x) {
        find(x); // Ensure path compression is applied
        return heightFromGround[x];
    }
};


