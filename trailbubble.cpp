#include "trailbubble.h"

TrailBubble::TrailBubble(Vector2f position, Color color)
{
	bubble = CircleShape(5);
	bubble.setPosition(position);
	bubble.setFillColor(color);
	lifetime = 6500;
	active = true;
}

void TrailBubble::update()
{
	if (active)
	{
		lifetime -= 5;

		if (lifetime <= 0)
		{
			active = false;
		}
	}
}

bool TrailBubble::isActive()
{
	return active;
}

void TrailBubble::draw(RenderWindow& window)
{
	if (active)
	{
		bubble.setFillColor(Color(bubble.getFillColor().r, bubble.getFillColor().g, bubble.getFillColor().b, lifetime));
		window.draw(bubble);
	}
}
