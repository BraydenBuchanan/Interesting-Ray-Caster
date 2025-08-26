#pragma once
#include <SFML/Graphics.hpp>

#define TURN_SPEED 100.f
#define MOVE_SPEED 80.f
#define PI 3.14159265359f

class Player {
public:
	void Draw(sf::RenderWindow& window);
	void Update(float dt);
public:
	sf::Vector2f pos;
	float angle = 360.f;

private:
	sf::CircleShape circle;
	sf::RectangleShape line;
};