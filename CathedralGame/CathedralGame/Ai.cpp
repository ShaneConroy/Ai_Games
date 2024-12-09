#include "Ai.h"

Ai::Ai(PieceManager& pieceManager, Grid& grid)
	: manager(pieceManager), grid(grid)
{
}

std::vector<bool> Ai::checkPossibleMoves()
{
    std::vector<bool> arrayOfValidTiles;
    Piece tempMatrix(static_cast<int>(pieceType::tower), sf::Vector2f(0, 0));
    const std::vector<int>& shapeMatrix = tempMatrix.pieceMatrix;

    int matrixSize = 3;

    for (int tileIndex = 0; tileIndex < grid.returnTileArray().size(); tileIndex++)
    {
        bool canPlacePiece = true;

        for (int row = 0; row < matrixSize; row++)
        {
            for (int col = 0; col < matrixSize; col++)
            {
                if (shapeMatrix[row * matrixSize + col] == 1)
                {
                    int targetTileIndex = tileIndex + row * GRID_SIZE + col;

                    if (targetTileIndex >= grid.returnTileArray().size() || grid.returnTileArray()[targetTileIndex].checkTaken())
                    {
                        canPlacePiece = false;
                        break;
                    }
                }
            }
        }
        if (canPlacePiece == false)
        {
            break;
        }
        arrayOfValidTiles.push_back(canPlacePiece);
	}

    return arrayOfValidTiles;
}

void Ai::evaluateMoves(std::vector<bool> tileValidArray)
{

}


int Ai::minimax(int depth, bool maximising)
{
    std::vector<bool> arrayOfValidTiles = checkPossibleMoves();

    if (maximising)
    {
        int maxInt = INT_MIN; // for max evaluation
        for (int iter = 0; iter < arrayOfValidTiles.size(); iter++)
        {
            if (arrayOfValidTiles[iter])
            {
                if (manager.canPlacePiece(pieceType::tower, iter, grid.returnTileArray()))
                {
                    manager.placePiece(pieceType::tower, iter, grid.returnTileArray(), true);

                    int eval = minimax(depth - 1, false);

                    manager.placePiece(pieceType::tower, iter, grid.returnTileArray(), false);

                    maxInt = std::max(maxInt, eval);
                }
            }
        }
        return maxInt;
    }
    else { // Minimising

        int minInt = INT_MAX;

        for (int iter = 0; iter < arrayOfValidTiles.size(); iter++)
        {
            if (arrayOfValidTiles[iter])
            {
                if (manager.canPlacePiece(pieceType::tower, iter, grid.returnTileArray()))
                {
                    manager.placePiece(pieceType::tower, iter, grid.returnTileArray(), true);

                    int eval = minimax(depth - 1, true);

                    manager.placePiece(pieceType::tower, iter, grid.returnTileArray(), false);

                    minInt = std::min(minInt, eval);
                }
            }
        }
        return minInt;
    }
}

int Ai::evaluateBoard()
{
    return 0;
}
