#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 800

using namespace std;

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "String Art", sf::Style::Default, settings);
	
	sf::CircleShape circle(350);
	circle.setFillColor(sf::Color::White);
	circle.setPointCount(100);

	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(10, 10)),
		sf::Vertex(sf::Vector2f(150, 150))
	};

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) 
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();
		window.draw(circle);
		window.draw(line, 2, sf::Lines);
		window.display();
	}

	return 0;
}