#pragma once
#include "PieceEnum.h"
#include "global.h"

//Black -> 36, 26, 15
//White -> 238, 220, 151
//Border -> 150, 77, 34
//Tile(B) -> 28, 28, 36
//Tile(W) -> 204, 204, 204

class Piece
{
private:

	pieceType type;

	sf::RectangleShape tile;

public:

	Piece();

};

