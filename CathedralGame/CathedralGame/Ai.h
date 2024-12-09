#pragma once

#include "PieceManager.h"
#include "Grid.h"
#include "Piece.h"

class Ai
{
public:
    Ai(PieceManager& pieceManager, Grid& grid);

private:

    PieceManager& manager;
    Grid& grid;

    // Take the first piece (biggest first) then place it in every grid tile.
    // Then add wheter its valid or not to a vector array.
    // Return the list
    std::vector<bool> checkPossibleMoves();

    // takes in the vector of bools and evaluates them
    void evaluateMoves(std::vector<bool>);

    // The minimax function
    int depth = 1;
    int minimax(int, bool);

    int evaluateBoard();
};