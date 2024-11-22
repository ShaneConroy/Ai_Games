#pragma once
#include "Global.h"

class Grid
{
private:
	Global global;

	int const SQUARE_SIZE = 15;
	int const GRID_SIZE = 50;
	int coluorChangeTimer = 0;
	int greenCount, redCount;
	int gridButtonTimer = 0;
	std::vector<sf::RectangleShape> gridArray;
	std::vector<sf::Text> textArray;
	std::vector<int> weightArray;
	sf::Vector3f red = {249, 68, 73};
	sf::Vector2f redSquarePos = { -1, -1 };
	int posRedSquare = 0;
	int posGreenSquare = 0;
	sf::Color calculateHeatMap(int);
	void changeGridColour(int, sf::RectangleShape&);
	void gridCostFunction();
	int checkGreenCount();
	int checkRedCount();
	void heatMapFunction();
	sf::Font weightFont;
	bool gridOn;
	void flowfield();
	std::vector<sf::RectangleShape> flowFieldArray;
	bool flowOn = false;
	int flowButtonTimer = 0;
	bool heatOn;
	int heatButtonTimer = 0;
	std::vector<sf::Vector2f> path2f;
	void integrationField();
	int cellCost[2500];
	std::vector<int> pathway;

public:

	void constructGrid();
	void gridFunction(sf::Vector2i);
	void draw(sf::RenderWindow &window);
	void makePathway();

};

