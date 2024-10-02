#include "globals.h"

class player
{
public:
	player();
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	sf::Vector2f getPlayerPos();
	sf::Vector2f getPlayerVelocity();
	float getPlayerRotation();	
	bool updateCOV(sf::Sprite npcSprite);
	sf::ConvexShape COV;

private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	double velocity;
	double rotationSpeed;
	double playerRotation;
	sf::Vector2f playerVelocity;


};



