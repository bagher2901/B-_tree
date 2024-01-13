#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class BPTree;

template <typename T>
class Node {
    bool isLeaf;
    std::vector<T> keys;
    std::vector<Node<T>*> children;
    Node<T>* next; // Pointer to the next leaf node
    friend class BPTree<T>;

public:
    Node(bool _isLeaf) : isLeaf(_isLeaf), next(nullptr) {}
};

template <typename T>
class BPTree {
    Node<T>* root;
    int order;

    Node<T>* findLeafNode(const T& key) {
        Node<T>* curr = root;
        while (!curr->isLeaf) {
            // Binary search in keys
            auto it = std::lower_bound(curr->keys.begin(), curr->keys.end(), key);
            int idx = it - curr->keys.begin();
            curr = curr->children[idx];
        }
        return curr;
    }

    void splitLeafNode(Node<T>* leaf) {
        Node<T>* newLeaf = new Node<T>(true);
        int mid = (order + 1) / 2;

        newLeaf->keys.assign(leaf->keys.begin() + mid, leaf->keys.end());
        leaf->keys.resize(mid);

        // Update next pointers for leaf nodes
        newLeaf->next = leaf->next;
        leaf->next = newLeaf;

        // Propagate the split upwards
        insertInternal(newLeaf->keys[0], leaf, newLeaf);
    }

    void insertInternal(T key, Node<T>* left, Node<T>* right) {
        if (left == root) {
            // Create new root
            root = new Node<T>(false);
            root->keys.push_back(key);
            root->children.push_back(left);
            root->children.push_back(right);
            return;
        }

        // Insert in the parent node
        Node<T>* parent = findParent(root, left);
        auto it = std::lower_bound(parent->keys.begin(), parent->keys.end(), key);
        int idx = it - parent->keys.begin();

        parent->keys.insert(it, key);
        parent->children.insert(parent->children.begin() + idx + 1, right);

        // Split the parent if needed
        if (parent->keys.size() >= order) {
            // Splitting logic for internal nodes...
        }
    }

    Node<T>* findParent(Node<T>* curr, Node<T>* child) {
        // Logic to find the parent of 'child' node
        // ...
    }

public:
    BPTree(int _order) : order(_order), root(nullptr) {}

    void insert(const T& key) {
        if (!root) {
            root = new Node<T>(true);
        }

        Node<T>* leaf = findLeafNode(key);
        auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        leaf->keys.insert(it, key);

        if (leaf->keys.size() >= order) {
            splitLeafNode(leaf);
        }
    }

    bool search(const T& key) {
        if (!root) return false;

        Node<T>* leaf = findLeafNode(key);
        auto it = std::find(leaf->keys.begin(), leaf->keys.end(), key);
        return it != leaf->keys.end();
    }

    // Destructor to handle memory deallocation
    ~BPTree() {
        // Recursive delete logic for nodes
    }
};

int main() {
    BPTree<int> bptree(3); // Example with order 3
    bptree.insert(10);
    bptree.insert(20);
    bptree.insert(5);

    if (bptree.search(20)) {
        std::cout << "Found 20" << std::endl;
    } else {
        std::cout << "20 not found" << std::endl;
    }

    return 0;
}
