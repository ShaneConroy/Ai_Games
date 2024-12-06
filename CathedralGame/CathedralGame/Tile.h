#pragma once
#include "global.h"
#include "PieceEnum.h"
#include "PieceTeam.h"

class Tile
{
private:
    pieceType type;
    team team;

    void behaviours(pieceType);

    int tileIndex;
    int gridSize;
    int tileSize;

    bool taken = false;

    sf::RectangleShape tile;

public:
    Tile();
    Tile(int iter, int gridSize, int tileSize);

    void draw(sf::RenderWindow& window);
    void update();

    sf::RectangleShape getRect() const { return tile; }
    void setColour(sf::Color colour);

    pieceType getType() { return type; };
    sf::Color getColour() { return tile.getFillColor(); };
    bool checkTaken() { return taken; };
    void updateTaken(bool temp) { taken = temp; };
};