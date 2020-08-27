#include <cmath>
#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 800

#define PI 3.14159265

using namespace std;

sf::Vector2f* generatePoints(int n, float radius) {
	sf::Vector2f* points = new sf::Vector2f[n];
	const float divisionAngle = 2 * PI / n;

	for (int i = 0; i < n; i++) {
		float currentAngle = divisionAngle * i;

		points[i] = sf::Vector2f(cos(currentAngle) * radius + 400, sin(currentAngle) * radius + 400);
	}

	return points;
}

void drawPoint(sf::RenderWindow &window, sf::Vector2f &coordinates) {
	sf::CircleShape point(5);
	point.setFillColor(sf::Color::White);
	point.setPosition(coordinates.x - point.getRadius(), coordinates.y - point.getRadius());
	window.draw(point);
}

void drawLine(sf::RenderWindow &window, sf::Vector2f &startCoordinates, sf::Vector2f &endCoordinates) {
	sf::Vertex line[] = {
		sf::Vertex(startCoordinates),
		sf::Vertex(endCoordinates)
	};

	window.draw(line, 2, sf::Lines);
}

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "String Art", sf::Style::Default, settings);
	
	sf::CircleShape circle(350);
	circle.setFillColor(sf::Color::Red);
	circle.setPointCount(100);
	circle.setPosition(400.f - circle.getRadius(), 400.f - circle.getRadius());

	sf::Vector2f* points = generatePoints(100, 350);

	

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) 
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();
		window.draw(circle);
		
		for (int i = 0; i < 100; i++)
			drawPoint(window, points[i]);

		for (int i = 0; i < 50; i++) {
			drawLine(window, points[i], points[i + 40]);
		}

		window.display();
	}

	return 0;
}



