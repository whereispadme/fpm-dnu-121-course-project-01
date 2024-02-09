#include "Circle.h"

Circle::Circle(float radius)
{
	circle = CircleShape(radius);

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

Circle::Circle(float radius, Color color)
{
	circle = CircleShape(radius);
	circle.setFillColor(color);

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

void Circle::setDefaultStatus(RenderWindow& window)
{
	circle.setRadius(50);
	circle.setFillColor(sf::Color::White);

	positions.clear();

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

void Circle::setTrailMovement(bool move)
{
	trailBubble.clear();
	isTrailMovement = move;
}

bool Circle::getTrailMovement()
{
	return isTrailMovement;
}

FloatRect Circle::getGlobalBounds()
{
	return circle.getGlobalBounds();
}

void Circle::setScale(float x, float y)
{
	circle.setScale(x, y);
}

void Circle::setRadius(float radius)
{
	circle.setRadius(radius);
}

float Circle::getRadius()
{
	return circle.getRadius();
}

Vector2f Circle::getPosition()
{
	return circle.getPosition();
}

bool Circle::getVisible()
{
	return isVisible;
}

void Circle::hide()
{
	isVisible = false;
	circle.setFillColor(Color::Transparent);
}

void Circle::show()
{
	isVisible = true;
	circle.setFillColor(colors[currentColorIndex]);
}

void Circle::draw(RenderWindow& window)
{
	FloatRect bounds = circle.getGlobalBounds();
	Vector2f center(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	static int moveCounter = 0;

	if (isTrailMovement)
	{
		if (moveCounter >= 17)
		{
			trailBubble.emplace_back(TrailBubble(center, sf::Color(0, 255, 255)));
			moveCounter = 0;
		}

		moveCounter++;

		for (size_t i = 0; i < trailBubble.size(); ++i)
		{
			trailBubble[i].update();
			trailBubble[i].draw(window);

			if (!trailBubble[i].isActive())
			{
				trailBubble.erase(trailBubble.begin() + i);
			}
		}
	}

	if (isAutoMove)
	{
		if (currentPositiontIndex == 0)
		{
			circle.setPosition(positions[0]);
			currentPositiontIndex = (currentPositiontIndex + 1) % positions.size();
		}
		else
		{
			circle.setPosition(positions[currentPositiontIndex]);
			currentPositiontIndex = (currentPositiontIndex + 1) % positions.size();
		}

		sf::sleep(sf::milliseconds(20));
	}

	window.draw(circle);
}

void Circle::setAutoMove(bool isAutoMove)
{
	this->isAutoMove = isAutoMove;
}

bool Circle::getAutoMove()
{
	return this->isAutoMove;
}

void Circle::move(RenderWindow& window, float x, float y)
{
	FloatRect bounds = circle.getGlobalBounds();
	Vector2f center(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	if (bounds.left + x >= 0 &&
		bounds.left + bounds.width + x <= window.getSize().x &&
		bounds.top + y >= 0 &&
		bounds.top + bounds.height + y <= window.getSize().y)
	{
		circle.move(x, y);
	}
	else
	{
		if (x > 0)
		{
			if (bounds.left + bounds.width + x > window.getSize().x)
			{
				circle.setPosition(window.getSize().x - bounds.width, circle.getPosition().y);
			}
			else
			{
				circle.move(x, 0);
			}
		}
		else if (x < 0)
		{
			if (bounds.left + x < 0)
			{
				circle.setPosition(0, circle.getPosition().y);
			}
			else
			{
				circle.move(x, 0);
			}
		}

		if (y > 0)
		{
			if (bounds.top + bounds.height + y > window.getSize().y)
			{
				circle.setPosition(circle.getPosition().x, window.getSize().y - bounds.height);
			}
			else
			{
				circle.move(0, y);
			}
		}
		else if (y < 0)
		{
			if (bounds.top + y < 0)
			{
				circle.setPosition(circle.getPosition().x, 0);
			}
			else
			{
				circle.move(0, y);
			}
		}
	}

	positions.push_back(circle.getPosition());

	if (positions.size() > 500)
	{
		positions.erase(positions.begin());
	}
}

void Circle::setColor(Color color)
{
	currentColorIndex = (currentColorIndex + 1) % colors.size();
	circle.setFillColor(colors[currentColorIndex]);
}

void Circle::setOutline(float thickness, Color color)
{
	circle.setOutlineThickness(thickness);
	circle.setOutlineColor(color);
}

void Circle::setSelected(bool isSelected)
{
	if (isSelected)
		setOutline(2, sf::Color(0, 255, 255));
	else
		setOutline(0, sf::Color::Transparent);

	this->isSelected = isSelected;
}

bool Circle::getSelected()
{
	return this->isSelected;
}

Figure * Circle::clone()
{
	return new Circle(*this);
}