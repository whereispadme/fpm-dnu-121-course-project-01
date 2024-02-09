#include "triangle.h"

Triangle::Triangle(float radius, Color color)
{
	triangle = CircleShape(radius, 3);
	triangle.setFillColor(color);

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

void Triangle::setDefaultStatus(RenderWindow& window)
{
	triangle.setRadius(66.6);
	triangle.setFillColor(sf::Color::White);

	positions.clear();

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

void Triangle::setTrailMovement(bool move)
{
	trailBubble.clear();
	isTrailMovement = move;
}

bool Triangle::getTrailMovement()
{
	return isTrailMovement;
}

FloatRect Triangle::getGlobalBounds()
{
	return triangle.getGlobalBounds();
}

void Triangle::setScale(float x, float y)
{
	triangle.setScale(x, y);
}

void Triangle::setRadius(float radius)
{
	triangle.setRadius(radius);
}

float Triangle::getRadius()
{
	return triangle.getRadius();
}

Vector2f Triangle::getPosition()
{
	return triangle.getPosition();
}

bool Triangle::getVisible()
{
	return isVisible;
}

void Triangle::hide()
{
	isVisible = false;
	triangle.setFillColor(Color::Transparent);
}

void Triangle::show()
{
	isVisible = true;
	triangle.setFillColor(colors[currentColorIndex]);
}

void Triangle::draw(RenderWindow& window)
{
	FloatRect bounds = triangle.getGlobalBounds();
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
			triangle.setPosition(positions[0]);
			currentPositiontIndex = (currentPositiontIndex + 1) % positions.size();
		}
		else
		{
			triangle.setPosition(positions[currentPositiontIndex]);
			currentPositiontIndex = (currentPositiontIndex + 1) % positions.size();
		}

		sf::sleep(sf::milliseconds(20));
	}

	window.draw(triangle);
}

void Triangle::setAutoMove(bool isAutoMove)
{
	this->isAutoMove = isAutoMove;
}

bool Triangle::getAutoMove()
{
	return this->isAutoMove;
}

void Triangle::move(RenderWindow& window, float x, float y)
{
	FloatRect bounds = triangle.getGlobalBounds();
	Vector2f center(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	if (bounds.left + x >= 0 &&
		bounds.left + bounds.width + x <= window.getSize().x &&
		bounds.top + y >= 0 &&
		bounds.top + bounds.height + y <= window.getSize().y)
	{
		triangle.move(x, y);
	}
	else
	{
		if (x > 0)
		{
			if (bounds.left + bounds.width + x > window.getSize().x)
			{
				triangle.setPosition(window.getSize().x - bounds.width, triangle.getPosition().y);
			}
			else
			{
				triangle.move(x, 0);
			}
		}
		else if (x < 0)
		{
			if (bounds.left + x < 0)
			{
				triangle.setPosition(0, triangle.getPosition().y);
			}
			else
			{
				triangle.move(x, 0);
			}
		}

		if (y > 0)
		{
			if (bounds.top + bounds.height + y > window.getSize().y)
			{
				triangle.setPosition(triangle.getPosition().x, window.getSize().y - bounds.height);
			}
			else
			{
				triangle.move(0, y);
			}
		}
		else if (y < 0)
		{
			if (bounds.top + y < 0)
			{
				triangle.setPosition(triangle.getPosition().x, 0);
			}
			else
			{
				triangle.move(0, y);
			}
		}
	}

	positions.push_back(triangle.getPosition());

	if (positions.size() > 500)
	{
		positions.erase(positions.begin());
	}
}

void Triangle::setColor(Color color)
{
	currentColorIndex = (currentColorIndex + 1) % colors.size();
	triangle.setFillColor(colors[currentColorIndex]);
}

void Triangle::setOutline(float thickness, Color color)
{
	triangle.setOutlineThickness(thickness);
	triangle.setOutlineColor(color);
}

void Triangle::setSelected(bool isSelected)
{
	if (isSelected)
		setOutline(2, sf::Color(0, 255, 255));
	else
		setOutline(0, sf::Color::Transparent);

	this->isSelected = isSelected;
}

bool Triangle::getSelected()
{
	return this->isSelected;
}

Figure * Triangle::clone()
{
	return new Triangle(*this);
}
