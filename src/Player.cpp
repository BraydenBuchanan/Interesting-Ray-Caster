#include "Player.hpp"

void Player::Update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		angle -= TURN_SPEED * dt;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		angle += TURN_SPEED * dt;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		float Radians = angle * PI / 180.f;

		pos.x += cos(Radians) * MOVE_SPEED * dt;
		pos.y += sin(Radians) * MOVE_SPEED * dt;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		float Radians = angle * PI / 180.f;

		pos.x -= cos(Radians) * MOVE_SPEED * dt;
		pos.y -= sin(Radians) * MOVE_SPEED * dt;
	}
}

void Player::Draw(sf::RenderWindow& window) {
	circle.setRadius(8.f);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(pos);
	circle.setFillColor(sf::Color::Green);

	line.setSize(sf::Vector2f(20.f, 2.f));
	line.setPosition(pos);
	line.setRotation(angle);
	line.setFillColor(sf::Color::Green);

	window.draw(line);
	window.draw(circle);
}
