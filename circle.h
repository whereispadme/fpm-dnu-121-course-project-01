#pragma once
#include "figure.h"

using namespace sf;

class Circle : public Figure
{

private:
	CircleShape circle;
	std::vector<Vector2f> positions;

public:
	Circle(float radius);
	Circle(float radius, Color color);

	void setDefaultStatus(RenderWindow& window);
	void setTrailMovement(bool move) override;
	bool getTrailMovement() override;
	FloatRect getGlobalBounds() override;
	void setScale(float x, float y) override;
	void setRadius(float radius);
	float getRadius();
	Vector2f getPosition() override;
	bool getVisible() override;
	void hide() override;
	void show() override;
	void draw(RenderWindow& window) override;
	void setAutoMove(bool isAutoMove) override;
	bool getAutoMove() override;
	void move(RenderWindow& window, float x, float y) override;
	void setColor(Color color) override;
	void setOutline(float thickness, Color color) override;
	void setSelected(bool isSelected) override;
	bool getSelected() override;
	Figure* clone() override;

};
