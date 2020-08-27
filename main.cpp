#include <cmath>
#include <iostream>

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

void drawImage(sf::RenderWindow& window) {
	sf::Image image;
	
	if (!image.loadFromFile("dog.jpg"))
		cerr << "Couldn't read image";

	sf::Texture texture;
	texture.loadFromImage(image);  //Load Texture from image

	sf::Sprite sprite;
	sprite.setTexture(texture);

	window.draw(sprite);
}

vector<sf::Vector2f> getPixelsInLine(sf::Vector2f& startCoordinates, sf::Vector2f& endCoordinates) {
	bool steep = false;
	float x0 = startCoordinates.x;
	float y0 = startCoordinates.y;
	float x1 = endCoordinates.x;
	float y1 = endCoordinates.y;

	vector<sf::Vector2f> pixels;
	
	if (abs(x0 - x1) < abs(y0 - y1)) {
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}
	
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			pixels.push_back(sf::Vector2f(y, x));
		}

		else {
			pixels.push_back(sf::Vector2f(x, y));
		}
		
		error2 += derror2;
		
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}

	return pixels;
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

	sf::Image image;

	if (!image.loadFromFile("dog.jpg"))
		cerr << "Couldn't read image";

	sf::Texture texture;
	texture.loadFromImage(image);  //Load Texture from image

	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) 
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();
		window.draw(circle);
		window.draw(sprite);
		
		for (int i = 0; i < 100; i++)
			drawPoint(window, points[i]);

		int choosenPoint = 0;

		// Number of strings
		for (int i = 0; i < 10; i++) {
			// Iterate over every point to see where to connect the string to
			for (int j = 0; j < 100; j++) {
				vector<sf::Vector2f> pixels = getPixelsInLine(points[choosenPoint], points[j]);
				
				for (sf::Vector2f pixel : pixels) {
					image.getPixel(pixel.x, pixel.y).toInteger();
				}
			}
		}

		window.display();
	}

	return 0;
}

