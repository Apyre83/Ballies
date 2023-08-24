#include "Ballies.h"

float TIME_FACTOR = 5.0f;
float BOUNCE = 0.7f;
float GRAVITY = 2.0f;

void	calculateBallsPosition(std::vector<Ball>& balls, float dt, std::vector<sf::RectangleShape>& obstacles, sf::RenderWindow& window, unsigned int &lastBallNumber)
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
			ball.calculateVelocity(obstacles, window, lastBallNumber);
			ball.update(dt);
		}
	}
}


void	drawArrow(sf::RenderWindow& window, sf::RectangleShape& arrowShaft, sf::ConvexShape& arrowHead)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f arrowShaftSize = arrowShaft.getSize();
	sf::Vector2f arrowHeadSize = arrowHead.getPoint(1) - arrowHead.getPoint(0);

	arrowShaft.setPosition({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) });
	arrowShaft.setRotation(sf::Angle(0));
	arrowShaft.setFillColor(sf::Color::White);

	arrowHead.setPosition({ static_cast<float>(mousePos.x + arrowShaftSize.x), static_cast<float>(mousePos.y + arrowShaftSize.y / 2 - arrowHeadSize.y / 2) });
	arrowHead.setRotation(sf::Angle(0));
	arrowHead.setFillColor(sf::Color::White);

	window.draw(arrowShaft);
	window.draw(arrowHead);
}


void	handleEvents(sf::RenderWindow& window, bool& isPaused, std::vector<sf::RectangleShape>& obstacles, bool& isDrawing, sf::Vector2i& startPosition, std::vector<Ball>& balls, bool &raceMode, unsigned int &lastBallNumber) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            isPaused = false;
			lastBallNumber = 1;
            initializeGame(window, balls, raceMode);
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
            rectangle.setPosition({ static_cast<float>(startPosition.x), static_cast<float>(startPosition.y) });
            rectangle.setSize(sf::Vector2f(length, RECTANGLE_WIDTH));
            rectangle.setOrigin({ 0, RECTANGLE_WIDTH / 2 });
            rectangle.setRotation(sf::Angle(rotation));
            rectangle.setFillColor(sf::Color::Blue);

            obstacles.push_back(rectangle);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
            obstacles.clear();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            isPaused = !isPaused;
        }
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
			raceMode = !raceMode;
			isPaused = false;
			lastBallNumber = 1;
			initializeGame(window, balls, raceMode);
		}

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
            TIME_FACTOR += 0.5f;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
            if (TIME_FACTOR > 0.5f)
            TIME_FACTOR -= 0.5f;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
            BOUNCE += 0.01f;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
            if (BOUNCE > 0.01f)
            BOUNCE -= 0.01f;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num5) {
            GRAVITY += 0.1f;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num6) {
            if (GRAVITY > 0.1f)
            GRAVITY -= 0.1f;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
            TIME_FACTOR = 5.0f;
            BOUNCE = 0.7f;
            GRAVITY = 2.0f;
        }
    }
}

#include <unistd.h>

int main(void) {

	Ball::loadFont("res/race.ttf");

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Ballies", sf::Style::Fullscreen);

    std::vector<sf::RectangleShape> obstacles = parseConfFile("conf");
    std::vector<Ball> balls;
	

	sf::RectangleShape arrowShaft;
	arrowShaft.setSize(sf::Vector2f(100, 10));

	sf::ConvexShape arrowHead;
	arrowHead.setPointCount(3);
	arrowHead.setPoint(0, sf::Vector2f(0, 0));
	arrowHead.setPoint(1, sf::Vector2f(30, 10));
	arrowHead.setPoint(2, sf::Vector2f(0, 20));


    sf::Clock clock;


	bool			isDrawing = false;
	bool			isPaused = false;
	unsigned int	lastBallNumber = 1;


	sf::Vector2i startPosition;
	

	sf::Font font;
	if (!font.loadFromFile("res/O4B.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
		return 1;
	}

	int		frameCounter = 0;
	float	timeAccumulator = 0.0f;

	sf::Text fpsText(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition({ 10, 10 });


	bool	raceMode = false;
	sf::Text raceModeText(font);
	raceModeText.setCharacterSize(24);
	raceModeText.setFillColor(sf::Color::White);
	raceModeText.setPosition({ 10, 40 });

    sf::Text    settingsText(font);
    settingsText.setCharacterSize(24);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition({ 10, 1000 });

    sf::Text    keysText(font, "R: Reset\nD: Delete all obstacles\nSpace: Pause\nM: Switch mode\nQ: Reset settings\nEsc: Quit\n'1': Increase time factor\n'2': Decrease time factor\n'3': Increase bounce\n'4': Decrease bounce\n'5': Increase gravity\n'6': Decrease gravity", 24);
    keysText.setFillColor(sf::Color::White);
    keysText.setPosition({ 10, 100 });


    initializeGame(window, balls, raceMode);


    while (window.isOpen()) {

        handleEvents(window, isPaused, obstacles, isDrawing, startPosition, balls, raceMode, lastBallNumber);


		if (isDrawing) {
			sf::RectangleShape tempRectangle;
			tempRectangle.setPosition({ static_cast<float>(startPosition.x), static_cast<float>(startPosition.y) });
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
			calculateBallsPosition(balls, dt, obstacles, window, lastBallNumber);
		}

        window.clear();


		if (raceMode == true)
			raceModeText.setString("MODE: Race");
		else
			raceModeText.setString("MODE: Sandbox");


        settingsText.setString("TIME_FACTOR: " + std::to_string(TIME_FACTOR) + "\nBOUNCE: " + std::to_string(BOUNCE) + "\nGRAVITY: " + std::to_string(GRAVITY));

        window.draw(keysText);
		window.draw(raceModeText);
		window.draw(fpsText);
        window.draw(settingsText);

        for (auto& ball : balls)
            ball.draw(window);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle);
        }

		//drawArrow(window, arrowShaft, arrowHead);

        window.display();

    }

    return 0;
}
