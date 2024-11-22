#include "player.h"


player::player()
{

	playerTexture.loadFromFile("ASSETS/ART/playerTexture.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(0.10, 0.10);
	playerSprite.setPosition(600, 400);
	sf::FloatRect playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2, playerBounds.height / 2);

	velocity = 0.0f;
	rotationSpeed = 1.5f;

	COV.setFillColor(sf::Color(141, 245, 71, 45));
	COV.setPointCount(3);
}

void player::Draw(sf::RenderWindow& window)
{

	if (buttonTimer > 0)
	{
		buttonTimer--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && buttonTimer == 0)
	{
		if (drawOn)
			drawOn = false;
		else if (!drawOn)
			drawOn = true;

		buttonTimer = 10;
	}
	if (drawOn)
	{
		window.draw(COV);
		drawAnchorPoints(window);
	}
	window.draw(playerSprite);


}
void player::Update(sf::RenderWindow& window)
{
	// Player rotation
	playerRotation = playerSprite.getRotation();
	float radians = playerRotation * (PI / 180.0f);

	float playerVelocityX = std::cos(radians) * velocity;
	float playerVelocityY = std::sin(radians) * velocity;
	playerVelocity = { playerVelocityX, playerVelocityY };

	// Constantly decreasing velocity until at 0
	playerSprite.move(playerVelocityX, playerVelocityY);

	if (velocity > 0.0f)
	{
		velocity -= 0.01f;
	}

	// when reaches the right, wrap around
	if (playerSprite.getPosition().x > window.getSize().x)
	{
		playerSprite.setPosition(0, playerSprite.getPosition().y);
	}
	if (playerSprite.getPosition().x < 0)
	{
		playerSprite.setPosition(window.getSize().x, playerSprite.getPosition().y);
	}
	if (playerSprite.getPosition().y > window.getSize().y)
	{
		playerSprite.setPosition(playerSprite.getPosition().x, 0);
	}
	if (playerSprite.getPosition().y < 0)
	{
		playerSprite.setPosition(playerSprite.getPosition().x, window.getSize().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (velocity < 2.f)
		{
			velocity += 0.1f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (velocity > 0.f)
		{
			velocity -= 0.1f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerSprite.rotate(rotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerSprite.rotate(-rotationSpeed);
	}
}

sf::Vector2f player::getPlayerPos()
{
	return sf::Vector2f(playerSprite.getPosition());
}

sf::Vector2f player::getPlayerVelocity()
{
	return playerVelocity;
}

float player::getPlayerRotation()
{
	return playerSprite.getRotation();
}

bool player::updateCOV(sf::Sprite npcSprite)
{
	COV.setPoint(0, playerSprite.getPosition());
	float rotationToRadian = playerSprite.getRotation() * PI / 180.f;
	float leftPoint = rotationToRadian - (45 / 2.0f) * PI / 180.f;
	float rightPoint = rotationToRadian + (45 / 2.0f) * PI / 180.f;

	COV.setPoint(1, playerSprite.getPosition() + sf::Vector2f(cos(leftPoint), sin(leftPoint)) * 250.f);
	COV.setPoint(2, playerSprite.getPosition() + sf::Vector2f(cos(rightPoint), sin(rightPoint)) * 250.f);

	float distancePlayerToNPC = distanceToPlayer(playerSprite.getPosition(), npcSprite.getPosition());
	sf::Vector2f playerDistance = npcSprite.getPosition() - playerSprite.getPosition();

	// Players outside cone range
	if (distancePlayerToNPC > 250)
	{
		return false;
	}
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

std::vector<sf::Vector2f> player::getAnchorPoints()
{
	std::vector<sf::Vector2f> anchorPoints;
	float playerRadi = playerSprite.getRotation() * (PI / 180.f);

	sf::Vector2f pointOne{ 50, 100 };
	sf::Vector2f pointTwo{ 50, -100 };
	sf::Vector2f pointThree{ 175, 0 };
	sf::Vector2f pointFour{ -100, -150 };

	sf::Vector2f rotatedPointOne = playerSprite.getPosition() + rotateAnchorPoints(pointOne, playerRadi);
	sf::Vector2f rotatedPointTwo = playerSprite.getPosition() + rotateAnchorPoints(pointTwo, playerRadi);
	sf::Vector2f rotatedPointThree = playerSprite.getPosition() + rotateAnchorPoints(pointThree, playerRadi);
	sf::Vector2f rotatedPointFour = playerSprite.getPosition() + rotateAnchorPoints(pointFour, playerRadi);

	anchorPoints.push_back(rotatedPointOne);
	anchorPoints.push_back(rotatedPointTwo);
	anchorPoints.push_back(rotatedPointThree);
	anchorPoints.push_back(rotatedPointFour);

	return anchorPoints;
}


//
void player::drawAnchorPoints(sf::RenderWindow& window)
{
	std::vector<sf::Vector2f> anchorPoints = getAnchorPoints();
	for (sf::Vector2f point : anchorPoints)
	{
		sf::CircleShape circle;
		circle.setRadius(5.f);
		circle.setFillColor(sf::Color::Green);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(point);
		window.draw(circle);
	}
}

sf::Vector2f player::rotateAnchorPoints(sf::Vector2f point, float radians)
{
	float cos, sin;
	cos = std::cos(radians);
	sin = std::sin(radians);

	return sf::Vector2f(point.x * cos - point.y * sin, point.x * sin + point.y * cos);
}
