#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class TrailBubble
{

private:
	sf::CircleShape bubble;
	int lifetime;
	bool active;

public:
	TrailBubble(sf::Vector2f position, sf::Color color);

	void update();
	bool isActive();
	void draw(sf::RenderWindow& window);

};
