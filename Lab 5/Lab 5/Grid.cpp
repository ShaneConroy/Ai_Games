#include "Grid.h"

// Constructs a 50x50 grid of sf::RectangleShapes
void Grid::constructGrid()
{
	for (int y = 1; y < GRID_SIZE + 1; y++)
	{
		for (int x = 1; x < GRID_SIZE + 1; x++)
		{
			// Set up square
			sf::RectangleShape grid;
			grid.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
			grid.setOutlineColor(sf::Color::Black);
			grid.setFillColor(sf::Color(245, 202, 123));
			grid.setOutlineThickness(1.0f);

			// Get its pos in grid & assign
			sf::Vector2i newPos;
			newPos.y = SQUARE_SIZE * y;
			newPos.x = SQUARE_SIZE * x;
			grid.setPosition(newPos.x, newPos.y);

			// Add to array
			gridArray.push_back(grid);
		}
	}

	// Sets up text for grid
	weightFont.loadFromFile("FONTS/BebasNeue.otf");
	weightArray.resize(GRID_SIZE * GRID_SIZE, 0);

	textArray.resize(GRID_SIZE * GRID_SIZE, sf::Text());
	for (auto& text : textArray) {
		text.setFont(weightFont);
		text.setCharacterSize(10);
	}
}

// Updates grid based on player input
void Grid::gridFunction(sf::Vector2i mousePos)
{
	if(coluorChangeTimer > 0)
		coluorChangeTimer -= 1;
	if (gridButtonTimer > 0)
		gridButtonTimer -= 1;
	if (flowButtonTimer > 0)
		flowButtonTimer -= 1;
	if (heatButtonTimer > 0)
		heatButtonTimer -= 1;

	// Check if mouse Pos is inside grid, left click calls changeGridColour
	for (int iter = 0; iter < gridArray.size(); iter++)
	{
		if (mousePos.x >= gridArray[iter].getPosition().x &&
			mousePos.x <= gridArray[iter].getPosition().x + gridArray[iter].getGlobalBounds().width &&
			mousePos.y >= gridArray[iter].getPosition().y &&
			mousePos.y <= gridArray[iter].getPosition().y + gridArray[iter].getGlobalBounds().height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (coluorChangeTimer == 0) // only go when timer depleted
				{
					if (checkGreenCount() == 0)
					{
						changeGridColour(1, gridArray[iter]);
						posGreenSquare = iter;
					}
					else if (gridArray[iter].getFillColor() == sf::Color(125, 200, 132)) // to red
					{
						if (checkRedCount() == 0)
						{
							changeGridColour(2, gridArray[iter]);
							redSquarePos = sf::Vector2f(iter % GRID_SIZE, iter / GRID_SIZE);
							posRedSquare = iter;

						}
					}
					else if (gridArray[iter].getFillColor() == sf::Color(249, 68, 73)) // to orange
					{
						changeGridColour(3, gridArray[iter]);
						redSquarePos = sf::Vector2f(-1, -1);
					}
					coluorChangeTimer = 10; // reset timer
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Mouse::isButtonPressed(sf::Mouse::Right)) // Black walls
			{
				changeGridColour(4, gridArray[iter]);
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) // Erase
			{
				changeGridColour(3, gridArray[iter]);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && gridButtonTimer == 0) // Turn off and on the grid
			{
				if (!gridOn)
				{
					integrationField();
					gridCostFunction();
					gridOn = true;
				}
				else if (gridOn)
				{
					for (auto& text : textArray)
					{
						text.setString(" "); // Clear the text
					}
					gridOn = false;
				}
				gridButtonTimer = 10;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && flowButtonTimer == 0) // Turn off and on the grid
			{
				if (!flowOn)
				{
					flowfield();
					makePathway();
					flowOn = true;
				}
				else if (flowOn)
				{
					flowFieldArray.clear();
					for (int iter = 0; iter < gridArray.size(); iter++)
					{
						if (gridArray[iter].getFillColor() == sf::Color::Blue)
						{
							gridArray[iter].setFillColor(sf::Color(245, 202, 123));
						}
					}
					flowOn = false;
				}
				flowButtonTimer = 10;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && heatButtonTimer == 0) // Turn off and on the grid
			{
				if (!heatOn)
				{
					heatMapFunction();
					heatOn = true;
				}
				else if (heatOn)
				{
					heatOn = false;
					for (auto& cell : gridArray)
					{
						// Reverts heat map, but doesnt change other grid blocks
						if (cell.getFillColor() != sf::Color(125, 200, 132) &&
							cell.getFillColor() != sf::Color(249, 68, 73) &&
							cell.getFillColor() != sf::Color(245, 202, 123) &&
							cell.getFillColor() != sf::Color(25, 25, 25) &&
							cell.getFillColor() != sf::Color::Blue)
						{
							changeGridColour(3, cell);
						}
					}
				}
				heatButtonTimer = 10;
			}
		}
	}
}

