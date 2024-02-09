#include "compositecomposite.h"

void CompositeComposite::addComposite(Composite* composite)
{
	vectorComposites.push_back(composite);
}

int CompositeComposite::getSelectedCompositesCount()
{
	int count = 0;
	for (const auto& composite : vectorComposites)
	{
		if (composite->getSelected())
		{
			++count;
		}
	}
	return count;
}

void CompositeComposite::setDefaultStatus(RenderWindow& window)
{
	for (auto& composite : vectorComposites)
	{
		composite->setDefaultStatus(window);
	}
}

void CompositeComposite::setTrailMovement(bool trailMovement)
{
	for (auto& composite : vectorComposites)
	{
		composite->setTrailMovement(trailMovement);
	}
}

bool CompositeComposite::getTrailMovement()
{
	if (!vectorComposites.empty())
	{
		return vectorComposites[0]->getTrailMovement();
	}
	return false;
}

FloatRect CompositeComposite::getGlobalBounds()
{
	FloatRect bounds;

	if (!vectorComposites.empty())
	{
		bounds = vectorComposites[0]->getGlobalBounds();
		for (size_t i = 1; i < vectorComposites.size(); ++i)
		{
			FloatRect compositeBounds = vectorComposites[i]->getGlobalBounds();
			bounds.left = std::min(bounds.left, compositeBounds.left);
			bounds.top = std::min(bounds.top, compositeBounds.top);
			float boundsRight = std::max(bounds.left + bounds.width, compositeBounds.left + compositeBounds.width);
			float boundsBottom = std::max(bounds.top + bounds.height, compositeBounds.top + compositeBounds.height);
			bounds.width = boundsRight - bounds.left;
			bounds.height = boundsBottom - bounds.top;
		}
	}
	return bounds;
}

void CompositeComposite::setScale(float scaleX, float scaleY)
{
	for (auto& composite : vectorComposites)
	{
		composite->setScale(scaleX, scaleY);
	}
}

Vector2f CompositeComposite::getPosition()
{
	if (!vectorComposites.empty())
	{
		return vectorComposites[0]->getPosition();
	}
	return Vector2f(0.f, 0.f);
}

bool CompositeComposite::getVisible()
{
	if (!vectorComposites.empty())
	{
		return vectorComposites[0]->getVisible();
	}
	return false;
}

void CompositeComposite::hide()
{
	for (auto& composite : vectorComposites)
	{
		composite->hide();
	}
}

void CompositeComposite::show()
{
	for (auto& composite : vectorComposites)
	{
		composite->show();
	}
}

void CompositeComposite::draw(RenderWindow& window)
{
	for (auto& composite : vectorComposites)
	{
		composite->draw(window);
	}
}

void CompositeComposite::setAutoMove(bool autoMove)
{
	for (auto& composite : vectorComposites)
	{
		composite->setAutoMove(autoMove);
	}
}

bool CompositeComposite::getAutoMove()
{
	if (!vectorComposites.empty())
	{
		return vectorComposites[0]->getAutoMove();
	}
	return false;
}

void CompositeComposite::move(RenderWindow& window, float offsetX, float offsetY)
{
	for (auto& composite : vectorComposites)
	{
		composite->move(window, offsetX, offsetY);
	}
}

void CompositeComposite::setColor(Color color)
{
	for (auto& composite : vectorComposites)
	{
		composite->setColor(color);
	}
}

void CompositeComposite::setOutline(float thickness, Color color)
{
	for (auto& composite : vectorComposites)
	{
		composite->setOutline(thickness, color);
	}
}

void CompositeComposite::setSelected(bool selected)
{
	for (auto& composite : vectorComposites)
	{
		composite->setSelected(selected);
	}
}

bool CompositeComposite::getSelected()
{
	if (!vectorComposites.empty())
	{
		return vectorComposites[0]->getSelected();
	}
	return false;
}

Figure* CompositeComposite::clone()
{
	CompositeComposite* newComposite = new CompositeComposite();

	for (auto& composite : vectorComposites)
	{
		Composite* clonedComposite = dynamic_cast<Composite*>(composite->clone());
		if (clonedComposite)
		{
			newComposite->addComposite(clonedComposite);
		}
		else
		{
			delete newComposite;
			return nullptr;
		}
	}

	return newComposite;
}

bool CompositeComposite::containsPoint(sf::Vector2f point)
{
	for (auto& composite : vectorComposites)
	{
		if (composite->containsPoint(point))
		{
			return true;
		}
	}

	return false;
}

std::vector<Composite*> CompositeComposite::getComposites()
{
	return vectorComposites;
}

std::vector<Composite*> CompositeComposite::getCompositeFigures()
{
	std::vector<Composite*> allCompositeFigures;

	for (auto& composite : vectorComposites)
	{
		CompositeComposite* compositeComposite = dynamic_cast<CompositeComposite*>(composite);
		if (compositeComposite != nullptr)
		{
			std::vector<Composite*> subCompositeFigures = compositeComposite->getCompositeFigures();
			allCompositeFigures.insert(allCompositeFigures.end(), subCompositeFigures.begin(), subCompositeFigures.end());
		}
		else
		{
			allCompositeFigures.push_back(composite);
		}
	}

	return allCompositeFigures;
}