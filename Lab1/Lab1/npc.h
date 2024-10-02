#include "globals.h"

class npc
{
public:
	npc();
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);

private:
	sf::Sprite npcSprite;
	sf::Texture npcTexture;

};
