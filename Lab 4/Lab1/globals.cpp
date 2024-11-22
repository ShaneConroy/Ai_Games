#include "globals.h"

//Given a vector, normalises it and returns
sf::Vector2f normaliseVector(const sf::Vector2f& vector)
{
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length != 0)
	{
		return vector / length;
	}
	return sf::Vector2f(0.f, 0.f);
}

// given a sprite and coord, rotates the sprite towards the coord
float rotateToPlayer(sf::Sprite& npc, const sf::Vector2f& playerPos)
{
	sf::Vector2f angleToTarget = playerPos - npc.getPosition();

	float radians = atan2(angleToTarget.y, angleToTarget.x);

	float newRotation = ((radians * 180 / PI));

	return newRotation;
}

sf::Vector2f getRandomCoord()
{
	// Code for getting random X, Y coord
	sf::Vector2f randomCoord;
	float randX = rand() % 1200;
	float randY = rand() % 800;

	randomCoord = { randX, randY };

	return randomCoord;
}

float distanceToPlayer(sf::Vector2f playerPos, sf::Vector2f npcPos)
{
	float distanceX = playerPos.x - npcPos.x;
	float distanceY = playerPos.y - npcPos.y;

	float distanceTo = std::sqrt(distanceX * distanceX + distanceY * distanceY);

	return distanceTo;
}
