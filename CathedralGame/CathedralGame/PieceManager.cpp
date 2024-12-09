#include "PieceManager.h"

PieceManager::PieceManager(sf::Vector2f beginPos) : startPos(beginPos)
{
    placePieces(startPos);
}

// Used for spawning in pieces
void PieceManager::placePieces(sf::Vector2f startPos)
{
    int gridWidth = 3;
    int gridHeight = 3;
    float tileSize = TILE_SIZE;

    for (int iter = 0; iter < PIECE_MAX; iter++)
    {
        int row = iter / gridWidth;
        int col = iter % gridWidth;

        sf::Vector2f piecePos = startPos + sf::Vector2f(col * (tileSize * 3), row * (tileSize * 3));
        Piece temp((iter + 3), piecePos);

        piecesArray.push_back(temp);
    }
}

void PieceManager::onClick(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = { sf::Mouse::getPosition(window) };

    for (Piece& piece : piecesArray)
    {
        sf::Vector2f pieceTopLeft = piece.getPos();
        float pieceWidth = 3 * TILE_SIZE;
        float pieceHeight = 3 * TILE_SIZE;

        if (mousePos.x >= pieceTopLeft.x && mousePos.x <= pieceTopLeft.x + pieceWidth &&
            mousePos.y >= pieceTopLeft.y && mousePos.y <= pieceTopLeft.y + pieceHeight)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                clickedPiece(piece.getType());
            }
        }
    }
}

void PieceManager::clickedPiece(pieceType type)
{
    selectedPiece = type;
}

void PieceManager::onTileClick(sf::RenderWindow& window, std::vector<Tile>& grid)
{
    if (selectedPiece == pieceType{})
    {
        return;
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    bool placeable = true;
    int matrixRows = 3;
    int matrixCols = 3;

    // Check if the selected piece is the Cathedral
    if (selectedPiece == pieceType::cathedral)
    {
        matrixRows = 4;
        matrixCols = 3;
    }

    Piece tempMatrix(static_cast<int>(selectedPiece), sf::Vector2f(0, 0));
    const std::vector<int>& shapeMatrix = tempMatrix.pieceMatrix;

    int matrixCentreRow = matrixRows / 2;
    int matrixCentreCol = matrixCols / 2;

    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i].getRect().getGlobalBounds().contains(worldMousePos))
        {
            int clickedRow = i / GRID_SIZE;
            int clickedCol = i % GRID_SIZE;
            int startRow = clickedRow - matrixCentreRow;
            int startCol = clickedCol - matrixCentreCol;

            // Check if the piece can be placed
            for (int row = 0; row < matrixRows; row++)
            {
                for (int col = 0; col < matrixCols; col++)
                {
                    if (shapeMatrix[row * matrixCols + col] == 1)
                    {
                        int targetRow = startRow + row;
                        int targetCol = startCol + col;
                        int targetIndex = targetRow * GRID_SIZE + targetCol;

                        if (targetRow < 0 || targetRow >= GRID_SIZE ||
                            targetCol < 0 || targetCol >= GRID_SIZE ||
                            grid[targetIndex].checkTaken())
                        {
                            placeable = false;
                            break;
                        }
                    }
                }
                if (!placeable)
                {
                    break;
                }
            }

            // If the piece is placeable and the mouse is clicked
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && placeable)
            {
                if (selectedPiece == pieceType::cathedral)
                {
                    for (int row = 0; row < matrixRows; row++)
                    {
                        for (int col = 0; col < matrixCols; col++)
                        {
                            if (shapeMatrix[row * matrixCols + col] == 1)
                            {
                                int targetRow = startRow + row;
                                int targetCol = startCol + col;
                                int targetIndex = targetRow * GRID_SIZE + targetCol;

                                grid[targetIndex].setColour(sf::Color(238, 220, 151));
                                grid[targetIndex].updateTaken(true);
                            }
                        }
                    }
                }
                else
                {
                    for (int row = 0; row < matrixRows; row++)
                    {
                        for (int col = 0; col < matrixCols; col++)
                        {
                            if (shapeMatrix[row * matrixCols + col] == 1)
                            {
                                int targetRow = startRow + row;
                                int targetCol = startCol + col;
                                int targetIndex = targetRow * GRID_SIZE + targetCol;

                                grid[targetIndex].setColour(sf::Color(238, 220, 151));
                                grid[targetIndex].updateTaken(true);
                            }
                        }
                    }
                }
                selectedPiece = pieceType{};
            }
            break;
        }
    }
}


void PieceManager::previewPiece(sf::RenderWindow& window, std::vector<Tile>& grid)
{
    if (selectedPiece == pieceType{} || selectedPiece == pieceType::cathedral)
        return;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    Piece tempMatrix(static_cast<int>(selectedPiece), sf::Vector2f(0, 0));
    const std::vector<int>& shapeMatrix = tempMatrix.pieceMatrix;
    int matrixSize = 3;

    int matrixCentre = matrixSize / 2;

    // Reset all tiles to their original colors
    for (Tile& tile : grid)
    {
        if (!tile.checkTaken())
        {
            if (tile.getType() == pieceType::bgWhite)
            {
                tile.setColour(sf::Color(204, 204, 204));
            }
            else if (tile.getType() == pieceType::bgBlack)
            {
                tile.setColour(sf::Color(28, 28, 36));
            }
            else if (tile.getType() == pieceType::border)
            {
                tile.setColour(sf::Color(150, 77, 34));
            }
        }
    }

    // Highlight the tiles under the piece being previewed
    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i].getRect().getGlobalBounds().contains(worldMousePos))
        {
            int hoveredRow = i / GRID_SIZE;
            int hoveredCol = i % GRID_SIZE;
            int startRow = hoveredRow - matrixCentre;
            int startCol = hoveredCol - matrixCentre;

            for (int row = 0; row < matrixSize; row++)
            {
                for (int col = 0; col < matrixSize; col++)
                {
                    if (shapeMatrix[row * matrixSize + col] == 1)
                    {
                        int targetRow = startRow + row;
                        int targetCol = startCol + col;
                        int targetIndex = targetRow * GRID_SIZE + targetCol;

                        if (targetRow >= 0 && targetRow < GRID_SIZE &&
                            targetCol >= 0 && targetCol < GRID_SIZE &&
                            !grid[targetIndex].checkTaken())
                        {
                            grid[targetIndex].setColour(sf::Color(123, 166, 230));
                        }

                    }
                }
            }
            break;
        }
    }
}

