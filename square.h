#pragma once
#include "figure.h"

class Square : public Figure
{

private:
	RectangleShape square;

public:
	Square(float side);
	Square(float side, Color color);

	void setDefaultStatus(RenderWindow& window);
	void setTrailMovement(bool move) override;
	bool getTrailMovement() override;
	FloatRect getGlobalBounds() override;
	void setScale(float x, float y) override;
	void setSize(float side);
	Vector2f getSize();
	Vector2f getPosition() override;
	bool getVisible() override;
	void hide();
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