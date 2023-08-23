#include "Ball.hpp"
#include "Ballies.h"

Ball::Ball(float x, float y, float radius, float gravity, float bounce, sf::Color color, bool raceMode)
    : x(x), y(y), radius(radius), gravity(gravity), bounce(bounce), initialColor(color), raceMode(raceMode), numberText(textFont) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition({ x, y });
	
}


void Ball::calculateVelocity(const std::vector<sf::RectangleShape> &obstacles, const sf::RenderWindow &window, unsigned int &lastBallNumber) {
	if (isHoldingBall) return;

	velocity.y += gravity;

	// Gestion des bords de la fenêtre
	if (y >= window.getSize().y - shape.getRadius()) {
		y = window.getSize().y - shape.getRadius();
		velocity.y *= -bounce;
		if (raceMode && !hasFallen) {
			initialColor = sf::Color(0, 255, 0);
			hasFallen = true;
			shape.setFillColor(initialColor);
			setNumber(lastBallNumber);
			lastBallNumber++;
		}
	}

	if (y <= shape.getRadius()) {
		y = shape.getRadius();
		velocity.y *= -bounce;
	}

	if (x >= window.getSize().x - shape.getRadius()) {
		x = window.getSize().x - shape.getRadius();
		velocity.x *= -bounce;
	}

	if (x <= shape.getRadius()) {
		x = shape.getRadius();
		velocity.x *= -bounce;
	}

	// Vérification de la collision avec chaque obstacle
	for (const auto& obstacle : obstacles)
	{
		float angle = obstacle.getRotation().asRadians(); // Conversion en radians
		float nx = std::sin(angle); // Composante x de la normale
		float ny = -std::cos(angle); // Composante y de la normale

		float dx = x - obstacle.getPosition().x;
		float dy = y - obstacle.getPosition().y;
		float t = dx * std::cos(angle) + dy * std::sin(angle);

		// Vérification de la collision
		float d = dx * nx + dy * ny;
		if (std::abs(d) <= shape.getRadius() && t >= 0 && t <= obstacle.getSize().x)
		{
			// Calcul de la réflexion basée sur la normale
			float dot = velocity.x * nx + velocity.y * ny;
			if (dot < 0) {
				velocity.x -= 2 * dot * nx * bounce;
				velocity.y -= 2 * dot * ny * bounce;
			}
		}
	}
}


void Ball::update(float dt) {
    velocity.y += gravity * dt / TIME_FACTOR;
    x += velocity.x * dt / TIME_FACTOR;
    y += velocity.y * dt / TIME_FACTOR;

    setPosition(x, y);
}


sf::Font Ball::textFont;


void Ball::loadFont(const std::string& fontPath) {
	if (!textFont.loadFromFile(fontPath)) {
		std::cout << "Unable to load font" << std::endl;
		exit(1);
	}
}
