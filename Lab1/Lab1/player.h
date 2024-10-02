#include "globals.h"

class player
{
public:
	player();
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
private:
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	double velocity;
	double rotationSpeed;
	double playerRotation;
};



