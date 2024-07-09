
# Tree and Graph Visualizer

## Project Description
This project implements a tree data structure and visualizes it using SFML (Simple and Fast Multimedia Library). The visualization includes various traversal orders such as pre-order, post-order, in-order, DFS (Depth-First Search), BFS (Breadth-First Search) and Min-Heap.

## Project Structure

### Class Hierarchy
1. **Tree**
    - Represents a K-ary tree.
    - Contains functionalities for adding nodes and performing different types of traversals.
    
2. **Node**
    - Represents a single node in the tree.
    - Stores the data and a list of children nodes.

3. **IteratorBase**
    - Abstract base class for different tree iterators.
    - Provides common functionality and interface for derived iterator classes.

4. **PreOrderIterator**
    - Inherits from `IteratorBase`.
    - Implements pre-order traversal.

5. **InOrderIterator**
    - Inherits from `IteratorBase`.
    - Implements in-order traversal for binary trees.

6. **PostOrderIterator**
    - Inherits from `IteratorBase`.
    - Implements post-order traversal.

7. **BFSIterator**
    - Inherits from `IteratorBase`.
    - Implements breadth-first search (BFS) traversal.

8. **DFSIterator**
    - Inherits from `IteratorBase`.
    - Implements depth-first search (DFS) traversal.

9. **HeapIterator**
    - Inherits from `BFSIterator`.
    - Converts a binary tree to a min-heap and traverses it.

10. **GraphVisualizer**
    - Visualizes the tree structure using the SFML library.
    - Provides functionalities to visualize the tree and highlight nodes during traversal.

11. **Complex**
    - Represents a complex number with real and imaginary parts.
    - Provides functionalities to handle operations on complex numbers.

## Libraries Used

### 1. Standard Template Library (STL)
The Standard Template Library (STL) is used extensively in this project for data structures and algorithms, including:
- `vector`: To store and manage dynamic arrays.
- `unordered_map`: To store and manage key-value pairs.
- `queue`: To implement the BFS traversal.
- `stack`: To implement the DFS traversal.
- `iostream`: For input and output operations.
- `string`: To handle strings.

### 2. Simple and Fast Multimedia Library (SFML)
The SFML library is used for graphical representation and visualization of the tree. The relevant SFML modules include:
- `SFML/Graphics.hpp`: For rendering shapes, text, and handling the window.
- `SFML/Window.hpp`: For handling window events and interactions.
- `SFML/System.hpp`: For system-specific functionalities such as sleeping.

### 3. Thread Library
The Thread library is part of the C++11 standard and is used for creating and managing threads, allowing us to implement delays during the tree traversal visualization.
- `thread`: To create and manage threads.
- `chrono`: To handle time-related functions and introduce delays.

## Usage

### Makefile
To compile and run the project, a `makefile` is provided. Here are the available commands:
- make all       // Build the project
- ./test        // Test the logic of the code
- ./demo       // Run the main program without visualization
- ./tree      // Run the main program with visualization






