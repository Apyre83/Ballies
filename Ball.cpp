#include "Ball.hpp"
#include "Kamlot.h"

Ball::Ball(float x, float y, float radius, float gravity, float bounce, sf::Color color)
    : x(x), y(y), radius(radius), gravity(gravity), bounce(bounce), isHoldingBall(false), velocity(0, 0) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setPosition(x, y);
}


void Ball::calculateVelocity(const std::vector<sf::RectangleShape> &obstacles, const sf::RenderWindow &window) {
	if (isHoldingBall) return;

	velocity.y += gravity;

	// Gestion des bords de la fenêtre
	if (y >= window.getSize().y - shape.getRadius()) {
		y = window.getSize().y - shape.getRadius();
		velocity.y *= -bounce;
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
		float angle = obstacle.getRotation() * 3.14159265f / 180.f; // Conversion en radians
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

/*
void Ball::calculateVelocity(const std::vector<sf::RectangleShape>& obstacles, const sf::RenderWindow& window) {
	if (isHoldingBall) return;

	velocity.y += gravity;

	// Gestion des bords de la fenêtre
	if (y + shape.getRadius() >= window.getSize().y) {
		y = window.getSize().y - shape.getRadius();
		velocity.y *= -bounce;
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
	for (const auto& obstacle : obstacles) {
		// 1. Transformation des coordonnées dans le repère de l'obstacle
		float angle = -obstacle.getRotation() * 3.14159265f / 180.f;
		float cosAngle = std::cos(angle);
		float sinAngle = std::sin(angle);

		float tx = cosAngle * (x - obstacle.getPosition().x) - sinAngle * (y - obstacle.getPosition().y);
		float ty = sinAngle * (x - obstacle.getPosition().x) + cosAngle * (y - obstacle.getPosition().y);

		// 2. Vérification de la collision avec l'AABB
		float left = 0;
		float right = obstacle.getSize().x;
		float top = 0;
		float bottom = obstacle.getSize().y;

		if (tx > left - radius && tx < right + radius && ty > top - radius && ty < bottom + radius) {
			// Collision détectée !

			float closestX = std::clamp(tx, left, right);
			float closestY = std::clamp(ty, top, bottom);

			float distanceX = tx - closestX;
			float distanceY = ty - closestY;
			float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

			if (distance < radius) {
				// 3. Ajustez la position et la vitesse
				float nx = distanceX / distance;
				float ny = distanceY / distance;

				float overlap = radius - distance;

				tx -= overlap * nx;
				ty -= overlap * ny;

				float dot = velocity.x * nx + velocity.y * ny;
				if (dot < 0) {
					velocity.x -= 2 * dot * nx * bounce;
					velocity.y -= 2 * dot * ny * bounce;
				}

				// 4. Transformez les coordonnées ajustées de retour dans le repère du monde
				x = cosAngle * tx + sinAngle * ty + obstacle.getPosition().x;
				y = -sinAngle * tx + cosAngle * ty + obstacle.getPosition().y;
			}
		}
	}
}
*/


void Ball::update(float dt) {
    velocity.y += gravity * dt / TIME_FACTOR;
    x += velocity.x * dt / TIME_FACTOR;
    y += velocity.y * dt / TIME_FACTOR;

    setPosition(x, y);
}
