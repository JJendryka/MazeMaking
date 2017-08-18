#include <algorithm>
#include <array>
#include <stack>
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include "MazeRecursiveBacktracker.h"

MazeRecursiveBacktracker::MazeRecursiveBacktracker(unsigned int size, unsigned short difficulty) : window(sf::VideoMode(800, 800), "Maze maker!!"){
    srand(time(nullptr));

    window.clear(sf::Color::Black);
    this->size = size;
    this->difficulty = difficulty;
    grid.resize(size * size);
    std::fill(grid.begin(), grid.end(), false);
    renderedMaze.create(size*2 + 1, size*2 + 1, sf::Color::Black);

    renderedMaze.setPixel(1, 0, sf::Color::Green);

    texture.loadFromImage(renderedMaze);
    rectangle.setPosition(0, 0);
    rectangle.setSize(sf::Vector2f(800, 800));
    rectangle.setTexture(&texture);
    window.draw(rectangle);
    window.display();
}

void MazeRecursiveBacktracker::createMaze() {
    struct Pos {unsigned int x, y, state; std::array<short, 4> order;};
    std::stack<Pos> states;

    Pos pos = {0, 0, 0, randomDirections()};
    states.push(pos);

    while (!states.empty()) {
        auto top = states.top();
        states.pop();

        grid[top.x + top.y * size] = true;
        renderedMaze.setPixel(top.x * 2 + 1, top.y * 2 + 1, sf::Color::Red);

        if(top.state < 3) states.push({top.x, top.y, top.state+1, top.order});

        if(top.order[top.state] == 0 && top.x!=size-1) {
            if (!(grid[(top.x + 1) + top.y * size])) {
                states.push({top.x + 1, top.y, 0, randomDirections()});

                renderedMaze.setPixel((top.x + 1) * 2, top.y * 2 + 1, sf::Color::White);
            }
        }
        if(top.order[top.state] == 1 && top.y!=0) {
            if(!(grid[top.x + (top.y-1) * size])) {
                states.push({top.x, top.y-1, 0, randomDirections()});

                renderedMaze.setPixel(top.x * 2 + 1, top.y * 2, sf::Color::White);
            }
        }
        if(top.order[top.state] == 2 && top.x!=0) {
            if(!(grid[(top.x-1) + top.y * size])) {
                states.push({top.x-1, top.y, 0, randomDirections()});

                renderedMaze.setPixel(top.x * 2, top.y * 2 + 1, sf::Color::White);
            }
        }
        if(top.order[top.state] == 3 && top.y!=size-1) {
            if(!(grid[top.x + (top.y+1) * size])) {
                states.push({top.x, top.y+1, 0, randomDirections()});

                renderedMaze.setPixel(top.x * 2 + 1, (top.y + 1) * 2, sf::Color::White);
            }
        }
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
        renderedMaze.setPixel(top.x * 2 + 1, top.y * 2 + 1, sf::Color::White);
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

std::array<short, 4> MazeRecursiveBacktracker::randomDirections() {
    std::array<short, 4> directions = {0, 1, 2, 3};
    std::random_shuffle(directions.begin(), directions.end());
    return directions;
};


