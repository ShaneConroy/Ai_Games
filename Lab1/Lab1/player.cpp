#include "player.h"


player::player()
{

	playerTexture.loadFromFile("ASSETS/ART/playerTexture.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(0.20, 0.20);
	playerSprite.setPosition(0, 50);
	sf::FloatRect playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2, playerBounds.height / 2);

	velocity = 0.0f;
	rotationSpeed = 5.0f;

}

void player::Draw(sf::RenderWindow& window)
{
	window.draw(playerSprite);
}
void player::Update(sf::RenderWindow& window)
{
	// Player rotation
	playerRotation = playerSprite.getRotation();
	float radians = playerRotation * (3.141592 / 180.0f);

	float playerVelocityX = std::cos(radians) * velocity;
	float playerVelocityY = std::sin(radians) * velocity;

	// Constantly decreasing velocity until at 0
	playerSprite.move(playerVelocityX, playerVelocityY);

	if (velocity > 0.0f)
	{
		velocity -= 0.01f;
	}

	// when reaches the right, wrap around
	if (playerSprite.getPosition().x > window.getSize().x)
	{
		playerSprite.setPosition(0 , playerSprite.getPosition().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (velocity < 5.f)
		{
			velocity += 0.1f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (velocity > 0.f)
		{
			velocity -= 0.1f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerSprite.rotate(rotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerSprite.rotate(-rotationSpeed);
	}
}