void Grid::integrationField()
{
	pathway.clear();
	pathway.resize(GRID_SIZE * GRID_SIZE, -1);

	for (int iter = 0; iter < 2500; iter++)
	{
		cellCost[iter] = INT_MAX - 1;
	}

	std::queue<int> unvisitedQueue; // grids to visit
	unvisitedQueue.push(posRedSquare);
	cellCost[posRedSquare] = 0;


	while (!unvisitedQueue.empty())
	{
		int currentGrid = unvisitedQueue.front();
		unvisitedQueue.pop();

		int currentGridX = (currentGrid % GRID_SIZE);
		int currentGridY = (currentGrid / GRID_SIZE);

		int currentCost = cellCost[currentGrid];


		// Loop through current grids neighbours
		for (int offsetY = -1; offsetY <= 1; offsetY++)
		{
			for (int offsetX = -1; offsetX <= 1; offsetX++)
			{
				if (offsetX == 0 && offsetY == 0) continue; // Skip self

				int neighbourIndex = currentGrid + offsetX + (offsetY * GRID_SIZE);

				if (neighbourIndex >= 0 && neighbourIndex < GRID_SIZE * GRID_SIZE)
				{

					if (gridArray[neighbourIndex].getFillColor() == sf::Color(25, 25, 25) || cellCost[neighbourIndex] == INT_MAX)
					{
						continue;
					}
					else if (cellCost[neighbourIndex] > currentCost + SQUARE_SIZE) // If the neighbour im looking at is expsensiver than me
					{
						if (offsetX == 0 && offsetY == 0)
							continue;
						
						else if (offsetX == 0 || offsetY == 0) // If its cardinal
						{
							cellCost[neighbourIndex] = currentCost + SQUARE_SIZE;
							unvisitedQueue.push(neighbourIndex);
							pathway[neighbourIndex] = currentGrid;
						}
						// Else its diagonal
						else {
							cellCost[neighbourIndex] = currentCost + (SQUARE_SIZE * 1.5);
							unvisitedQueue.push(neighbourIndex);
							pathway[neighbourIndex] = currentGrid;
						}
					}
				}
			}
		}
	}
}

// Changes colour of grid passed in
void Grid::changeGridColour(int switcher, sf::RectangleShape& grid)
{
	switch (switcher)
	{
	case 1:
		grid.setFillColor(sf::Color(125, 200, 132)); // green
		break;
	case 2:
		grid.setFillColor(sf::Color(249, 68, 73)); // red 
		break;
	case 3:
		grid.setFillColor(sf::Color(245, 202, 123)); // orange
		break;
	case 4:
		grid.setFillColor(sf::Color(25, 25, 25)); // black
		break;
	default:
		break;
	}
}

// Counts all green squares in the grid
int Grid::checkGreenCount()
{
	greenCount = 0;
	for (const auto& grid : gridArray)
	{
		if (grid.getFillColor() == sf::Color(125, 200, 132))
		{
			greenCount += 1;
		}
	}
	return greenCount;
}

// Counts all red squares in the grid
int Grid::checkRedCount()
{
	redCount = 0;
	for (const auto& grid : gridArray)
	{
		if (grid.getFillColor() == sf::Color(249, 68, 73))
		{
			redCount += 1;
		}
	}
	return redCount;
}

// Returns intensity for heat map
sf::Color Grid::calculateHeatMap(int distance)
{
	int intensity = std::max(0, 255 - distance * 5);
	return sf::Color(255, intensity, intensity);
}

// Colours grid based on distance from end goal
void Grid::heatMapFunction()
{
	for (int i = 0; i < gridArray.size(); i++)
	{
		if (gridArray[i].getFillColor() == sf::Color(245, 202, 123))
		{
			sf::Vector2i gridPos(i % GRID_SIZE, i / GRID_SIZE);
			int distance = abs(gridPos.x - redSquarePos.x) + abs(gridPos.y - redSquarePos.y);
			gridArray[i].setFillColor(calculateHeatMap(distance));
		}
	}
}

