#include "Square.h"

Square::Square(float side)
{
	square = RectangleShape(Vector2f(side, side));

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

Square::Square(float side, Color color)
{
	square = RectangleShape(Vector2f(side, side));
	square.setFillColor(color);

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

void Square::setDefaultStatus(RenderWindow& window)
{
	square.setSize(Vector2f(100, 100));
	square.setFillColor(sf::Color::White);

	positions.clear();

	isSelected = false;
	isTrailMovement = false;
	isVisible = false;
	isAutoMove = false;
}

void Square::setTrailMovement(bool move)
{
	trailBubble.clear();
	isTrailMovement = move;
}

bool Square::getTrailMovement()
{
	return isTrailMovement;
}

FloatRect Square::getGlobalBounds()
{
	return square.getGlobalBounds();
}

void Square::setScale(float x, float y)
{
	square.setScale(x, y);
}

void Square::setSize(float side)
{
	square.setSize(Vector2f(side, side));
}

Vector2f Square::getSize()
{
	return square.getSize();
}

Vector2f Square::getPosition()
{
	return square.getPosition();
}

bool Square::getVisible()
{
	return isVisible;
}

void Square::hide()
{
	isVisible = false;
	square.setFillColor(sf::Color::Transparent);
}

void Square::show()
{
	isVisible = true;
	square.setFillColor(colors[currentColorIndex]);
}

void Square::draw(RenderWindow& window)
{
	FloatRect bounds = square.getGlobalBounds();
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
			square.setPosition(positions[0]);
			currentPositiontIndex = (currentPositiontIndex + 1) % positions.size();
		}
		else
		{
			square.setPosition(positions[currentPositiontIndex]);
			currentPositiontIndex = (currentPositiontIndex + 1) % positions.size();
		}

		sf::sleep(sf::milliseconds(20));
	}

	window.draw(square);
}

void Square::setAutoMove(bool isAutoMove)
{
	this->isAutoMove = isAutoMove;
}

bool Square::getAutoMove()
{
	return this->isAutoMove;
}

void Square::move(RenderWindow& window, float x, float y)
{
	FloatRect bounds = square.getGlobalBounds();
	Vector2f center(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	if (bounds.left + x >= 0 &&
		bounds.left + bounds.width + x <= window.getSize().x &&
		bounds.top + y >= 0 &&
		bounds.top + bounds.height + y <= window.getSize().y)
	{
		square.move(x, y);
	}
	else
	{
		if (x > 0)
		{
			if (bounds.left + bounds.width + x > window.getSize().x)
			{
				square.setPosition(window.getSize().x - bounds.width, square.getPosition().y);
			}
			else
			{
				square.move(x, 0);
			}
		}
		else if (x < 0)
		{
			if (bounds.left + x < 0)
			{
				square.setPosition(0, square.getPosition().y);
			}
			else
			{
				square.move(x, 0);
			}
		}

		if (y > 0)
		{
			if (bounds.top + bounds.height + y > window.getSize().y)
			{
				square.setPosition(square.getPosition().x, window.getSize().y - bounds.height);
			}
			else
			{
				square.move(0, y);
			}
		}
		else if (y < 0)
		{
			if (bounds.top + y < 0)
			{
				square.setPosition(square.getPosition().x, 0);
			}
			else
			{
				square.move(0, y);
			}
		}
	}

	positions.push_back(square.getPosition());

	if (positions.size() > 500)
	{
		positions.erase(positions.begin());
	}
}

void Square::setColor(Color color)
{
	currentColorIndex = (currentColorIndex + 1) % colors.size();
	square.setFillColor(colors[currentColorIndex]);
}

void Square::setOutline(float thickness, Color color)
{
	square.setOutlineThickness(thickness);
	square.setOutlineColor(color);
}

void Square::setSelected(bool isSelected)
{
	if (isSelected)
		setOutline(2, sf::Color(0, 255, 255));
	else
		setOutline(0, sf::Color::Transparent);

	this->isSelected = isSelected;
}

bool Square::getSelected()
{
	return this->isSelected;
}

Figure * Square::clone()
{
	return new Square(*this);
}
