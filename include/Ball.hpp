
#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

class Ball {
private:
    float			x,	y;
    float			radius;
    float			gravity;
    float			bounce;
    bool			isHoldingBall = false;
    sf::Vector2f	velocity = { 0, 0 };
    sf::CircleShape	shape;
	sf::Color		initialColor;
	bool			hasFallen = false;
	bool			raceMode;

	static sf::Font	textFont;
	sf::Text		numberText;


public:
    Ball(float x, float y, float radius, float gravity, float bounce, sf::Color color, bool raceMode);

    void	calculateVelocity(const std::vector<sf::RectangleShape> &obstacles, const sf::RenderWindow &window, unsigned int &lastBallNumber);
    void	update(float dt);
    void	draw(sf::RenderWindow& window) {
		window.draw(shape);
		
		if (hasFallen && raceMode) {
			numberText.setPosition({ x + radius - 2, y + radius - 5 });
			window.draw(numberText);
		}
	}


    void	setOutline(float thickness, const sf::Color& color) {
        shape.setOutlineThickness(thickness);
        shape.setOutlineColor(color);
    }
    void	setPosition(float x, float y) {
        this->x = x;
        this->y = y;
        shape.setPosition({ x, y });
    }
    void	setVelocity(float vx, float vy) {
        velocity.x = vx;
        velocity.y = vy;
    }
    void	setIsHoldingBall(bool holding) { isHoldingBall = holding; }


	void	setNumber(int number) {

		numberText.setFont(textFont);
		numberText.setString(std::to_string(number));
		numberText.setCharacterSize(20);
		numberText.setFillColor(sf::Color::Black);

		sf::FloatRect textRect = numberText.getLocalBounds();

		numberText.setOrigin({ textRect.width / 2.0f, textRect.height / 2.0f });
	}

	static void	loadFont(const std::string& fontPath);


    float	getX() const { return (x); }
    float	getY() const { return (y); }
    float	getRadius() const { return (radius); }
    bool	getIsHoldingBall() const { return (isHoldingBall); }
};

#endif // BALL_HPP

