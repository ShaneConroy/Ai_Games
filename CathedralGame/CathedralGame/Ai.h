#pragma once

#include "PieceManager.h"
#include "Grid.h"
#include "Piece.h"
#include <vector>
#include <climits>

class Ai
{
public:
    Ai(PieceManager& pieceManager, Grid& grid);

private:

    PieceManager& manager;
    Grid& grid;

};
