#include <SFML/Graphics.hpp>
#include <vector>

#include "Map.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

std::vector<std::vector<int>> grid = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML");
	sf::Event event;

	window.setFramerateLimit(60.f);

	Map map(grid);
	Player player;
	Renderer renderer;

	player.pos = sf::Vector2f(50.f, 50.f);

	sf::Clock clock;
	float dt;

	while (window.isOpen()) {
		dt = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();
		}

		player.Update(dt);

		window.clear();

		renderer.draw3dView(window, player, map);

		map.Draw(window);
		player.Draw(window);
		renderer.drawRays(window, player, map);
		
		window.display();
	}
}