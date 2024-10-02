#include "globals.h"
#include "behavioursEnum.h"
#include "behaviours.h"

class npc
{
public:
	npc(behaviourType beginBehaviour);
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, sf::Vector2f playerPos, sf::Vector2f playerVelocity, float playerRotation);
	void checkVision(sf::Vector2f playerPos);
	void setUpCOV();
	bool visionDetection(sf::Vector2f playerPos);
	sf::Sprite getSprite() { return npcSprite; }

private:
	sf::Sprite npcSprite;
	sf::Texture npcTexture;
	behaviourType currentBehaviour;
	behaviours behaviour;
	float npcSpeed = 2.0f;

	void labels();
	sf::Font font;

	sf::Text seekLabel;
	sf::Text wanderLabel;
	sf::Text pursueLabel;
	sf::Text arriveLabel;
	sf::Text fleeLabel;

	float coneLength = 250;
	sf::ConvexShape cov;
};