// Places an arrow in each cell, poitning to the cheapest neighbour
void Grid::flowfield()
{
	for (int row = 0; row < GRID_SIZE; row++)
	{
		for (int col = 0; col < GRID_SIZE; col++)
		{
			int currentIndex = row * GRID_SIZE + col;
			int currentLowest = INT_MAX;
			sf::Vector2f direction;
			sf::Vector2f bestNeighbour(-1, -1);

			for (int offsetY = -1; offsetY <= 1; offsetY++)
			{
				for (int offsetX = -1; offsetX <= 1; offsetX++)
				{
					if (offsetX == 0 && offsetY == 0) continue; // Skip self

					int rowNeighbour = row + offsetY;
					int colNeighbour = col + offsetX;

					// Boundary check
					if (rowNeighbour >= 0 && rowNeighbour < GRID_SIZE &&
						colNeighbour >= 0 && colNeighbour < GRID_SIZE)
					{
						int currentNeighbour = rowNeighbour * GRID_SIZE + colNeighbour;
						float neighbourWeight = cellCost[currentNeighbour];

						if (neighbourWeight < currentLowest)
						{
							currentLowest = neighbourWeight;
							pathway.push_back(currentLowest);
							direction = sf::Vector2f(offsetX, offsetY);
							

						}
					}
				}
			}			

			sf::RectangleShape arrow;
			arrow.setSize(sf::Vector2f(10.0f, 2.0f));
			arrow.setOrigin(5.0f, 1.0f);
			arrow.setPosition(gridArray[currentIndex].getPosition().x + SQUARE_SIZE / 2, gridArray[currentIndex].getPosition().y + SQUARE_SIZE / 2);
			float angle = atan2(direction.y, direction.x) * 180 / 3.14159f;
			arrow.setRotation(angle);
			arrow.setFillColor(sf::Color::Black);

			flowFieldArray.push_back(arrow);
		}
	}
}

// Draws the quickest path from the start to the end goal
void Grid::makePathway()
{

	if (posGreenSquare == -1 || posRedSquare == -1)
	{
		return;
	}

	int currentCell = pathway[posGreenSquare];

	while (currentCell != posRedSquare && currentCell != -1)
	{
		gridArray[currentCell].setFillColor(sf::Color::Blue); // Bluw
		currentCell = pathway[currentCell];
	}
}


// Gets the cost of the grid based on distance from th end goal
// Puts weight into text array
void Grid::gridCostFunction()
{
	// If the start and finish aren't placed, don't continue
	if (checkGreenCount() == 0 || checkRedCount() == 0)
	{
		return;
	}

	int endX = (posRedSquare % GRID_SIZE);
	int endY = (posRedSquare / GRID_SIZE);

	for (int iter = 0; iter < 2500; iter++)
	{
		weightArray[iter] = static_cast<int>(cellCost[iter]); // convert weight to int
		textArray[iter].setString(std::to_string(weightArray[iter]));
		textArray[iter].setPosition(gridArray[iter].getPosition());
	}

	for (int row = 0; row < GRID_SIZE; row++)
	{
		for (int col = 0; col < GRID_SIZE; col++)
		{
			int currentGrid = (row * GRID_SIZE) + col;

			// Calculates weight of each tile based off distance away from end

			float weight = std::sqrt(std::pow(endX - col, 2) + std::pow(endY - row, 2));

			if (col == endY && row == endX)
			{
				weightArray[currentGrid] = 0;
				textArray[currentGrid].setString("0");
			}
			else if (gridArray[currentGrid].getFillColor() == sf::Color(25, 25, 25)) // if it's a wall
			{
				weightArray[currentGrid] = INT_MAX; // value too high, always go around
				textArray[currentGrid].setString("X");
				textArray[currentGrid].setPosition(gridArray[currentGrid].getPosition());
			}
		}
	}
}


void Grid::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < gridArray.size(); i++)
	{
		window.draw(gridArray[i]);
	}

	for (int i = 0; i < textArray.size(); i++)
	{
		window.draw(textArray[i]);
	}

	for (const auto& arrow : flowFieldArray)
	{
		window.draw(arrow);
	}

}
