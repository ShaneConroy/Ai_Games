#include "Ai.h"


Ai::Ai(PieceManager& pieceManager, Grid& gameGrid)
    : manager(pieceManager), grid(gameGrid)
{
}

void Ai::update()
{
    if (manager.startAi)
    {
        startAi();
    }
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
            continue;
        }
        arrayOfValidTiles.push_back(canPlacePiece);
	}

    return arrayOfValidTiles;
}

std::vector<bool> Ai::placePiece(std::vector<bool> arrayOfValidTiles, int cellNum)
{
    Piece tempMatrix(static_cast<int>(pieceType::tower), sf::Vector2f(0, 0));
    const std::vector<int>& shapeMatrix = tempMatrix.pieceMatrix;

    int startRow = cellNum - 3;
    int startCol = cellNum - 3;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (shapeMatrix[row * 3 + col] == 1)
            {
                int targetRow = startRow + row;
                int targetCol = startCol + col;

                if (targetRow >= 0 && targetRow < GRID_SIZE && targetCol >= 0 && targetCol < GRID_SIZE)
                {
                    int targetIndex = targetRow * GRID_SIZE + targetCol;

                    if (!arrayOfValidTiles[targetIndex] && shapeMatrix[row * 3 + col] == 1)
                    {
                        arrayOfValidTiles[targetIndex] = true;
                    }
                }
            }
        }
    }

    return arrayOfValidTiles;
}


void Ai::startAi()
{
    std::cout << "startAi()" << "\n";
    std::vector<bool> currentGridState;

    for (Tile tile : grid.returnTileArray())
    {
        currentGridState.push_back(tile.checkTaken());
    }

    int depth = 0;
    bool maximising = true;

    int bestScore = INT_MIN;
    int bestMove = -1;

    for (int i = 0; i < currentGridState.size(); ++i)
    {
        if (!currentGridState[i])
        {
            std::vector<bool> newGridState = placePiece(currentGridState, i);

            int score = minimax(depth, !maximising, newGridState);

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    if (bestMove != -1)
    {
        placePiece(currentGridState, bestMove);
        manager.startAi = false;
    }
    std::cout << miniMaxRuns << "\n";
    std::cout << "BEST MOVE: " << bestMove << "\n";
}


int Ai::minimax(int depth, bool maximising, std::vector<bool> modifiedGrid)
{
    if (depth == MAX_DEPTH)
    {
        return evaluateBoard(modifiedGrid);
    }
    
    miniMaxRuns += 1;

    if (maximising)
    {
        int maxEva = INT_MIN;

        for (int iter = 0; iter < modifiedGrid.size(); iter++)
        {
            if (!modifiedGrid[iter])
            {
                std::vector<bool> newTileArray = placePiece(modifiedGrid, iter);
                maxEva = std::max(maxEva, minimax(depth + 1, !maximising, newTileArray));
            }
        }
        return maxEva;
    }
    else {

        int minEva = INT_MAX;

        for (int iter = 0; iter < modifiedGrid.size(); iter++)
        {
            if (!modifiedGrid[iter])
            {
                std::vector<bool> newTileArray = placePiece(modifiedGrid, iter);
                minEva = std::min(minEva, minimax(depth + 1, maximising, newTileArray));
            }
        }
        return minEva;
    }
}

int Ai::evaluateBoard(std::vector<bool> newTileArray)
{
    int score = 0;

    int gridSize = static_cast<int>(sqrt(newTileArray.size()));
    int centerRow = gridSize / 2;
    int centerCol = gridSize / 2;

    for (int index = 0; index < newTileArray.size(); ++index)
    {
        if (newTileArray[index])
        {
            int row = index / gridSize;
            int col = index % gridSize;

            int distanceFromCenter = abs(row - centerRow) + abs(col - centerCol);
            int proximityScore = gridSize - distanceFromCenter;

            score += proximityScore;
        }
    }

    return score;
}


