#include "npc.h"

npc::npc(behaviourType beginBehaviour)
	:currentBehaviour(beginBehaviour)
{
	npcTexture.loadFromFile("ASSETS/ART/npcTexture.png");
	npcSprite.setTexture(npcTexture);
	npcSprite.setScale(0.125, 0.125);
	npcSprite.setPosition(900, 500);
	npcSprite.setOrigin(npcSprite.getTextureRect().getSize().x / 2, npcSprite.getTextureRect().getSize().y / 2);

	setUpCOV();
}

void npc::Draw(sf::RenderWindow& window)
{
	if (buttonTimer > 0)
	{
		buttonTimer--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && buttonTimer == 0)
	{
		if (drawOn)
			drawOn = false;
		else if (!drawOn)
			drawOn = true;

		buttonTimer = 10;
	}
	if (drawOn)
	{
		window.draw(npcSprite);
	}
	window.draw(seekLabel);
	window.draw(wanderLabel);
	window.draw(pursueLabel);
	window.draw(arriveLabel);
	window.draw(fleeLabel);
	//window.draw(cov);
}

void npc::Update(sf::RenderWindow& window, sf::Vector2f playerPos, sf::Vector2f playerVelocity, float playerRotation)
{
	//Boundary checks
	if (currentBehaviour != behaviourType::flee)
	{
		if (npcSprite.getPosition().x > window.getSize().x) // Right boundary
		{
			npcSprite.setPosition(0, npcSprite.getPosition().y);
		}
		else if (npcSprite.getPosition().x < 0) // Left boundary
		{
			npcSprite.setPosition(window.getSize().x, npcSprite.getPosition().y);
		}

		if (npcSprite.getPosition().y > window.getSize().y) // Bottom boundary
		{
			npcSprite.setPosition(npcSprite.getPosition().x, 0);
		}
		else if (npcSprite.getPosition().y < 0) // Top boundary
		{
			npcSprite.setPosition(npcSprite.getPosition().x, window.getSize().y);
		}
	}
	else {
		if (npcSprite.getPosition().x > window.getSize().x - npcSprite.getGlobalBounds().width)
		{
			npcSprite.setPosition(window.getSize().x - npcSprite.getGlobalBounds().width, npcSprite.getPosition().y);
		}
		else if (npcSprite.getPosition().x < 0)
		{
			npcSprite.setPosition(0, npcSprite.getPosition().y);
		}
		if (npcSprite.getPosition().y > window.getSize().y - npcSprite.getGlobalBounds().height)
		{
			npcSprite.setPosition(npcSprite.getPosition().x, window.getSize().y - npcSprite.getGlobalBounds().height);
		}
		else if (npcSprite.getPosition().y < 0)
		{
			npcSprite.setPosition(npcSprite.getPosition().x, 0);
		}
	}
	
	// NPC behaviours

	if (currentBehaviour == behaviourType::flee)
	{
		npcSprite.move(behaviour.flee(npcSprite.getPosition(), playerPos, -npcSpeed));
		npcSprite.setRotation(rotateToPlayer(npcSprite, playerPos));
	}
	else if (currentBehaviour == behaviourType::arrive)
	{
		npcSprite.move(behaviour.arrive(npcSprite.getPosition(), playerPos, npcSpeed, 10));
		npcSprite.setRotation(rotateToPlayer(npcSprite, playerPos));
		
	}	
	else if (currentBehaviour == behaviourType::pursue)
	{
		npcSprite.move(behaviour.seek(npcSprite.getPosition(), behaviour.getPlayerPredictedPos(playerPos, playerVelocity, playerRotation), npcSpeed));
		npcSprite.setRotation(rotateToPlayer(npcSprite, playerPos));
	}
	else if (currentBehaviour == behaviourType::seek)
	{
		npcSprite.move(behaviour.seek(npcSprite.getPosition(), playerPos, npcSpeed)); 
		npcSprite.setRotation(rotateToPlayer(npcSprite, playerPos));
	}
	else if(currentBehaviour == behaviourType::wander)
	{
		float wanderRotation = 0.0f;
		sf::Vector2f wanderDirection = behaviour.wander(npcSpeed, wanderRotation, npcSprite.getPosition());
		npcSprite.setRotation(wanderRotation);
		npcSprite.move(wanderDirection);
	}


	labels();
	checkVision(playerPos);
}

