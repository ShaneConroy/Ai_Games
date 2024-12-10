#pragma once

#include "PieceManager.h"
#include "Grid.h"
#include "Piece.h"

class Ai
{
public:
    Ai(PieceManager& pieceManager, Grid& gameGrid);
    void update();

private:

    PieceManager& manager;
    Grid& grid;

    // Take the first piece (biggest first) then place it in every grid tile.
    // Then add wheter its valid or not to a vector array.
    // Return the list
    std::vector<bool> checkPossibleMoves();

    std::vector<bool> placePiece(std::vector<bool>, int);

    void startAi();

    // The minimax function
    int depth = 0;
    int const MAX_DEPTH = 2;
    int minimax(int, bool, std::vector<bool>);
    int miniMaxRuns = 0;
    int evaluateBoard(std::vector<bool>);
};