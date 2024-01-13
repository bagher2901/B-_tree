#include <iostream>
#include <vector>

template <typename T>
class BPTree;

template <typename T>
class Node {
    bool isLeaf;
    std::vector<T> keys;
    std::vector<Node<T>*> children;
    friend class BPTree<T>;

public:
    Node(bool _isLeaf) : isLeaf(_isLeaf) {}
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

public:
    BPTree(int _order) : order(_order), root(nullptr) {}

    void insert(const T& key) {
        if (!root) {
            root = new Node<T>(true);
        }

        // Find the leaf node where this key should be inserted
        Node<T>* leaf = findLeafNode(key);

        // Insert key in the leaf node
        auto it = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        leaf->keys.insert(it, key);

        // Split if needed and propagate up
        // (This part is simplified and needs to handle more cases in a full implementation)
        if (leaf->keys.size() >= order) {
            // Splitting logic here...
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
