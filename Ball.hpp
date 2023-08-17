
#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Ball {
private:
    float x, y;
    float radius;
    float gravity;
    float bounce;
    bool isHoldingBall;
    sf::Vector2f velocity;
    sf::CircleShape shape;

public:
    Ball(float x, float y, float radius, float gravity, float bounce, sf::Color color);

    void calculateVelocity(const std::vector<sf::RectangleShape> &obstacles, const sf::RenderWindow &window);
    void update(float dt);
    void draw(sf::RenderWindow& window) { window.draw(shape); }


    void setOutline(float thickness, const sf::Color& color) {
        shape.setOutlineThickness(thickness);
        shape.setOutlineColor(color);
    }
    void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
        shape.setPosition(x, y);
    }
    void setVelocity(float vx, float vy) {
        velocity.x = vx;
        velocity.y = vy;
    }
    void setIsHoldingBall(bool holding) { isHoldingBall = holding; }

    float getX() const { return (x); }
    float getY() const { return (y); }
    float getRadius() const { return (radius); }
    bool getIsHoldingBall() const { return (isHoldingBall); }
};

#endif // BALL_HPP

