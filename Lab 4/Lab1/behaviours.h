#pragma once
#include "globals.h"

class behaviours
{
public:
	sf::Vector2f seek(sf::Vector2f currentPos, sf::Vector2f playerPos, float currentSpeed);
	sf::Vector2f wander(float currentSpeed, float& wanderRotation, const sf::Vector2f& npcPos );
	sf::Vector2f getPlayerPredictedPos(sf::Vector2f playerPos, sf::Vector2f playerVelocity, float rotation);
	sf::Vector2f arrive(sf::Vector2f currentPos, sf::Vector2f playerPos, float currentSpeed, float arriveRadius);
	sf::Vector2f flee(sf::Vector2f currentPos, sf::Vector2f playerPos, float currentSpeed);

private:

	int timer;
	sf::Vector2f wanderDirection;
};