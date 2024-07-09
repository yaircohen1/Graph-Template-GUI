// coheny405@gmail.com
#pragma once

#include <memory>
#include <stdexcept>

#include "Node.hpp"
#include "Iterator.hpp"

template <typename T, size_t K=2> // generic template for tree Kary with a default value of 2 for K
class Tree {
private:
    Node<T>* root; // A pointer to the root node

    // Function to find a node with a specific value
    Node<T>* find_node(Node<T>* node, const T& val) const {
        if (node->getData() == val) {
            return node;
        }
        // Recursively search for the node
        for (Node<T>* child : node->getChildren()) {
            Node<T>* found = find_node(child, val);
            if (found) {
                return found;
            }
        }
        return nullptr;
    }

public:

    // Constructor
    Tree(): root(nullptr) {}
    

    // Destructor
    ~Tree() {
        delete root;
    }

    // add a root node
    void add_root(const T& val) {
        if (root) {
            throw std::runtime_error("Root already exists");
        }
        root = new Node<T>(val);
    }

    // get the root node
    Node<T>* get_root() const {
        return root;
    }

    // add a child to specific parent if index is not mentioned, add to the free space in order in the children vector default
    void add_sub_node(const T& parentVal, const T& childVal) {
        Node<T>* parent = find_node(root, parentVal);
        if (parent){
            if (parent->getChildren().size() >= K) {
                throw std::runtime_error("Parent has reached the maximum number of children");
            }
            parent->addChild(new Node<T>(childVal));
        } else {
            throw std::runtime_error("Parent not found");
        }
    }

    // Overload add_sub_node to add a child to a specific parent at a specific index
    void add_sub_node(const T& parentVal, const T& childVal, size_t index) {
        Node<T>* parent = find_node(root, parentVal);
        if (parent) {
            if (index >= K) {
                throw std::runtime_error("Index out of bounds");
            }
            if (parent->getChildren().size() >= K) {
                throw std::runtime_error("Parent has reached the maximum number of children");
            }
            parent->addChild(new Node<T>(childVal), index);      
        } else {
            throw std::runtime_error("Parent not found");
        }
    }

    // Function to get the node by value
    Node<T>* find_node(const T& val) const {
        return find_node(root, val);
    }


    using PreOrderIter = PreOrderIterator<T>;
    using PostOrderIter = PostOrderIterator<T>;
    using InOrderIter = InOrderIterator<T>;
    using BFSIter = BFSIterator<T>;
    using DFSIter = DFSIterator<T>;
    using HeapIter = HeapIterator<T>;

    PreOrderIter begin_pre_order() const {
        return PreOrderIter(root);
    }
    
    PreOrderIter end_pre_order() const {
        return PreOrderIter(nullptr);
    }


    // constexper is used to evaluate the condition at compile time

    auto begin_post_order() const {
        if constexpr (K == 2) {
            return PostOrderIter(root);
        } else {
            return DFSIter(root);
        }
    }
    
    auto end_post_order() const {
        if constexpr (K == 2) {
            return PostOrderIter(nullptr);
        } else {
            return DFSIter(nullptr);
        }
    }

    auto begin_in_order() const {
        if constexpr (K == 2) {
            return InOrderIter(root);
        } else {
            return DFSIter(root);
        }
    }

    auto end_in_order() const {
        if constexpr (K == 2) {
            return InOrderIter(nullptr);
        } else {
            return DFSIter(nullptr);
        }
    }

    BFSIter begin_bfs_scan() const {
        return BFSIter(root);
    }

    BFSIter end_bfs_scan() const {
        return BFSIter(nullptr);
    }

    DFSIter begin_dfs_scan() const {
        return DFSIter(root);
    }

    DFSIter end_dfs_scan() const {
        return DFSIter(nullptr);
    }

    // Method myHeap convert binary tree to min heap and return the iterator for the min heap
    // Step 1: Check if the tree is binary, if not throw an exception
    // Step 2: Convert the binary tree to a vector 
    // Step 3: Build a min-heap from the collected elements
    // Step 4: Rebuild the tree as a min-heap
    // Step 5: Return a BFS iterator to the minimum heap

    void myHeap() {
        // Check if the tree is binary, else throw an exception
        if (K != 2) {
            throw std::runtime_error("The tree is not binary");
        }

        // Convert the binary tree to a vector with the BFS iterator
        std::vector<T> elements;
        for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
            elements.push_back(*it);
        }

        // Build a min-heap from the collected elements
        std::make_heap(elements.begin(), elements.end(), std::greater<T>());
        root = new Node<T>(elements.front());
        std::queue<Node<T>*> q; // A queue to store the parent nodes
        q.push(root); // Push the root node to the queue
        size_t i = 1; // Start from the second element

        // Rebuild the tree as a min-heap
        while (!q.empty() && i < elements.size()) {
            Node<T>* current = q.front();
            q.pop();
            current->addChild(new Node<T>(elements[i++])); // Add the left child
            q.push(current->getChildren().back()); // Push the left child to the queue
            // Add the right child if it exists
            if (i < elements.size()) {
                current->addChild(new Node<T>(elements[i++]));
                q.push(current->getChildren().back());
            }
        }
    }

    HeapIter begin_heap() {
        myHeap();
        return HeapIter(root);
    }

    HeapIter end_heap() {
        return HeapIter(nullptr);
    }
};


