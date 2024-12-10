#include "Piece.h"

Piece::Piece(int piece, sf::Vector2f pos, team tileTeam) : piecePos(pos)
{
    type = static_cast<pieceType>(piece);

    tileTeam = team::white;

    setMatrix(type);

    generatePiece();
}

void Piece::setMatrix(pieceType type)
{
    switch (type)
    {
    case pieceType::tavern:
        pieceMatrix = { 1, 0, 0,
                        0, 0, 0,
                        0, 0, 0 };
        break;

    case pieceType::stable:
        pieceMatrix = { 1, 0, 0,
                        1, 0, 0,
                        0, 0, 0 };
        break;

    case pieceType::inn:
        pieceMatrix = { 1, 0, 0,
                        1, 1, 0,
                        0, 0, 0 };
        break;

    case pieceType::bridge:
        pieceMatrix = { 0, 1, 0,
                        0, 1, 0,
                        0, 1, 0 };
        break;

    case pieceType::square:
        pieceMatrix = { 1, 1, 0,
                        1, 1, 0,
                        0, 0, 0 };
        break;

    case pieceType::manor:
        pieceMatrix = { 0, 1, 0,
                        1, 1, 1,
                        0, 0, 0 };
        break;

    case pieceType::castle:
        pieceMatrix = { 1, 0, 1,
                        1, 1, 1,
                        0, 0, 0 };
        break;

    case pieceType::tower:
        pieceMatrix = { 0, 0, 1,
                        0, 1, 1,
                        1, 1, 0 };
        break;

    case pieceType::abbey:
        pieceMatrix = { 1, 0, 0,
                        1, 1, 0,
                        0, 1, 0 };
        break;

    case pieceType::academy:
        pieceMatrix = { 0, 1, 0,
                        1, 1, 0,
                        0, 1, 1 };
        break;

    case pieceType::infirmary:
        pieceMatrix = { 0, 1, 0,
                        1, 1, 1,
                        0, 1, 0 };
        break;

    case pieceType::cathedral:
        pieceMatrix = { 0, 1, 0,
                        1, 1, 1,
                        0, 1, 0,
                        0, 1, 0 };
        break;
    }
}

void Piece::setPosition(sf::Vector2f pos)
{
    for (size_t i = 0; i < pieceShape.size(); i++)
    {
        sf::Vector2f offset = pieceShape[i].getPosition() - piecePos;
        pieceShape[i].setPosition(pos);
    }
}

void Piece::generatePiece()
{
    pieceShape.clear();
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (pieceMatrix.size() == 12) // The cathedral piece
            {
                for (int row = 0; row < 4; row++)
                {
                    for (int col = 0; col < 3; col++)
                    {
                        if (pieceMatrix[row * 3 + col] == 1)
                        {
                            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
                            shape.setPosition(piecePos + sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));

                            shape.setFillColor(sf::Color(212, 212, 212));
                            shape.setOutlineColor(sf::Color::Black);
                            shape.setOutlineThickness(2);

                            pieceShape.push_back(shape);
                        }
                    }
                }
            }
            if (pieceMatrix[row * 3 + col] == 1)
            {
                sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
                shape.setPosition(piecePos + sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));

                shape.setFillColor(sf::Color(238, 220, 151));
                shape.setOutlineColor(sf::Color::Black);
                shape.setOutlineThickness(2);

                pieceShape.push_back(shape);
            }
        }
    }
}

void Piece::draw(sf::RenderWindow& window)
{
    for (size_t iter = 0; iter < pieceShape.size(); iter++)
    {
        window.draw(pieceShape[iter]);
    }
}