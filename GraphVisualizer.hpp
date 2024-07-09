//coheny405@gmial.com
#pragma once

#include <SFML/Graphics.hpp>
#include "Tree.hpp"
#include "Node.hpp"
#include <unordered_map> // For std::unordered_map
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::this_thread::sleep_for

template <typename T, size_t K = 2>
class GraphVisualizer {
private:
    const Tree<T, K>& tree;
    std::string treeName;
    std::unordered_map<Node<T>*, sf::Vector2f> nodePositions; // Map to store the positions of the nodes

    void setPosition(Node<T>* node, sf::Vector2f pos) {  // sf::Vector2f is a 2D vector (x, y)
        nodePositions[node] = pos;
    }

    sf::Vector2f getPosition(Node<T>* node) const {
        auto it = nodePositions.find(node);
        if (it != nodePositions.end()) {
            return it->second;
        }
        return sf::Vector2f(0, 0); // Return (0, 0) if the node is not found
    }

    // Function to draw a node (parameters are window, node, font)
    void drawNode(sf::RenderWindow& window, Node<T>* node, const sf::Font& font, sf::Color color = sf::Color::Green) const {
        if (!node) return;

        sf::CircleShape circle(20);
        circle.setFillColor(color);
        circle.setPosition(getPosition(node) - sf::Vector2f(20, 20));
        window.draw(circle);

        sf::Text text;
        text.setFont(font);

        if constexpr (std::is_same_v<T, Complex>) {
            text.setString(node->getData().to_string());
        } else {
            text.setString(std::to_string(node->getData()));
        }

        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(getPosition(node) - sf::Vector2f(10, 10));
        window.draw(text);
    }


    // Function to draw the edges of the tree
    void drawEdges(sf::RenderWindow& window, Node<T>* node) const {
        if (!node) return;

        sf::Vector2f pos1 = getPosition(node);
        for (Node<T>* child : node->getChildren()) {
            sf::Vector2f pos2 = getPosition(child);
            sf::Vertex line[] = {
                sf::Vertex(pos1, sf::Color::Black),
                sf::Vertex(pos2, sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    // Function to layout the tree (xOffset is the horizontal offset between the nodes)
    void layoutTree(Node<T>* node, sf::Vector2f position, float xOffset) {
        if (!node) return;

        setPosition(node, position); // Set the position of the node

        float childOffset = xOffset / node->getChildren().size(); // Calculate the child offset
        float currentX = position.x - (xOffset / 2); // Calculate the current x position

        // Loop through the children of the node and layout the tree
        for (Node<T>* child : node->getChildren()) {
            layoutTree(child, sf::Vector2f(currentX, position.y + 100), childOffset);
            currentX += childOffset; // Update the current x position
        }
    }

    // Function to draw the tree
    void drawTree(sf::RenderWindow& window, const sf::Font& font) const {
        window.clear(sf::Color::White);

        // Draw the edges of the tree
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            Node<T>* node = tree.find_node(*it);
            drawEdges(window, node);
        }

        // Draw the nodes of the tree
        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            Node<T>* node = tree.find_node(*it);
            drawNode(window, node, font);
        }
    }

    // Drew the order of the tree (window, order)
    void drawOrder(sf::RenderWindow& window, const std::vector<T>& order, const std::string& iteratorName, const sf::Font& font) const {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);

        std::string orderStr;
        orderStr += iteratorName + ": ";
         for (const auto& val : order) {
            if constexpr (std::is_same_v<T, Complex>) {
                orderStr += val.to_string() + " ";
            } else {
                orderStr += std::to_string(val) + " ";
            }
        }
        text.setString(orderStr);

         for (const auto& val : order) {
            if constexpr (std::is_same_v<T, Complex>) {
                orderStr += val.to_string() + " ";
            } else {
                orderStr += std::to_string(val) + " ";
            }
        }
        
        // Center the text horizontally at the bottom of the window
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(window.getSize().x / 2.0f, window.getSize().y - 30);

        window.draw(text);
    }

    
public:
    // Constructor
    GraphVisualizer(const Tree<T, K>& tree, const std::string& name) : tree(tree), treeName(name) {
        if (tree.get_root()) {
            //set the position of the root node to the center of the window under the headline
            layoutTree(tree.get_root(), sf::Vector2f(400, 150), 400); // sf::Vector2f is a 2D vector (400, 50) and 400 is the horizontal offset 
        }
    }

   
    // Function to visualize the tree (window)
    void visualize(sf::RenderWindow& window) const {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Failed to load font");
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            drawTree(window, font);
            window.display();
        }
    }
    

    // Function to visualize the tree with an iterator (begin, end, window)
    template <typename Iterator>
    void visualizeWithIterator(const std::string& iteratorName, Iterator begin, Iterator end, sf::RenderWindow& window) const {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Failed to load font");
        }

        auto it = begin;
        std::vector<T> order;

        while (window.isOpen()) { 
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            if (!(iteratorName == "myHeap")) {
                drawTree(window, font);
            }
            drawOrder(window, order, iteratorName, font);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Show the initial tree for 2 seconds
            
            if (it != end) {
                Node<T>* node = tree.find_node(*it);
                if (node) {
                    drawNode(window, node, font, sf::Color::Red);
                    order.push_back(*it);
                    ++it;
                    window.display();
                    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep for 500 milliseconds
                }
            }
            
            if (!(it != end) && !order.empty()) {
                for (const auto& val : order) {
                    std::cout << val << " ";
                }
                std::cout << std::endl;
                order.clear();
                break;
            }
        }
    }
};








