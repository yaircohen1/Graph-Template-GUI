// coheny405@gmail.com
#pragma once

#include <iostream>
#include <stack>
#include <unordered_set>
#include <queue>

#include "Node.hpp"

// Base class for all iterators
template<typename T>
class IteratorBase {
public:
    virtual ~IteratorBase() = default;
    virtual bool operator!=(const IteratorBase& other) const = 0;
    virtual const T& operator*() const = 0; 
    virtual IteratorBase& operator++() = 0;
};

// Pre Order Iterator inheriting from IteratorBase
template<typename T>
class PreOrderIterator: public IteratorBase<T> {
    protected:
        Node<T>* current; // A pointer to the current node
        std::stack<Node<T>*> stackNodes; // A stack to store nodes

    public:
        PreOrderIterator (Node<T>* root) {
            if (root) {
                stackNodes.push(root);
                advance();
            } else {
                current = nullptr;
            }
        }

        // Operator overloading for the != operator to check if the current node is not equal to the other node
        bool operator!=(const IteratorBase<T>& other) const override {
            const PreOrderIterator* otherPtr = dynamic_cast<const PreOrderIterator*>(&other);
            if (otherPtr) {
                return current != otherPtr->current;
            }
            return true;
        }
        

        // Operator overloading for the * operator to get reference to the T value of the current node
        const T& operator*() const override {
            if (current == nullptr) {
                throw std::runtime_error("Dereferencing a null pointer");
            }
            return current->getData();
        }

        // Operator overloading for the ++ operator to advance to the next node
        IteratorBase<T>& operator++() override {
            advance();
            return *this; // return the current iterator
        }
    
