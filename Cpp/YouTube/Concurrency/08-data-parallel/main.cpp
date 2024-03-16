#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>    // for fill
#include <memory>
#include <chrono>       // for sleep

// Compile with: g++ -std=c++17 main.cpp -o main.out [-lpthread] [-lsfml-graphics] [-lsfml-window] [-lsfml-system]
// Compile with: g++ -std=c++17 main.cpp -o main.out -lpthread -lsfml-graphics -lsfml-window -lsfml-system

// Third party libraries
// Install with: sudo apt-get install libsfml-dev
#include <SFML/Graphics.hpp>

// Globally available grid
static std::vector<int> grid;
// Global array of all of our objects
std::vector<std::unique_ptr<sf::Shape>> shapes;
// Keeps track of the program running
bool isRunning = true;

// Function to update grid
// This will be handled in each thread, independently working
// on the task.
void update_grid(int x, int y) {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        grid[y*2 + x] = rand()%4;
    }
}

// Entry point into our program
int main() {
    // Initialize our grid with 4 entries
    grid.reserve(4); // Pre allocates memory for 4 ints
    std::fill(begin(grid), end(grid), 0); // Fills entire vector with zeroes (0)

    // Pick out the shape being drawn
    // in our grid and update it accordingly.
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            shapes.push_back(std::make_unique<sf::CircleShape>(100.0f));
        }
    }

    // Lainch threads
    std::vector<std::thread> threads;
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            threads.push_back(std::thread(update_grid, x, y));
        }
    }

    // Main program loop
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML with C++ threads");

    // Main Game loop
    while (window.isOpen() && isRunning) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
        }

        // Clear the window
        window.clear();
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                // Set the position
                shapes[y*2+x]->setPosition(x*200, y*200);
                // Update the color
                switch (grid[y*2+x]) {
                    case 0:
                        shapes[y*2+x]->setFillColor(sf::Color::Red);
                        break;
                    case 1:
                        shapes[y*2+x]->setFillColor(sf::Color::Green);
                        break;
                    case 2:
                        shapes[y*2+x]->setFillColor(sf::Color::Blue);
                        break;
                    case 3:
                        shapes[y*2+x]->setFillColor(sf::Color::Magenta);
                        break;
                    
                    default:
                        break;
                }           
            }
        }

        // Draw all of our shapes
        for (auto& shape: shapes) {
            window.draw(*shape);
        }
        window.display();
    }

    // Join threads before program execution terminates
    for (auto& th : threads) {
        th.join();
    }

    // Program finish
    std::cout << "Program Terminating" << std::endl;

    return 0;
}