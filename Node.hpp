//coheny405@gmial.com
#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

#include "Complex.hpp"

template <typename T> // T is a generic type

class Node {
private:
    T data; 
    std::vector<Node<T>*> children; // A vector of pointers to the children nodes

public: 
    
    // Constructor
    Node(T value) : data(value) {}

    // Destructor
    ~Node() {
        for (Node<T>* child : children) {
            delete child;
        }
    }

    // Function to get a reference to the data of the node type T
    const T &getData() const {
        return data;
    }

    // Function to set the data of the node type T
    void setData(T data) {
        this->data = data;
    }

    
    // Function to add a child node
    void addChild(Node<T>* child) {
        children.push_back(child);
    }

    // Overloade function to add a child node at a specific index
    void addChild(Node<T>* child, size_t index) {
        // Increase the size of the vector if the index is out of bounds
        if (index >= children.size()) {
            children.resize(index + 1, nullptr);
        }
        if (children.at(index) == nullptr) {
            children.at(index) = child; 
        } else {
            throw std::runtime_error("Index is already occupied");
        }
    }

   
    // Function to get a reference to vector of pointers to the children nodes type T
    const std::vector<Node<T>*> &getChildren() const {
        return children;
    }

    // Operator overloading for the << operator
    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        os << node.data;
        return os;
    }

};