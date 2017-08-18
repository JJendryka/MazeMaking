#pragma once

#include <vector>
#include <bitset>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class MazePrim {
public:
    MazePrim(unsigned int size, unsigned short difficulty);
    void createMaze();

private:

    unsigned int size;
    unsigned short difficulty;

    std::vector<short> grid;

    sf::RenderWindow window;
    sf::Image renderedMaze;
    sf::Texture texture;
    sf::RectangleShape rectangle;
};