void npc::checkVision(sf::Vector2f playerPos)
{
	if (visionDetection(playerPos) == true)
	{
		cov.setFillColor(sf::Color(221, 51, 47, 45));
	}
	else {
		cov.setFillColor(sf::Color(141, 245, 71, 45));
	}

	cov.setPoint(0, npcSprite.getPosition());
	float rotationToRadian = npcSprite.getRotation() * PI / 180.f;
	float leftPoint = rotationToRadian - (45 / 2.0f) * PI / 180.f;
	float rightPoint = rotationToRadian + (45 / 2.0f) * PI / 180.f;

	cov.setPoint(1, npcSprite.getPosition() + sf::Vector2f(cos(leftPoint), sin(leftPoint)) * coneLength);
	cov.setPoint(2, npcSprite.getPosition() + sf::Vector2f(cos(rightPoint), sin(rightPoint)) * coneLength);
}

void npc::setUpCOV()
{
	cov.setFillColor(sf::Color(141, 245, 71, 45));
	cov.setPointCount(3);
}

bool npc::visionDetection(sf::Vector2f playerPos)
{
	float distancePlayerToNPC = distanceToPlayer(playerPos, npcSprite.getPosition());
	sf::Vector2f playerDistance = playerPos - npcSprite.getPosition();

	// Players outside cone range
	if (distancePlayerToNPC > coneLength)
	{
		return false;
	}
	float rotationToRadian = npcSprite.getRotation() * PI / 180.f;
	sf::Vector2f vectorForward = normaliseVector(sf::Vector2f(std::cos(rotationToRadian), (std::sin(rotationToRadian))));
	sf::Vector2f playerDistanceNormal = normaliseVector(playerDistance);

	float dot = vectorForward.x * playerDistanceNormal.x + vectorForward.y * playerDistanceNormal.y;
	dot = std::max(-1.0f, std::min(1.0f, dot));

	float angleBetween = std::acos(dot) * 180.f / PI;
	if (angleBetween < 45)
		return true;
	else
		return false;
}

// Should seperate the npcs so they dont overlap
sf::Vector2f npc::seperate(std::vector<npc> npcArray)
{
	float seperationRadius = 5.f;
	sf::Vector2f seperationForce;
	int neighbouCount = 0;

	for (int i = 1; i < npcArray.size(); i++)
	{
		sf::Vector2f differenceBetween = npcArray[i].getSprite().getPosition() - npcArray[i].getSprite().getPosition();
		float distanceToNeighour = sqrt(differenceBetween.x * differenceBetween.x + differenceBetween.y * differenceBetween.y);

		if (distanceToNeighour < seperationRadius && distanceToNeighour > 0)
		{
			differenceBetween = differenceBetween / distanceToNeighour;
			seperationForce += differenceBetween;
			neighbouCount++;
		}

	}// for 

	if (neighbouCount > 0)
	{
		seperationForce = seperationForce / static_cast<float>(neighbouCount);
	}

	return seperationForce;
}

void npc::labels()
{
	font.loadFromFile("ASSETS/FONTS/BebasNeue.otf");
	seekLabel.setFont(font);
	seekLabel.setCharacterSize(20);
	wanderLabel.setFont(font);
	pursueLabel.setFont(font);
	arriveLabel.setFont(font);
	fleeLabel.setFont(font);

	if (currentBehaviour == behaviourType::seek) {
		seekLabel.setString("seek");
		seekLabel.setPosition(npcSprite.getPosition().x, npcSprite.getPosition().y - 10);
	}

	if (currentBehaviour == behaviourType::wander) {
		wanderLabel.setString("wander");
		wanderLabel.setPosition(npcSprite.getPosition().x, npcSprite.getPosition().y - 10);
	}

	if (currentBehaviour == behaviourType::pursue) {
		pursueLabel.setString("pursue");
		pursueLabel.setPosition(npcSprite.getPosition().x, npcSprite.getPosition().y - 10);
	}

	//if (currentBehaviour == behaviourType::arrive) {
	//	arriveLabel.setString("arrive");
	//	arriveLabel.setPosition(npcSprite.getPosition().x, npcSprite.getPosition().y - 10);
	//}

	if (currentBehaviour == behaviourType::flee) {
		fleeLabel.setString("flee");
		fleeLabel.setPosition(npcSprite.getPosition().x, npcSprite.getPosition().y - 10);
	}
}
