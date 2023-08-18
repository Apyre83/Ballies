#include "Ballies.h"

void	calculateBallsPosition(std::vector<Ball>& balls, float dt, std::vector<sf::RectangleShape>& obstacles, sf::RenderWindow& window)
{
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
}

void handleEvents(sf::RenderWindow& window, bool& isPaused, std::vector<sf::RectangleShape>& obstacles, bool& isDrawing, sf::Vector2i& startPosition, std::mt19937& gen, std::vector<Ball>& balls) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            isPaused = false;
            initializeGame(window, balls, gen);
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
            float rotation = std::atan2(dy, dx) * 180.0f / 3.14159265f;

            sf::RectangleShape rectangle;
            rectangle.setPosition(static_cast<float>(startPosition.x), static_cast<float>(startPosition.y));
            rectangle.setSize(sf::Vector2f(length, RECTANGLE_WIDTH));
            rectangle.setOrigin(0, RECTANGLE_WIDTH / 2);
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
}


int main(void) {
    std::random_device rd;
    std::mt19937 gen(rd());

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Kamlot", sf::Style::Fullscreen);

    std::vector<sf::RectangleShape> obstacles = parseConfFile("conf");
    std::vector<Ball> balls;

    initializeGame(window, balls, gen);

    sf::Clock clock;

	bool isDrawing = false;
	sf::Vector2i startPosition;
	
	bool	isPaused = false;

	

	sf::Font font;
	if (!font.loadFromFile("res/O4B.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return 1;
	}

	int		frameCounter = 0;
	float	timeAccumulator = 0.0f;

	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(10, 10);


    while (window.isOpen()) {

        handleEvents(window, isPaused, obstacles, isDrawing, startPosition, gen, balls);


		if (isDrawing) {
			sf::RectangleShape tempRectangle;
			tempRectangle.setPosition(static_cast<float>(startPosition.x), static_cast<float>(startPosition.y));
			sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
			tempRectangle.setSize(sf::Vector2f(static_cast<float>(currentMousePosition.x - startPosition.x), static_cast<float>(currentMousePosition.y - startPosition.y)));
			tempRectangle.setFillColor(sf::Color(100, 100, 100, 100));
			window.draw(tempRectangle);
		}



        float dt = clock.restart().asSeconds();



		/* FPS */
		frameCounter++;
		timeAccumulator += dt;

		if (frameCounter == 30) {
			float fps = frameCounter / timeAccumulator;
			fpsText.setString("FPS: " + std::to_string(fps));
			frameCounter = 0;
			timeAccumulator = 0.0f;
		}


		if (!isPaused) {
			calculateBallsPosition(balls, dt, obstacles, window);
		}


        window.clear();

		window.draw(fpsText);
        for (auto& ball : balls)
            ball.draw(window);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle);
        }

        window.display();
    }

    return 0;
}
