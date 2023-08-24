
#ifndef BALLIES_H
#define BALLIES_H

#include <SFML/Graphics.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <cmath>
#include <random>

#include "Ball.hpp"


extern float TIME_FACTOR;
extern float BOUNCE;
extern float GRAVITY;


#define RECTANGLE_WIDTH 15.0f


void	initializeGame(sf::RenderWindow& window, std::vector<Ball>& balls, bool raceMode);
std::vector<sf::RectangleShape>	parseConfFile(const std::string& file);

#endif