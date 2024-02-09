#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

#include "trailbubble.h"

class Figure
{

protected:
	std::vector<TrailBubble> trailBubble;
	std::vector<Vector2f> positions;

	std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, sf::Color(255, 165, 0) };

	int currentColorIndex = 0;
	int currentPositiontIndex = 0;

	bool isSelected;
	bool isTrailMovement;
	bool isVisible;
	bool isAutoMove;

public:
	virtual void setDefaultStatus(RenderWindow&) = 0;
	virtual void setTrailMovement(bool) = 0;
	virtual bool getTrailMovement() = 0;
	virtual FloatRect getGlobalBounds() = 0;
	virtual void setScale(float, float) = 0;
	virtual Vector2f getPosition() = 0;
	virtual bool getVisible() = 0;
	virtual void hide() = 0;
	virtual void show() = 0;
	virtual void draw(RenderWindow&) = 0;
	virtual void setAutoMove(bool) = 0;
	virtual bool getAutoMove() = 0;
	virtual void move(RenderWindow&, float, float) = 0;
	virtual void setColor(Color) = 0;
	virtual void setOutline(float, Color) = 0;
	virtual void setSelected(bool) = 0;
	virtual bool getSelected() = 0;
	virtual Figure* clone() = 0;

};