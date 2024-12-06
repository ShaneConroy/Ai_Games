#include "Grid.h"

Grid::Grid()
{
	constructGrid();
}

void Grid::constructGrid()
{
	for (int tile = 0; tile < MAX_GRID; tile++)
	{
		tileArray.push_back(Tile(tile, GRID_SIZE, TILE_SIZE));
	}
}

void Grid::update(sf::RenderWindow& window, PieceManager& pieceManager)
{
	for (Tile tile : tileArray)
	{
		tile.update();
	}

	pieceManager.onTileClick(window, tileArray);
	pieceManager.previewPiece(window, tileArray);
	pieceManager.previewPieceCathedral(window, tileArray);
}

void Grid::draw(sf::RenderWindow& window)
{
	for (Tile tile : tileArray)
	{
		tile.draw(window);
	}
}