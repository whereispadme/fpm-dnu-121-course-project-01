#include "composite.h"

void Composite::addFigure(Figure* figure)
{
	vectorFigures.push_back(figure);
}

int Composite::getSelectedFiguresCount()
{
	int count = 0;
	for (const auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			++count;
		}
	}
	return count;
}

void Composite::setDefaultStatus(RenderWindow& window)
{
	for (auto& figure : vectorFigures)
	{
		figure->setDefaultStatus(window);
	}
}

void Composite::setTrailMovement(bool trailMovement)
{
	for (auto& figure : vectorFigures)
	{
		figure->setTrailMovement(trailMovement);
	}
}

bool Composite::getTrailMovement()
{
	if (!vectorFigures.empty())
	{
		return vectorFigures[0]->getTrailMovement();
	}
	return false;
}

FloatRect Composite::getGlobalBounds()
{
	FloatRect bounds;
	if (!vectorFigures.empty())
	{
		bounds = vectorFigures[0]->getGlobalBounds();
		for (size_t i = 1; i < vectorFigures.size(); ++i)
		{
			FloatRect figureBounds = vectorFigures[i]->getGlobalBounds();
			bounds.left = std::min(bounds.left, figureBounds.left);
			bounds.top = std::min(bounds.top, figureBounds.top);
			float boundsRight = std::max(bounds.left + bounds.width, figureBounds.left + figureBounds.width);
			float boundsBottom = std::max(bounds.top + bounds.height, figureBounds.top + figureBounds.height);
			bounds.width = boundsRight - bounds.left;
			bounds.height = boundsBottom - bounds.top;
		}
	}
	return bounds;
}

void Composite::setScale(float scaleX, float scaleY)
{
	for (auto& figure : vectorFigures)
	{
		figure->setScale(scaleX, scaleY);
	}
}

Vector2f Composite::getPosition()
{
	if (!vectorFigures.empty())
	{
		return vectorFigures[0]->getPosition();
	}
	return Vector2f(0.f, 0.f);
}

bool Composite::getVisible()
{
	if (!vectorFigures.empty())
	{
		return vectorFigures[0]->getVisible();
	}

	return false;
}

void Composite::hide()
{
	for (auto& figure : vectorFigures)
	{
		figure->hide();
	}
}

void Composite::show()
{
	for (auto& figure : vectorFigures)
	{
		figure->show();
	}
}

void Composite::draw(RenderWindow& window)
{
	for (auto& figure : vectorFigures)
	{
		figure->draw(window);
	}
}

void Composite::setAutoMove(bool autoMove)
{
	for (auto& figure : vectorFigures)
	{
		figure->setAutoMove(autoMove);
	}
}

bool Composite::getAutoMove()
{
	if (!vectorFigures.empty())
	{
		return vectorFigures[0]->getAutoMove();
	}

	return false;
}

void Composite::move(RenderWindow& window, float offsetX, float offsetY)
{
	for (auto& figure : vectorFigures)
	{
		figure->move(window, offsetX, offsetY);
	}
}

void Composite::setColor(Color color)
{
	for (auto& figure : vectorFigures)
	{
		figure->setColor(color);
	}
}

void Composite::setOutline(float thickness, Color color)
{
	for (auto& figure : vectorFigures)
	{
		figure->setOutline(thickness, color);
	}
}

void Composite::setSelected(bool selected)
{
	for (auto& figure : vectorFigures)
	{
		figure->setSelected(selected);
	}
}

bool Composite::getSelected()
{
	if (!vectorFigures.empty())
	{
		return vectorFigures[0]->getSelected();
	}
	return false;
}

Figure* Composite::clone()
{
	Composite* newComposite = new Composite();

	for (auto& figure : vectorFigures)
	{
		Figure* figureCopy = figure->clone();
		if (figureCopy)
		{
			newComposite->addFigure(figureCopy);
		}
		else
		{
			delete newComposite;
			return nullptr;
		}
	}

	return newComposite;
}

bool Composite::containsPoint(sf::Vector2f point)
{
	for (auto& figure : vectorFigures)
	{
		if (figure->getGlobalBounds().contains(point))
		{
			return true;
		}
	}

	return false;
}

std::vector<Figure*> Composite::getFigures()
{
	return vectorFigures;
}