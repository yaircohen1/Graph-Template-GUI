// coheny405@gmail.com
#include <iostream>
#include "Tree.hpp"
#include "Node.hpp"
#include "Complex.hpp"

int main() {
    try {
        Tree<int> binaryTree; // Create a binary tree 
        binaryTree.add_root(1); // Add the root node
        binaryTree.add_sub_node(1, 2);
        binaryTree.add_sub_node(1, 3);
        binaryTree.add_sub_node(2, 4);
        binaryTree.add_sub_node(2, 5);
        binaryTree.add_sub_node(3, 6);
    
        std::cout << "Binary Tree (default K=2) Pre-Order: ";
        for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        
        std::cout << "Binary Tree (default K=2) Post-Order: ";
        for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        std::cout << "Binary Tree (default K=2) In-Order: ";
        for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        Tree<int> binaryTreeInOrder; // Create a binary tree for In-Order traversal
        binaryTreeInOrder.add_root(1); 
        binaryTreeInOrder.add_sub_node(1, 2);
        binaryTreeInOrder.add_sub_node(1, 3);
        binaryTreeInOrder.add_sub_node(2, 4);
        binaryTreeInOrder.add_sub_node(2, 5);
        binaryTreeInOrder.add_sub_node(3, 6, 1); // Add a sub-node with a specific index to the right

        std::cout << "Binary Tree (default K=2, node val:6 is on the right side) In-Order: ";
        for (auto it = binaryTreeInOrder.begin_in_order(); it != binaryTreeInOrder.end_in_order(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        Tree<int, 3> ternaryTree; // Create a K-ary tree with K=3
        ternaryTree.add_root(1);
        ternaryTree.add_sub_node(1, 2);
        ternaryTree.add_sub_node(1, 3);
        ternaryTree.add_sub_node(1, 4);
        ternaryTree.add_sub_node(2, 5);
        ternaryTree.add_sub_node(2, 6);
        ternaryTree.add_sub_node(2, 7);
        ternaryTree.add_sub_node(4, 8);

        std::cout << "Ternary Tree (K=3) Post-Order (return DFS): ";
        for (auto it = ternaryTree.begin_post_order(); it != ternaryTree.end_post_order(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        std::cout << "Ternary Tree (K=3) DFS: ";
        for (auto it = ternaryTree.begin_dfs_scan(); it != ternaryTree.end_dfs_scan(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        std::cout << "Ternary Tree (K=3) BFS: ";
        for (auto it = ternaryTree.begin_bfs_scan(); it != ternaryTree.end_bfs_scan(); ++it) {
            std::cout
            << *it << " ";
        }
        std::cout << std::endl;

        Tree<Complex, 2> complexTree; // Create a K-ary tree with K=2 and Complex data type
        complexTree.add_root(Complex(1, 1));
        complexTree.add_sub_node(Complex(1, 1), Complex(2, 2));
        complexTree.add_sub_node(Complex(1, 1), Complex(3, 3));
        complexTree.add_sub_node(Complex(2, 2), Complex(4, 4));
        complexTree.add_sub_node(Complex(2, 2), Complex(5, 5));
        complexTree.add_sub_node(Complex(3, 3), Complex(6, 6));

        std::cout << "Complex Tree (K=2) Pre-Order: ";
        for (auto it = complexTree.begin_pre_order(); it != complexTree.end_pre_order(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        Tree<double,2> doubleTree; // Create a K-ary tree with K=2 and double data type not un-sorted
        doubleTree.add_root(5.7);   
        doubleTree.add_sub_node(5.7, 3.2);
        doubleTree.add_sub_node(5.7, 7.1);
        doubleTree.add_sub_node(3.2, 2.1);
        doubleTree.add_sub_node(3.2, 4.5);
        doubleTree.add_sub_node(7.1, 6.3);
        doubleTree.add_sub_node(7.1, 8.9);

        std::cout << "Double Tree (K=2) Min heap: ";
        for (auto it = doubleTree.begin_heap(); it != doubleTree.end_heap(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}