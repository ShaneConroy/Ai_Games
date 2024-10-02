#include "behaviours.h"

// Goes straight for the player
sf::Vector2f behaviours::seek(sf::Vector2f currentPos, sf::Vector2f playerPos, float currentSpeed)
{
	sf::Vector2f vectorToPlayer = playerPos - currentPos;
	sf::Vector2f normalisedVector = normaliseVector(vectorToPlayer);
	sf::Vector2f direction = normalisedVector * currentSpeed;

	return direction;
}

// Will pick a random spot on screen and go towards it, after a delay, will do it again
sf::Vector2f behaviours::wander(float currentSpeed, float& wanderRotation, const sf::Vector2f& npcPos)
{
	timer--;
	if (timer < 0)
	{
		sf::Vector2f randomPoint = getRandomCoord();
		sf::Vector2f direction = randomPoint - npcPos;
		float distanceToTarget = (direction.x * direction.x + direction.y * direction.y);

		sf::Vector2f normalisedVector = normaliseVector(direction);

		wanderDirection = normalisedVector * currentSpeed;

		float directionRadians = std::atan2(direction.x, direction.y);
		wanderRotation = directionRadians * PI / 180.f;

		timer = 500;
	}
	return wanderDirection;
}

// Gets the pplayers predicted pos in a set amount of frames
sf::Vector2f behaviours::getPlayerPredictedPos(sf::Vector2f playerPos, sf::Vector2f playerVelocity, float rotation)
{
	sf::Vector2f predictedPos;
	predictedPos = playerPos;
	sf::Vector2f normalisedPlayerVelocity = normaliseVector(playerVelocity);

	float radians = rotation * PI / 180.f;
	predictedPos.x += cos(radians) * (playerVelocity.x * 5);
	predictedPos.y += sin(radians) * (playerVelocity.y * 5);

	return predictedPos;
}

sf::Vector2f behaviours::arrive(sf::Vector2f currentPos, sf::Vector2f playerPos, float currentSpeed, float arriveRadius)
{
	sf::Vector2f vectorToPlayer = playerPos - currentPos;
	sf::Vector2f normalisedVector = normaliseVector(vectorToPlayer);

	sf::Vector2f direction;

	float length = std::sqrt(vectorToPlayer.x * vectorToPlayer.x + vectorToPlayer.y * vectorToPlayer.y);
	direction = normalisedVector * (currentSpeed * (length / 100));

	return direction;
}

// Runs in the opposite direction of the player 
sf::Vector2f behaviours::flee(sf::Vector2f currentPos, sf::Vector2f playerPos, float currentSpeed)
{
	sf::Vector2f vectorToPlayer = playerPos - currentPos;
	sf::Vector2f normalisedVector = normaliseVector(vectorToPlayer);
	sf::Vector2f direction = normalisedVector * currentSpeed;

	return direction;
}
