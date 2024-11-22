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

	std::vector<npc> fingerFourArray;

	npc ffOne(behaviourType::arrive);
	npc ffTwo(behaviourType::arrive);
	npc ffThree(behaviourType::arrive);
	npc ffFour(behaviourType::arrive);

	fingerFourArray.push_back(ffOne);
	fingerFourArray.push_back(ffTwo);
	fingerFourArray.push_back(ffThree);
	fingerFourArray.push_back(ffFour);

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

			std::vector<sf::Vector2f> ffPos = playerOBJ.getAnchorPoints();

			/*
			new vector = ffpos
			ffpos = - (ffpos.y * distance between opint and enemy)
			*/
			for (int i = 0; i < ffPos.size(); i++)
			{
				//sf::Vector2f movePointPos = ffPos[i];
				//float distance = distanceToPlayer(fingerFourArray[i].getSprite().getPosition(), playerOBJ.getPlayerPos());
				//distance /= 1000;
				//movePointPos = sf::Vector2f(movePointPos.x, -(movePointPos.y * distance));

				//float playerRadi = playerOBJ.getPlayerRotation() * (PI / 180.f);
				//sf::Vector2f yoke = playerOBJ.rotateAnchorPoints(movePointPos, playerRadi);

				fingerFourArray[i].Update(window, ffPos[i], playerOBJ.getPlayerVelocity(), playerOBJ.getPlayerRotation());
				fingerFourArray[i].Draw(window);
			}// for

			playerOBJ.updateCOV(npcWander.getSprite());
			playerOBJ.updateCOV(npcPursue.getSprite());
			playerOBJ.updateCOV(npcArrive.getSprite());
			playerOBJ.updateCOV(npcFlee.getSprite());


			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}


	}
}