#include "Ballies.h"

void initializeGame(sf::RenderWindow& window, std::vector<Ball>& balls, bool raceMode) {
    std::random_device rd;
    std::mt19937 gen(rd());

    float y = window.getSize().y / 2.0f;

	sf::Color color(255, 0, 0);

    std::uniform_int_distribution<> distrib(0, 1920);
    balls.clear();
    for (int i = 0; i < 50; i++) {
        float pos = static_cast<float>(distrib(gen));
		
		if (!raceMode) color = sf::Color(4 * i, 255 - 4 * i, 0);

        Ball ball(pos, y / 2, 20.f, GRAVITY, BOUNCE, color, raceMode);
        ball.setOutline(2, sf::Color::White);
        balls.push_back(ball);
    }
}


std::vector<sf::RectangleShape> parseConfFile(const std::string& file) {
    std::ifstream confFile(file);
    std::string line;
    std::vector<sf::RectangleShape> rectangles;

    if (!confFile) {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }

    while (getline(confFile, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "rectangle") {
            float x, y, width, height, rotation;
            int r, g, b;
            iss >> x >> y >> width >> height >> rotation >> r >> g >> b;
            std::cout << "x: " << x << " y: " << y << " width: " << width << " height: " << height << " rotation: " << rotation << " r: " << r << " g: " << g << " b: " << b << std::endl;

            sf::RectangleShape rectangle(sf::Vector2f(width, height));
            rectangle.setPosition({ x, y });
            rectangle.setRotation(sf::Angle(rotation));
            rectangle.setFillColor(sf::Color(r, g, b));
            rectangles.push_back(rectangle);
        }
    }
    return rectangles;
}
