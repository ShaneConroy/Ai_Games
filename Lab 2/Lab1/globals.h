#pragma once

#ifdef _DEBUG  
#pragma comment(lib,"sfml-graphics-d.lib")  
#pragma comment(lib,"sfml-audio-d.lib")  
#pragma comment(lib,"sfml-system-d.lib")  
#pragma comment(lib,"sfml-window-d.lib")  
#pragma comment(lib,"sfml-network-d.lib")  
#else  
#pragma comment(lib,"sfml-graphics.lib")  
#pragma comment(lib,"sfml-audio.lib")  
#pragma comment(lib,"sfml-system.lib")  
#pragma comment(lib,"sfml-window.lib")  
#pragma comment(lib,"sfml-network.lib")  
#endif  

#include <iostream>
#include <SFML/Graphics.hpp> 
#include <random>

sf::Vector2f normaliseVector(const sf::Vector2f& vector);
float rotateToPlayer(sf::Sprite& npc, const sf::Vector2f& playerPos);
sf::Vector2f getRandomCoord();
float distanceToPlayer(sf::Vector2f playerPos, sf::Vector2f npcPos);

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;