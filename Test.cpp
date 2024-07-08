// coheny405@gmail.com

#include "Complex.hpp"
#include "Iterator.hpp"
#include "Node.hpp"
#include "Tree.hpp"

#include "doctest.h"
#include <sstream>
#include <string>

// test Complex class
TEST_CASE("Testing Complex class") {
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3(4, 6);

    CHECK(c1.getReal() == 1);
    CHECK(c1.getImag() == 2);

    CHECK(c1 + c2 == c3);
    CHECK(c1 - c2 == Complex(-2, -2));
    CHECK(c1 * c2 == Complex(-5, 10));
    CHECK(c1 / c2 == Complex(0.44, 0.08));

    c1 += c2;
    CHECK(c1 == c3);
    c1 -= c2;
    CHECK(c1 == Complex(1, 2));
    c1 *= c2;
    CHECK(c1 == Complex(-5, 10));
    c1 /= c2;
    CHECK(c1 == Complex(1, 2));

    CHECK(c1 != c2);
    CHECK(c1 == Complex(1, 2));

    CHECK(c1 < c2);
    CHECK(c1 <= c2);
    CHECK(c2 > c1);
    CHECK(c2 >= c1);

    std::stringstream ss;
    ss << c1;
    CHECK(ss.str() == "1+2i");
}

// test Node class
TEST_CASE("Testing Node class") {
    Node<int> node(1);
    CHECK(node.getData() == 1);
    CHECK(node.getChildren().size() == 0);

    node.addChild(new Node<int>(2));
    CHECK(node.getChildren().size() == 1);
    CHECK(node.getChildren()[0]->getData() == 2);

    CHECK_THROWS(node.addChild(new Node<int>(3), 0));
    node.addChild(new Node<int>(3), 1);
    CHECK(node.getChildren()[1]->getData() == 3);

}

// test Tree class
TEST_CASE("Testing Tree class") {
    Tree<int> binaryTree;
    binaryTree.add_root(1);
    binaryTree.add_sub_node(1, 2);
    binaryTree.add_sub_node(1, 3);
    binaryTree.add_sub_node(2, 4);
    binaryTree.add_sub_node(2, 5);
    binaryTree.add_sub_node(3, 6);
    CHECK_THROWS(binaryTree.add_root(7));
    CHECK_THROWS(binaryTree.add_sub_node(3,7,0));

    std::stringstream ss;
    for (auto it = binaryTree.begin_pre_order(); it != binaryTree.end_pre_order(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "1 2 4 5 3 6 ");

    ss.str("");
    for (auto it = binaryTree.begin_post_order(); it != binaryTree.end_post_order(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "4 5 2 6 3 1 ");

    ss.str("");
    for (auto it = binaryTree.begin_in_order(); it != binaryTree.end_in_order(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "4 2 5 1 6 3 ");

    ss.str("");
    for (auto it = binaryTree.begin_bfs_scan(); it != binaryTree.end_bfs_scan(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "1 2 3 4 5 6 ");

    ss.str("");
    for (auto it = binaryTree.begin_heap(); it != binaryTree.end_heap(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "1 2 3 4 5 6 ");

    Tree<int> binaryTreeInOrder;
    binaryTreeInOrder.add_root(1);
    binaryTreeInOrder.add_sub_node(1, 2);
    binaryTreeInOrder.add_sub_node(1, 3);
    binaryTreeInOrder.add_sub_node(2, 4);
    binaryTreeInOrder.add_sub_node(2, 5);
    binaryTreeInOrder.add_sub_node(3, 6, 1);

    ss.str("");
    for (auto it = binaryTreeInOrder.begin_in_order(); it != binaryTreeInOrder.end_in_order(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "4 2 5 1 3 6 ");

    Tree<int, 3> ternaryTree;
    ternaryTree.add_root(1);
    ternaryTree.add_sub_node(1, 2);
    ternaryTree.add_sub_node(1, 3);
    ternaryTree.add_sub_node(1, 4);
    ternaryTree.add_sub_node(2, 5);
    ternaryTree.add_sub_node(2, 6);
    ternaryTree.add_sub_node(2, 7);
    ternaryTree.add_sub_node(4, 8);

    ss.str("");
    for (auto it = ternaryTree.begin_post_order(); it != ternaryTree.end_post_order(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "1 2 5 6 7 3 4 8 ");

    CHECK_THROWS(ternaryTree.myHeap());

    ss.str("");
    for (auto it = ternaryTree.begin_dfs_scan(); it != ternaryTree.end_dfs_scan(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "1 2 5 6 7 3 4 8 ");

    ss.str("");
    for (auto it = ternaryTree.begin_bfs_scan(); it != ternaryTree.end_bfs_scan(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "1 2 3 4 5 6 7 8 ");

    Tree <Complex> binaryComlexTree;
    binaryComlexTree.add_root(Complex(1, 2));
    binaryComlexTree.add_sub_node(Complex(1, 2), Complex(3, 4));
    binaryComlexTree.add_sub_node(Complex(1, 2), Complex(5, 6));
    binaryComlexTree.add_sub_node(Complex(3, 4), Complex(7, 8));
    binaryComlexTree.add_sub_node(Complex(3, 4), Complex(9, 10));
    binaryComlexTree.add_sub_node(Complex(5, 6), Complex(11, 12));

    ss.str("");
    for (auto it = binaryComlexTree.begin_pre_order(); it != binaryComlexTree.end_pre_order(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "1+2i 3+4i 7+8i 9+10i 5+6i 11+12i ");

    Tree <std::string> stringTree; // not ordered
    stringTree.add_root("C");
    stringTree.add_sub_node("C", "F");
    stringTree.add_sub_node("C", "A");
    stringTree.add_sub_node("F", "B");
    stringTree.add_sub_node("F", "D"); 
    stringTree.add_sub_node("A", "L");
    stringTree.add_sub_node("A", "E");

    ss.str("");
    for (auto it = stringTree.begin_heap(); it != stringTree.end_heap(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "A B C F D L E ");


    // Create a K-ary tree with K=5 and double data type
    Tree<double, 5> doubleTree;
    doubleTree.add_root(5.7);
    doubleTree.add_sub_node(5.7, 3.2);
    doubleTree.add_sub_node(5.7, 7.1);
    doubleTree.add_sub_node(3.2, 2.1);
    doubleTree.add_sub_node(3.2, 4.5);
    doubleTree.add_sub_node(7.1, 6.3);
    doubleTree.add_sub_node(7.1, 8.9);
    doubleTree.add_sub_node(7.1, 14.54);
    doubleTree.add_sub_node(8.9, 11);
    doubleTree.add_sub_node(8.9, 12.7);
    doubleTree.add_sub_node(8.9, 13.1);
    doubleTree.add_sub_node(8.9, 14.2);
    doubleTree.add_sub_node(8.9, 15.3);
    doubleTree.add_sub_node(15.3, 16.4);
    doubleTree.add_sub_node(15.3, 17.5);

    ss.str("");
    for (auto it = doubleTree.begin_dfs_scan(); it != doubleTree.end_dfs_scan(); ++it) {
        ss << *it << " ";
    }
    CHECK(ss.str() == "5.7 3.2 2.1 4.5 7.1 6.3 8.9 11 12.7 13.1 14.2 15.3 16.4 17.5 14.54 ");
}


