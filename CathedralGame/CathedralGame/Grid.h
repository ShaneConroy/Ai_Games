#pragma once
#include "global.h"
#include "Tile.h"
#include "PieceManager.h"

class Grid
{
private:
	
	std::vector<Tile> tileArray;

	void constructGrid();

public:

	Grid();

	void draw(sf::RenderWindow& window);
	void update(sf::RenderWindow& window, PieceManager& pieceManager);


};