    protected:
        void advance() {
            // If the stack is empty, set the current node to null
            if (stackNodes.empty()) {
                current = nullptr;
                return;
            }       

            current = stackNodes.top(); // Get the top node from the stack
            stackNodes.pop(); // Remove the top node from the stack

            const auto& children = current->getChildren(); // Get the children of the current node
            
            // Iterate through the children in reverse order and push them to the stack
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                stackNodes.push(*it); // Push the child node to the stack
            }
        }

    };

    // Post-Order iterator inheriting from IteratorBase
    template<typename T>
    class PostOrderIterator : public IteratorBase<T> {
    private:
        Node<T>* current; // A pointer to the current node
        std::stack<Node<T>*> stackNodes; // A stack to store nodes
        std::unordered_set<Node<T>*> visitedNodes; // A set to store visited nodes 

    public:
        PostOrderIterator (Node<T>* root) {
            if (root) {
                stackNodes.push(root);
                advance();
            } else {
                current = nullptr;
            }
        }

        // Operator overloading for the != operator to check if the current node is not equal to the other node
        bool operator!=(const IteratorBase<T>& other) const override {
            const PostOrderIterator* otherPtr = dynamic_cast<const PostOrderIterator*>(&other);
            if (otherPtr) {
                return current != otherPtr->current;
            }
            return true;
        }

        // Operator overloading for the * operator to get reference to the T value of the current node
        const T& operator*() const override {
            if (current == nullptr) {
                throw std::runtime_error("Dereferencing a null pointer");
            }
            return current->getData();
        }

        // Operator overloading for the ++ operator to advance to the next node
        IteratorBase<T>& operator++() override {
            advance();
            return *this; // return the current iterator
        }

    private:
        void advance() {
            while (!stackNodes.empty()) {
                Node<T>* node = stackNodes.top(); // Get the top node from the stack

                // If the node has no children or the node has been visited, set the current node to the node and pop the stack
                if (node->getChildren().empty() || visitedNodes.count(node) > 0) { 
                    current = node;
                    stackNodes.pop();
                    return;
                }

                visitedNodes.insert(node); // Insert the node to the visited set
                // Iterate through the children in reverse order and push them to the stack
                for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it) {
                    stackNodes.push(*it);
                }
            }

            current = nullptr;
        }
    }; 

    // Class In-Order iterator inheriting from IteratorBase
    template<typename T>
    class InOrderIterator: public IteratorBase<T> {
    private:
        Node<T>* current; // A pointer to the current node
        std::stack<Node<T>*> stackNodes; // A stack to store nodes
    
    public:
        InOrderIterator (Node<T>* root) {
            if (root) {
                pushLeftMostNodes(root);
                advance();
            } else {
                current = nullptr;
            }
        }
    
        // Operator overloading for the != operator to check if the current node is not equal to the other node
        bool operator!=(const IteratorBase<T>& other) const override {
            const InOrderIterator* otherPtr = dynamic_cast<const InOrderIterator*>(&other);
            if (otherPtr) {
                return current != otherPtr->current;
            }
            return true;
        }

        // Operator overloading for the * operator to get reference to the T value of the current node
        const T& operator*() const override {
            if (current == nullptr) {
                throw std::runtime_error("Dereferencing a null pointer");
            }
            return current->getData();
        }

        // Operator overloading for the ++ operator to advance to the next node
        IteratorBase<T>& operator++() override {
            advance();
            return *this; // return the current iterator
        }
    
    private:
        void pushLeftMostNodes(Node<T>* node) {
            while (node != nullptr) {
                stackNodes.push(node);
                if (!node->getChildren().empty()) {
                    node = node->getChildren().front();
                } else {
                    node = nullptr;
                }
            }
        }

        void advance() {
            if (stackNodes.empty()) {
                current = nullptr;
                return;
            }

            current = stackNodes.top();
            stackNodes.pop();

            if (!current->getChildren().empty() && current->getChildren().size() > 1) {
                pushLeftMostNodes(current->getChildren().back());
            }
        }  
};

    // Class for the BFS iterator inheriting from IteratorBase
    template<typename T>
    class BFSIterator: public IteratorBase<T>{
    protected:
        Node<T>* current; // A pointer to the current node
        std::queue<Node<T>*> queueNodes; // A queue to store nodes

    public:
        BFSIterator(Node<T>* root) {
            if (root) {
                queueNodes.push(root);
                advance();
            } else {
                current = nullptr;
            }
        }

        // Operator overloading for the != operator to check if the current node is not equal to the other node
        bool operator!=(const IteratorBase<T>& other) const override {
            const BFSIterator* otherPtr = dynamic_cast<const BFSIterator*>(&other); 
            if (otherPtr) {
                return current != otherPtr->current;
            }
            return true;
        }

        // Operator overloading for the * operator to get reference to the T value of the current node
        const T& operator*() const override {
            if (current == nullptr) {
                throw std::runtime_error("Dereferencing a null pointer");
            }
            return current->getData();
        }

        // Operator overloading for the ++ operator to advance to the next node
        IteratorBase<T>& operator++() override {
            advance();
            return *this; // return the current iterator
        }

    private:
        void advance() {
            if (queueNodes.empty()) {
                current = nullptr;
                return;
            }

            current = queueNodes.front(); // Get the front node from the queue
            queueNodes.pop(); // Remove the front node from the queue

            const auto& children = current->getChildren(); // Get the children of the current node

            // Iterate through the children and push them to the queue
            for (auto it = children.begin(); it != children.end(); ++it) {
                queueNodes.push(*it); // Push the child node to the queue
            }
        }
    };

    // Class for the DFS iterator inheriting from PreOrderIterator
    template<typename T>
    class DFSIterator : public PreOrderIterator<T> {
    public:
        DFSIterator(Node<T>* root) : PreOrderIterator<T>(root) {}
        

        bool operator!=(const IteratorBase<T>& other) const override {
        const DFSIterator* otherPtr = dynamic_cast<const DFSIterator*>(&other);
        if (otherPtr) {
            return this->current != otherPtr->current;
        }
        return true;
        }

        const T& operator*() const override {
        return PreOrderIterator<T>::operator*();
        }

        IteratorBase<T>& operator++() override {
        return PreOrderIterator<T>::operator++();
        }
    };

    // Class for the Heap iterator inheriting from BFSIterator
    template<typename T>
    class HeapIterator : public BFSIterator<T> {
    public:
        HeapIterator(Node<T>* root) : BFSIterator<T>(root) {}

        bool operator!=(const IteratorBase<T>& other) const override {
            const HeapIterator* otherPtr = dynamic_cast<const HeapIterator*>(&other);
            if (otherPtr) {
                return this->current != otherPtr->current;
            }
            return true;
        }

        const T& operator*() const override {
            return BFSIterator<T>::operator*();
        }

        IteratorBase<T>& operator++() override {
            return BFSIterator<T>::operator++();
        }
    };

    

    

    
