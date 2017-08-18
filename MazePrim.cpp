#include <algorithm>
#include <array>
#include <list>
#include <stack>
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include "MazePrim.h"
#include "MazeRecursiveBacktracker.h"

MazePrim::MazePrim(unsigned int size, unsigned short difficulty) : window(sf::VideoMode(800, 800), "Maze maker!!"){
    srand(time(nullptr));

    window.clear(sf::Color::Black);
    this->size = size;
    this->difficulty = difficulty;
    grid.resize(size * size);
    std::fill(grid.begin(), grid.end(), 0);
    renderedMaze.create(size*2 + 1, size*2 + 1, sf::Color::Black);

    renderedMaze.setPixel(1, 0, sf::Color::Green);

    texture.loadFromImage(renderedMaze);
    rectangle.setPosition(0, 0);
    rectangle.setSize(sf::Vector2f(800, 800));
    rectangle.setTexture(&texture);
    window.draw(rectangle);
    window.display();
}

void MazePrim::createMaze() {

    std::vector<std::pair<int, int>> frontier;
    grid[0] = 1;
    renderedMaze.setPixel(1, 1, sf::Color::White);
    grid[1] = 2;
    renderedMaze.setPixel(3, 1, sf::Color::Red);
    grid[size] = 2;
    renderedMaze.setPixel(1, 3, sf::Color::Red);
    frontier.push_back(std::make_pair(1, 0));
    frontier.push_back(std::make_pair(0, 1));

    while(!frontier.empty()) {
        int toBecameFull = rand() % frontier.size();
        grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size] = 1;
        renderedMaze.setPixel(frontier[toBecameFull].first * 2 + 1, frontier[toBecameFull].second * 2 + 1, sf::Color::White);
        if (frontier[toBecameFull].first != size - 1) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size + 1] == 0) {
            grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size + 1] = 2;
            frontier.push_back(std::make_pair(frontier[toBecameFull].first + 1, frontier[toBecameFull].second));
                renderedMaze.setPixel((frontier[toBecameFull].first + 1)*2+1, (frontier[toBecameFull].second)*2+1, sf::Color::Red);
        }
        if (frontier[toBecameFull].first != 0) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size - 1] == 0) {
            grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size - 1] = 2;
            frontier.push_back(std::make_pair(frontier[toBecameFull].first - 1, frontier[toBecameFull].second));
                renderedMaze.setPixel((frontier[toBecameFull].first - 1) * 2+1, (frontier[toBecameFull].second) * 2+1, sf::Color::Red);
        }
        if (frontier[toBecameFull].second != size - 1) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size + size] == 0) {
            grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size + size] = 2;
            frontier.push_back(std::make_pair(frontier[toBecameFull].first, frontier[toBecameFull].second + 1));
                renderedMaze.setPixel((frontier[toBecameFull].first)*2+1, (frontier[toBecameFull].second + 1)*2+1, sf::Color::Red);
        }
        if (frontier[toBecameFull].second != 0) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size - size] == 0) {
            grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size - size] = 2;
            frontier.push_back(std::make_pair(frontier[toBecameFull].first, frontier[toBecameFull].second - 1));
                renderedMaze.setPixel((frontier[toBecameFull].first)*2+1, (frontier[toBecameFull].second - 1)*2+1, sf::Color::Red);
        }

        auto directions = MazeRecursiveBacktracker::randomDirections();
        for(int i=0; i<4; i++){
            if (directions[i] == 0 && frontier[toBecameFull].first != size - 1) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size + 1] == 1) {
                renderedMaze.setPixel(frontier[toBecameFull].first * 2 + 2, frontier[toBecameFull].second * 2 + 1, sf::Color::White);
                break;
            }
            if (directions[i] == 1 && frontier[toBecameFull].first != 0) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size - 1] == 1) {
                renderedMaze.setPixel(frontier[toBecameFull].first * 2, frontier[toBecameFull].second * 2 + 1, sf::Color::White);
                break;
            }
            if (directions[i] == 2 && frontier[toBecameFull].second != size - 1) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size + size] == 1) {
                renderedMaze.setPixel(frontier[toBecameFull].first * 2 + 1, frontier[toBecameFull].second * 2 + 2, sf::Color::White);
                break;
            }
            if (directions[i] == 3 && frontier[toBecameFull].second != 0) if (grid[frontier[toBecameFull].first + frontier[toBecameFull].second * size - size] == 1) {
                renderedMaze.setPixel(frontier[toBecameFull].first * 2 + 1, frontier[toBecameFull].second * 2, sf::Color::White);
                break;
            }
        }
        frontier.erase(frontier.begin() + toBecameFull);
        if(size <= 25) {
            texture.loadFromImage(renderedMaze);
            window.draw(rectangle);
            window.display();
            bool exit = false;
            while (true) {
                sf::Event event;
                window.pollEvent(event);
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) exit = true;
                    break;
                }
            }
            if (exit) break;
        }
    }

    renderedMaze.setPixel(size * 2 -1, size*2, sf::Color::Red);

    int toCarve = size * size / 1000 * (100 - difficulty + 1);
    for (int i=0; i<toCarve; i++) {
        int x = (rand() % (size - 2)) + 1;
        int y = (rand() % (size - 2)) + 1;
        int direction = rand() % 4;
        switch (direction) {
            case 0:
                if(renderedMaze.getPixel(x * 2 + 2, y * 2 + 1) == sf::Color::White) i--;
                renderedMaze.setPixel(x * 2+ 2, y * 2 + 1, sf::Color::White);
                break;
            case 1:
                if(renderedMaze.getPixel(x * 2 + 1, y * 2) == sf::Color::White) i--;
                renderedMaze.setPixel(x * 2 + 1, y * 2, sf::Color::White);
                break;
            case 2:
                if(renderedMaze.getPixel(x * 2, y * 2 + 1) == sf::Color::White) i--;
                renderedMaze.setPixel(x * 2, y * 2 + 1, sf::Color::White);
                break;
            case 3:
                if(renderedMaze.getPixel(x * 2 + 1, y * 2 + 2) == sf::Color::White) i--;
                renderedMaze.setPixel(x * 2 + 1, y * 2 + 2, sf::Color::White);
                break;
        }
        if (size <= 25) {
            texture.loadFromImage(renderedMaze);
            window.draw(rectangle);
            window.display();
            bool exit = false;
            while (true) {
                sf::Event event;
                window.pollEvent(event);
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) exit = true;
                    break;
                }
            }
            if (exit) break;
        }
    }

    renderedMaze.saveToFile("maze.png");
}


