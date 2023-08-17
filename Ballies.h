
#pragma once

#include <SFML/Graphics.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <cmath>
#include <random>

#include "Ball.hpp"


#ifdef _WIN64
#define TIME_FACTOR 5
#define BOUNCE 0.7f
#define GRAVITY 2.0f

#elif _WIN32
#define TIME_FACTOR 5
#define BOUNCE 0.7f
#define GRAVITY 2.0f

#elif __linux__
#define TIME_FACTOR 1
#define BOUNCE 0.8f
#define GRAVITY 2.0f

#endif