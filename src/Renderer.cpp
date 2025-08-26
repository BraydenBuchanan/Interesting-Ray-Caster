#include "Renderer.hpp"

Renderer::Renderer() {
	skyTexture = std::make_unique<sf::Texture>();
	wallTexture = std::make_unique<sf::Texture>();
}

void Renderer::draw3dView(sf::RenderWindow& window, Player& player, const Map& map) {
	skyTexture->loadFromFile("Weez.jpg");
	wallTexture->loadFromFile("Weez.png");

	sky.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2.f));
	sky.setTexture(skyTexture.get());

	ground.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2.f));
	ground.setPosition(0.f, SCREEN_HEIGHT / 2.f);
	ground.setFillColor(sf::Color(90, 90, 90));

	window.draw(sky);
	window.draw(ground);
	
	float angle = player.angle - FOV / 2.f;
	float angleIncrement = FOV / float(NO_OF_RAYS);
	float MaxRenderDist = MAX_RAY_CAST_DEPTH * map.getCellSize();

	for (int i = 0; i < NO_OF_RAYS; i++, angle += angleIncrement) {
		Ray ray = castRay(player.pos, angle, map);

		if (ray.isHit) {
			ray.dist *= cos((player.angle - angle) * PI / 180.f);
			float wallHeight = (map.getCellSize() * SCREEN_HEIGHT) / ray.dist;

			if (wallHeight > SCREEN_HEIGHT)
				wallHeight = SCREEN_HEIGHT;

			float brightness = 1.f - (ray.dist / MaxRenderDist);

			if (brightness < 0.f)
				brightness = 0.f;

			float shade = (ray.isHitVertical ? 0.5f : 1.f) * brightness;
			float wallOffset = SCREEN_HEIGHT / 2.f - wallHeight / 2.f;

			sf::RectangleShape column(sf::Vector2f(COL_WIDTH, wallHeight));
			column.setPosition(i * COL_WIDTH, wallOffset);
			column.setFillColor(sf::Color(255 * shade, 255 * shade, 255 * shade));
			column.setTexture(wallTexture.get());
			column.setTextureRect(sf::IntRect(i * COL_WIDTH, 0, 100, 675));

			window.draw(column);
		}
	}
}

void Renderer::drawRays(sf::RenderWindow& window, const Player& player, const Map& map) {
	for (float angle = player.angle - FOV / 2; angle < player.angle + FOV; angle += 0.2f) {
		Ray ray = castRay(player.pos, angle, map);

		if (ray.isHit) {
			sf::Vertex line[] = {
				sf::Vertex(player.pos, sf::Color::Green),
				sf::Vertex(ray.hitPos, sf::Color::Green)
			};

			window.draw(line, 2, sf::Lines);
		}
	}
}

Ray castRay(sf::Vector2f start, float angleInDegrees, const Map& map) {
	float angle = angleInDegrees * PI / 180.f;
	float verticalTan = -1.f / tan(angle);
	float horizontalTan = -tan(angle);

	float cellSize = map.getCellSize();
	bool isHit = false;

	size_t horDOF = 0, verDOF = 0;

	float verticalDist = std::numeric_limits<int>::max();
	float horizontalDist = std::numeric_limits<int>::max();

	sf::Vector2f verRayPos, horRayPos, offset;

	// HORIZONTAL WALLS

	if (cos(angle) > 0.001f) { // left
		horRayPos.x = floor(start.x / cellSize) * cellSize + cellSize;
		horRayPos.y = (start.x - horRayPos.x) * horizontalTan + start.y;

		offset.x = cellSize;
		offset.y = -offset.x * horizontalTan;
	}

	else if (cos(angle) < -0.001f) { // right
		horRayPos.x = floor(start.x / cellSize) * cellSize - 0.01f;
		horRayPos.y = (start.x - horRayPos.x) * horizontalTan + start.y;

		offset.x = -cellSize;
		offset.y = -offset.x * horizontalTan;
	}

	else horDOF = MAX_RAY_CAST_DEPTH;

	const auto& grid = map.getGrid();

	for (; horDOF < MAX_RAY_CAST_DEPTH; horDOF++) {
		int mapX = int(horRayPos.x / cellSize);
		int mapY = int(horRayPos.y / cellSize);

		if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX]) {
			isHit = true;

			horizontalDist = sqrt((horRayPos.x - start.x) * (horRayPos.x - start.x) + (horRayPos.y - start.y) * (horRayPos.y - start.y));
			break;
		}

		horRayPos += offset;
	}

	/**************************************************************/

	// VERTICAL WALLS

	if (sin(angle) > 0.001f) {
		verRayPos.y = floor(start.y / cellSize) * cellSize + cellSize;
		verRayPos.x = (start.y - verRayPos.y) * verticalTan + start.x;

		offset.y = cellSize;
		offset.x = -offset.y * verticalTan;
	}

	else if (sin(angle) < -0.001f) {
		verRayPos.y = floor(start.y / cellSize) * cellSize - 0.01f;
		verRayPos.x = (start.y - verRayPos.y) * verticalTan + start.x;

		offset.y = -cellSize;
		offset.x = -offset.y * verticalTan;
	}

	else verDOF = MAX_RAY_CAST_DEPTH;

	for (; verDOF < MAX_RAY_CAST_DEPTH; verDOF++) {
		int mapX = int(verRayPos.x / cellSize);
		int mapY = int(verRayPos.y / cellSize);

		if (mapY < grid.size() && mapX < grid[mapY].size() && grid[mapY][mapX]) {
			isHit = true;

			verticalDist = sqrt((verRayPos.x - start.x) * (verRayPos.x - start.x) + (verRayPos.y - start.y) * (verRayPos.y - start.y));
			break;
		}

		verRayPos += offset;
	}
	return Ray{ horizontalDist < verticalDist ? horRayPos : verRayPos, std::min(horizontalDist, verticalDist), isHit, verticalDist < horizontalDist };
}