#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"
#include "Map.hpp"

#define SCREEN_WIDTH 1200.f
#define SCREEN_HEIGHT 675.f

#define PI 3.14159265359f
#define FOV 60.f
#define MAX_RAY_CAST_DEPTH 16
#define NO_OF_RAYS 1200
#define COL_WIDTH SCREEN_WIDTH / (float)NO_OF_RAYS

struct Ray {
	sf::Vector2f hitPos;
	float dist;
	bool isHit;
	bool isHitVertical;
};

static Ray castRay(sf::Vector2f start, float angleInDegrees, const Map& map);

class Renderer {
public:
	Renderer();

	void draw3dView(sf::RenderWindow& window, Player& player, const Map& map);
	void drawRays(sf::RenderWindow& window, const Player& player, const Map& map);

private:
	sf::RectangleShape sky;
	sf::RectangleShape ground;

	std::unique_ptr<sf::Texture> skyTexture;
	std::unique_ptr<sf::Texture> wallTexture;
};