#pragma once
#include "global.h"
#include "Piece.h"

class Grid
{
private:

	int const ROWS = 10;
	int const COLS = 10;
	std::vector<Piece> grid;

	void constructGrid();

public:

	Grid();

	void draw(sf::RenderWindow& window);
	void update();

};

