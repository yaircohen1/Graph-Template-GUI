#include <iostream>
#include "Tree.hpp"
#include "Node.hpp"
#include "Complex.hpp"
#include "GraphVisualizer.hpp"

int main() {
    try {
        Tree<int> binaryTree; // Create a binary tree 
        binaryTree.add_root(1); // Add the root node
        binaryTree.add_sub_node(1, 2);
        binaryTree.add_sub_node(1, 3);
        binaryTree.add_sub_node(2, 4);
        binaryTree.add_sub_node(2, 5);
        binaryTree.add_sub_node(3, 6);

        GraphVisualizer<int> visualizer(binaryTree, "Binary Tree Visualization");
        {
        // Visualize the tree and get the window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree");
        
        // Visualize with Pre-Order Iterator
        visualizer.visualizeWithIterator("Pre-Order", binaryTree.begin_pre_order(), binaryTree.end_pre_order(), window);

        // Visualize with Post-Order Iterator
        visualizer.visualizeWithIterator("Post-Order",binaryTree.begin_post_order(), binaryTree.end_post_order(), window);

        // Visualize with In-Order Iterator
        visualizer.visualizeWithIterator("In-Order",binaryTree.begin_in_order(), binaryTree.end_in_order(), window);
        }
       

        Tree<int, 3> ternaryTree; // Create a K-ary tree with K=3
        ternaryTree.add_root(1);
        ternaryTree.add_sub_node(1, 2);
        ternaryTree.add_sub_node(1, 3);
        ternaryTree.add_sub_node(1, 4);
        ternaryTree.add_sub_node(2, 5);
        ternaryTree.add_sub_node(2, 6);
        ternaryTree.add_sub_node(2, 7);
        ternaryTree.add_sub_node(4, 8);

        GraphVisualizer<int, 3> visualizerTernary(ternaryTree, "Ternary Tree Visualization");
        {
        // Visualize the tree and get the window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Ternary Tree");

        // Visualize with Post-Order Iterator
        visualizerTernary.visualizeWithIterator("Post-Order", ternaryTree.begin_post_order(), ternaryTree.end_post_order(), window);
        
        // Visualize with DFS Iterator
        visualizerTernary.visualizeWithIterator("DFS", ternaryTree.begin_dfs_scan(), ternaryTree.end_dfs_scan(), window);

        // Visualize with BFS Iterator
        visualizerTernary.visualizeWithIterator("BFS", ternaryTree.begin_bfs_scan(), ternaryTree.end_bfs_scan(), window); 
        }

        // Create a K-ary tree with K=2 and Complex data type
        Tree<Complex, 2> complexTree;
        complexTree.add_root(Complex(1, 1));
        complexTree.add_sub_node(Complex(1, 1), Complex(2, 2));
        complexTree.add_sub_node(Complex(1, 1), Complex(3, 3));
        complexTree.add_sub_node(Complex(2, 2), Complex(4, 4));
        complexTree.add_sub_node(Complex(2, 2), Complex(5, 5));
        complexTree.add_sub_node(Complex(3, 3), Complex(6, 6));

        GraphVisualizer<Complex, 2> visualizerComplex(complexTree, "Complex Tree Visualization");
        {
        // Visualize the tree and get the window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Complex Tree");

        // Visualize with myHeap Iterator 
        visualizerComplex.visualizeWithIterator("myHeap", complexTree.begin_heap(), complexTree.end_heap(), window);
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }



    return 0;
}



