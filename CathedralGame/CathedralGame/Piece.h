#pragma once
#include "PieceEnum.h"
#include "global.h"

class Piece
{
public:

	Piece(int piece = 0, sf::Vector2f pos = sf::Vector2f(0, 0));
	void draw(sf::RenderWindow& window);
	void setMatrix(pieceType);
	pieceType getType() { return type; };
	void setPosition(sf::Vector2f);
	sf::Vector2f getPos() { return piecePos; };
	std::vector<int>pieceMatrix = std::vector<int>(9, 0);

private:

	pieceType type;

	sf::Vector2f piecePos;


	std::vector<sf::RectangleShape> pieceShape;

	// This function will take the piece matrix and generate a shape
	void generatePiece();

};

