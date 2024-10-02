#include "globals.h"
#include "player.h"
#include "npc.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Project");

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	player playerOBJ;
	npc npcOBJ;


	while (window.isOpen())
	{
		sf::Event event;  
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
		}

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			window.clear();
			playerOBJ.Update(window);
			playerOBJ.Draw(window);

			npcOBJ.Update(window);
			npcOBJ.Draw(window);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}


	}
}