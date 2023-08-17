#include "Kamlot.h"

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
            rectangle.setPosition(x, y);
            rectangle.setRotation(rotation);
            rectangle.setFillColor(sf::Color(r, g, b));
            rectangles.push_back(rectangle);
        }
    }
    return rectangles;
}

void initializeGame(sf::RenderWindow& window, std::vector<sf::RectangleShape>& obstacles, std::vector<Ball>& balls, std::mt19937& gen) {
    float x = window.getSize().x / 2.0f;
    float y = window.getSize().y / 2.0f;

    std::uniform_int_distribution<> distrib(0, 1920);
    balls.clear();
    for (int i = 0; i < 50; i++) {
        float pos = static_cast<float>(distrib(gen));
        Ball ball(pos, y / 2, 20.f, GRAVITY, BOUNCE, sf::Color(4 * i, 255 - 4 * i, 0));
        ball.setOutline(2, sf::Color::White);
        balls.push_back(ball);
    }
}

int main(void) {
    std::random_device rd;
    std::mt19937 gen(rd());

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Kamlot", sf::Style::Fullscreen);

    std::vector<sf::RectangleShape> obstacles = parseConfFile("conf");
    std::vector<Ball> balls;

    initializeGame(window, obstacles, balls, gen);

    sf::Clock clock;

	bool isDrawing = false;
	sf::Vector2i startPosition;
	const float RECTANGLE_WIDTH = 15.0f;  // Vous pouvez ajuster cette valeur selon vos besoins.
	
	bool	isPaused = false;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                isPaused = false;
				initializeGame(window, obstacles, balls, gen);
            }
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				startPosition = sf::Mouse::getPosition(window);
				isDrawing = true;
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				isDrawing = false;
				sf::Vector2i endPosition = sf::Mouse::getPosition(window);

				float dx = static_cast<float>(endPosition.x - startPosition.x);
				float dy = static_cast<float>(endPosition.y - startPosition.y);
				float length = std::sqrt(dx * dx + dy * dy);
				float rotation = std::atan2(dy, dx) * 180.0f / 3.14159265f;  // Convertir en degrés

				sf::RectangleShape rectangle;
				rectangle.setPosition(static_cast<float>(startPosition.x), static_cast<float>(startPosition.y));
				rectangle.setSize(sf::Vector2f(length, RECTANGLE_WIDTH));
				rectangle.setOrigin(0, RECTANGLE_WIDTH / 2); // Centrer la rotation autour du milieu du rectangle
				rectangle.setRotation(rotation);
				rectangle.setFillColor(sf::Color::Blue);

				obstacles.push_back(rectangle);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
				obstacles.clear();
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				isPaused = !isPaused;
			}

        }

		if (isDrawing) {
			sf::RectangleShape tempRectangle;
			tempRectangle.setPosition(static_cast<float>(startPosition.x), static_cast<float>(startPosition.y));
			sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
			tempRectangle.setSize(sf::Vector2f(static_cast<float>(currentMousePosition.x - startPosition.x), static_cast<float>(currentMousePosition.y - startPosition.y)));
			tempRectangle.setFillColor(sf::Color(100, 100, 100, 100));
			window.draw(tempRectangle);
		}



        float dt = clock.restart().asSeconds();

		if (isPaused) {
			continue;
		}

        for (auto& ball : balls) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                double distance = std::sqrt(std::pow(ball.getX() - mousePos.x, 2) + std::pow(ball.getY() - mousePos.y, 2));
                if (distance <= ball.getRadius() && !ball.getIsHoldingBall()) {
                    ball.setIsHoldingBall(true);
                }
            }
            else {
                ball.setIsHoldingBall(false);
            }

            if (ball.getIsHoldingBall()) // Si l'utilisateur tient la balle
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                float x = static_cast<float>(mousePos.x);
                float y = static_cast<float>(mousePos.y);
                ball.setVelocity(0, 0);
                ball.setPosition(x, y);
            }
            else
            {
                ball.calculateVelocity(obstacles, window);
                ball.update(dt);
            }
        }

        window.clear();
        for (auto& ball : balls)
            ball.draw(window);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle);
        }

        window.display();
    }

    return 0;
}
