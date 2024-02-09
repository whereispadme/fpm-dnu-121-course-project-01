#pragma once
#include "figure.h"

class Triangle : public Figure
{

private:
	sf::CircleShape triangle;

public:
	Triangle(float radius, sf::Color color);

	void setDefaultStatus(sf::RenderWindow& window);
	void setTrailMovement(bool move);
	bool getTrailMovement();
	sf::FloatRect getGlobalBounds();
	void setScale(float x, float y);
	void setRadius(float radius);
	float getRadius();
	sf::Vector2f getPosition();
	bool getVisible();
	void hide();
	void show();
	void draw(sf::RenderWindow& window);
	void setAutoMove(bool isAutoMove);
	bool getAutoMove();
	void move(sf::RenderWindow& window, float x, float y);
	void setColor(sf::Color color);
	void setOutline(float thickness, sf::Color color);
	void setSelected(bool isSelected);
	bool getSelected();
	Figure* clone();

};
