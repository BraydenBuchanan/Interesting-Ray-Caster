#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define CELL_SIZE 20.f

class Map {
public:
	Map(std::vector<std::vector<int>> grid);
	void Draw(sf::RenderWindow& window);

	float getCellSize() const { return CELL_SIZE; }
	const std::vector<std::vector<int>> getGrid() const { return grid; }
private:
	std::vector<std::vector<int>> grid;
	sf::RectangleShape cell;
};