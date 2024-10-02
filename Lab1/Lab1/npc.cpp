#include "npc.h"

npc::npc()
{
	npcTexture.loadFromFile("ASSETS/ART/npcTexture.png");
	npcSprite.setTexture(npcTexture);
	npcSprite.setScale(0.45, 0.45);
	npcSprite.setPosition(0, 150);
}

void npc::Draw(sf::RenderWindow& window)
{
	window.draw(npcSprite);
}

void npc::Update(sf::RenderWindow& window)
{
	npcSprite.setPosition(npcSprite.getPosition().x + 2, npcSprite.getPosition().y);
	if (npcSprite.getPosition().x > window.getSize().x)
	{
		npcSprite.setPosition(0, npcSprite.getPosition().y);
	}
}
