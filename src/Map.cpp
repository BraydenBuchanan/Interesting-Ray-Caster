#include "Map.hpp"

Map::Map(std::vector<std::vector<int>> grid) : grid(grid) {}

void Map::Draw(sf::RenderWindow& window) {
	cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cell.setOutlineThickness(1.f);
	cell.setOutlineColor(sf::Color::Black);

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == 0)
				cell.setFillColor(sf::Color::White);
			else if (grid[i][j] == 1)
				cell.setFillColor(sf::Color::Red);

			cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);
			window.draw(cell);
		}
	}
}