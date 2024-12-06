#include "Tile.h"

// Default constrcutor
Tile::Tile()
    : tileIndex(0), gridSize(1), tileSize(1), tile(sf::Vector2f(1, 1))
{
    type = pieceType::bgWhite;
    tile.setPosition(0, 0);
    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(1);
    behaviours(type);
}

Tile::Tile(int iter, int gridSize, int tileSize)
    : tileIndex(iter), gridSize(gridSize), tileSize(tileSize), tile(sf::Vector2f(tileSize, tileSize))
{
    float xPos = ((tileIndex % gridSize) * tileSize) + 50;
    float yPos = ((tileIndex / gridSize) * tileSize) + 50;

    type = pieceType::bgWhite;

    tile.setPosition(xPos, yPos);
    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(1);

    if (tileIndex < gridSize || tileIndex >= (gridSize * (gridSize - 1)) ||
        tileIndex % gridSize == 0 || tileIndex % gridSize == gridSize - 1)
    {
        type = pieceType::border;
    }
    else if ((tileIndex + (tileIndex / gridSize)) % 2 == 0)
    {
        type = pieceType::bgBlack;
    }

    behaviours(type);
}

void Tile::behaviours(pieceType)
{
    if (type == pieceType::bgWhite)
    {
        tile.setFillColor(sf::Color(204, 204, 204));
    }
    else if (type == pieceType::bgBlack)
    {
        tile.setFillColor(sf::Color(28, 28, 36));
    }
    else if (type == pieceType::border)
    {
        tile.setFillColor(sf::Color(150, 77, 34));
        taken = true;
    }
}

void Tile::draw(sf::RenderWindow& window)
{
    window.draw(tile);
}

void Tile::update()
{
    behaviours(type);
}

void Tile::setColour(sf::Color colour)
{
    tile.setFillColor(colour);
}
