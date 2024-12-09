#pragma once
#include "global.h"
#include "Piece.h"
#include "Tile.h"

/**
 * @class PieceManager
 * @brief Creates Pieces for game. Handles, Collisions, Drawing and Placement.
 */
class PieceManager
{
public:
    /**
     * @brief PieceManager constructor.
     * @param beginPos is the initial pos for spawning the pieces on the right side of the screen.
     */
    PieceManager(sf::Vector2f beginPos);

    /**
     * @brief Draw function. Handles drawing board pieces.
     * @param window Pass in the render window.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Places the pieces on the board.
     * @param startPos Gives the initial pos.
     */
    void placePieces(sf::Vector2f startPos);

    /**
     * @brief When a piece is clicked, passes the type to be stored.
     * @param window Render window.
     */
    void onClick(sf::RenderWindow& window);

    /**
     * @brief Stores the type of tile.
     * @param type Takes in the piece's type.
     */
    void clickedPiece(pieceType type);

    /**
     * @brief With a type selected, when the grid is clicked, draws the selected piece on the grid.
     * @param window Takes in the Render window.
     * @param grid Takes in an array of Tile for the grid.
     */
    void onTileClick(sf::RenderWindow& window, std::vector<Tile>& grid);

    /**
    * @brief When a piece is selected itl show a preview of the oiece when youre hovering over the grid
    * @param Window for draw
    * @param grid is an array of class Tile
    */
    void previewPiece(sf::RenderWindow& window, std::vector<Tile>& grid);

    /**
    * @brief Same functionality as previewPiece,only this one is specifically only for the Cathdral piece
    * @param Window for draw
    * @param grid is an array of class Tile
    */
    void previewPieceCathedral(sf::RenderWindow& window, std::vector<Tile>& grid);


    bool canPlacePiece(pieceType type, int tileIndex, std::vector<Tile>& grid);

    void placePiece(pieceType type, int tileIndex, std::vector<Tile>& grid, bool place);

private:

    Piece piece; ///< Piece object
    sf::Vector2f startPos; ///< Start pos for placing pieces
    std::vector<Piece> piecesArray; ///< Array for all pieces on the board

    int pieceCap = 30; ///< Max pieces on the board
    pieceType selectedPiece; ///< Currently selected piece
    Tile tile; ///< Tile object
};