void PieceManager::previewPieceCathedral(sf::RenderWindow& window, std::vector<Tile>& grid)
{
    if (selectedPiece != pieceType::cathedral)
        return;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    Piece tempMatrix(static_cast<int>(pieceType::cathedral), sf::Vector2f(0, 0));
    const std::vector<int>& shapeMatrix = tempMatrix.pieceMatrix;

    int matrixRows = 4;
    int matrixCols = 3;
    int matrixCentreRow = matrixRows / 2;
    int matrixCentreCol = matrixCols / 2;

    for (Tile& tile : grid)
    {
        if (!tile.checkTaken())
        {
            if (tile.getType() == pieceType::bgWhite)
            {
                tile.setColour(sf::Color(204, 204, 204));
            }
            else if (tile.getType() == pieceType::bgBlack)
            {
                tile.setColour(sf::Color(28, 28, 36));
            }
            else if (tile.getType() == pieceType::border)
            {
                tile.setColour(sf::Color(150, 77, 34));
            }
        }
    }

    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i].getRect().getGlobalBounds().contains(worldMousePos))
        {
            int hoveredRow = i / GRID_SIZE;
            int hoveredCol = i % GRID_SIZE;

            int startRow = hoveredRow - matrixCentreRow;
            int startCol = hoveredCol - matrixCentreCol;

            for (int row = 0; row < matrixRows; row++)
            {
                for (int col = 0; col < matrixCols; col++)
                {
                    if (shapeMatrix[row * matrixCols + col] == 1)
                    {
                        int targetRow = startRow + row;
                        int targetCol = startCol + col;
                        int targetIndex = targetRow * GRID_SIZE + targetCol;

                        if (targetRow >= 0 && targetRow < GRID_SIZE &&
                            targetCol >= 0 && targetCol < GRID_SIZE &&
                            !grid[targetIndex].checkTaken())
                        {
                            grid[targetIndex].setColour(sf::Color(123, 166, 230));
                        }
                    }
                }
            }
            break;
        }
    }
}

bool PieceManager::canPlacePiece(pieceType type, int tileIndex, std::vector<Tile>& grid)
{
    int matrixRows = 3;
    int matrixCols = 3;

    Piece tempMatrix(static_cast<int>(type), sf::Vector2f(0, 0));
    const std::vector<int>& shapeMatrix = tempMatrix.pieceMatrix;

    int matrixCentreRow = matrixRows / 2;
    int matrixCentreCol = matrixCols / 2;

    int clickedRow = tileIndex / GRID_SIZE;
    int clickedCol = tileIndex % GRID_SIZE;
    int startRow = clickedRow - matrixCentreRow;
    int startCol = clickedCol - matrixCentreCol;

    for (int row = 0; row < matrixRows; ++row)
    {
        for (int col = 0; col < matrixCols; ++col)
        {
            if (shapeMatrix[row * matrixCols + col] == 1)
            {
                int targetRow = startRow + row;
                int targetCol = startCol + col;
                int targetIndex = targetRow * GRID_SIZE + targetCol;

                if (targetRow < 0 || targetRow >= GRID_SIZE ||
                    targetCol < 0 || targetCol >= GRID_SIZE ||
                    grid[targetIndex].checkTaken())
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void PieceManager::placePiece(pieceType type, int tileIndex, std::vector<Tile>& grid, bool place)
{
    int matrixRows = 3;
    int matrixCols = 3;

    if (type == pieceType::cathedral)
    {
        matrixRows = 4;
        matrixCols = 3;
    }

    Piece tempMatrix(static_cast<int>(type), sf::Vector2f(0, 0));
    const std::vector<int>& shapeMatrix = tempMatrix.pieceMatrix;

    int matrixCentreRow = matrixRows / 2;
    int matrixCentreCol = matrixCols / 2;

    int clickedRow = tileIndex / GRID_SIZE;
    int clickedCol = tileIndex % GRID_SIZE;
    int startRow = clickedRow - matrixCentreRow;
    int startCol = clickedCol - matrixCentreCol;

    for (int row = 0; row < matrixRows; ++row)
    {
        for (int col = 0; col < matrixCols; ++col)
        {
            if (shapeMatrix[row * matrixCols + col] == 1)
            {
                int targetRow = startRow + row;
                int targetCol = startCol + col;
                int targetIndex = targetRow * GRID_SIZE + targetCol;

                if (targetRow >= 0 && targetRow < GRID_SIZE &&
                    targetCol >= 0 && targetCol < GRID_SIZE)
                {
                    grid[targetIndex].updateTaken(place);
                    grid[targetIndex].setColour(place ? sf::Color(238, 220, 151) : sf::Color(204, 204, 204));
                }
            }
        }
    }
}



void PieceManager::draw(sf::RenderWindow& window)
{
    for (Piece& piece : piecesArray)
    {
        piece.draw(window);
    }
}