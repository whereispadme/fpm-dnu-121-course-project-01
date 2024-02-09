#pragma once
#include "Figure.h"

class Composite : public Figure
{

private:
	std::vector<Figure*> vectorFigures;

public:
	void addFigure(Figure* figure);
	int getSelectedFiguresCount();
	void setDefaultStatus(RenderWindow& window) override;
	void setTrailMovement(bool trailMovement) override;
	bool getTrailMovement() override;
	FloatRect getGlobalBounds() override;
	void setScale(float scaleX, float scaleY) override;
	Vector2f getPosition() override;
	bool getVisible() override;
	void hide() override;
	void show() override;
	void draw(RenderWindow& window) override;
	void setAutoMove(bool autoMove) override;
	bool getAutoMove() override;
	void move(RenderWindow& window, float offsetX, float offsetY) override;
	void setColor(Color color) override;
	void setOutline(float thickness, Color color) override;
	void setSelected(bool selected) override;
	bool getSelected() override;
	Figure* clone() override;
	bool containsPoint(sf::Vector2f point);
	std::vector<Figure*> getFigures();

};