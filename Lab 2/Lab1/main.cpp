#include "globals.h"
#include "player.h"
#include "npc.h"
#include "behavioursEnum.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML Project");

	srand(time(NULL));

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	player playerOBJ;
	npc npcSeek(behaviourType::seek);
	npc npcWander(behaviourType::wander);
	npc npcPursue(behaviourType::pursue);
	npc npcArrive(behaviourType::arrive);
	npc npcFlee(behaviourType::flee);

	bool seekOn = false;
	bool wanderOn = false;
	bool pursueOn = false;
	bool arriveOn = false;
	bool fleeOn = false;

	int buttonTimer = 10;


	while (window.isOpen())
	{
		sf::Event event;  
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			window.clear();
			playerOBJ.Update(window);
			playerOBJ.Draw(window);

			if (buttonTimer > 0)
			{
				buttonTimer--;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && buttonTimer == 0)
			{
				if (seekOn)
				{
					seekOn = false;
				}
				else if(!seekOn)
				{
					seekOn = true;
				}
				buttonTimer = 10;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && buttonTimer == 0)
			{
				if (wanderOn)
				{
					wanderOn = false;
				}
				else if (!wanderOn)
				{
					wanderOn = true;
				}
				buttonTimer = 10;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && buttonTimer == 0)
			{
				if (pursueOn)
				{
					pursueOn = false;
				}
				else if (!pursueOn)
				{
					pursueOn = true;
				}
				buttonTimer = 10;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && buttonTimer == 0)
			{
				if (arriveOn)
				{
					arriveOn = false;
				}
				else if (!arriveOn)
				{
					arriveOn = true;
				}
				buttonTimer = 10;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && buttonTimer == 0)
			{
				if (fleeOn)
				{
					fleeOn = false;
				}
				else if (!fleeOn)
				{
					fleeOn = true;
				}
				buttonTimer = 10;
			}

			if (seekOn)
			{
				npcSeek.Update(window, playerOBJ.getPlayerPos(), playerOBJ.getPlayerVelocity(), playerOBJ.getPlayerRotation());
				if (playerOBJ.updateCOV(npcSeek.getSprite()))
				{
					playerOBJ.COV.setFillColor(sf::Color(221, 51, 47, 45));
				}	
				else {
					playerOBJ.COV.setFillColor(sf::Color(141, 245, 71, 45));
				}
				npcSeek.Draw(window);
			}
			if (wanderOn)
			{
				npcWander.Update(window, playerOBJ.getPlayerPos(), playerOBJ.getPlayerVelocity(), playerOBJ.getPlayerRotation());
				if (playerOBJ.updateCOV(npcWander.getSprite()))
				{
					playerOBJ.COV.setFillColor(sf::Color(221, 51, 47, 45));
				}
				else {
					playerOBJ.COV.setFillColor(sf::Color(141, 245, 71, 45));
				}
				npcWander.Draw(window);
			}
			if (pursueOn)
			{
				npcPursue.Update(window, playerOBJ.getPlayerPos(), playerOBJ.getPlayerVelocity(), playerOBJ.getPlayerRotation());
				if (playerOBJ.updateCOV(npcPursue.getSprite()))
				{
					playerOBJ.COV.setFillColor(sf::Color(221, 51, 47, 45));
				}
				else {
					playerOBJ.COV.setFillColor(sf::Color(141, 245, 71, 45));
				}
				npcPursue.Draw(window);
			}
			if (arriveOn)
			{
				npcArrive.Update(window, playerOBJ.getPlayerPos(), playerOBJ.getPlayerVelocity(), playerOBJ.getPlayerRotation());
				if (playerOBJ.updateCOV(npcArrive.getSprite()))
				{
					playerOBJ.COV.setFillColor(sf::Color(221, 51, 47, 45));
				}
				else {
					playerOBJ.COV.setFillColor(sf::Color(141, 245, 71, 45));
				}
				npcArrive.Draw(window);
			}
			if (fleeOn)
			{
				npcFlee.Update(window, playerOBJ.getPlayerPos(), playerOBJ.getPlayerVelocity(), playerOBJ.getPlayerRotation());
				if (playerOBJ.updateCOV(npcFlee.getSprite()))
				{
					playerOBJ.COV.setFillColor(sf::Color(221, 51, 47, 45));
				}
				else {
					playerOBJ.COV.setFillColor(sf::Color(141, 245, 71, 45));
				}
				npcFlee.Draw(window);
			}


			playerOBJ.updateCOV(npcWander.getSprite());
			playerOBJ.updateCOV(npcPursue.getSprite());
			playerOBJ.updateCOV(npcArrive.getSprite());
			playerOBJ.updateCOV(npcFlee.getSprite());


			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}


	}
}