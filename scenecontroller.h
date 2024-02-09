#pragma once
#include "composite.h"
#include "compositecomposite.h"
#include "figure.h"
#include "circle.h"
#include "triangle.h"
#include "square.h"

class SceneController
{

private:
	sf::RenderWindow* window;
	sf::Event event;

	std::vector<Figure*> vectorFigures;
	std::vector<Figure*> vectorCutFigures;
	std::vector<Figure*> vectorCopyFigures;

	sf::Vector2f offset;
	sf::Vector2f leftClickPos;
	sf::Vector2f rightClickPos;

	bool isLeftDragging;
	bool isRightDragging;
	bool isCollisions;

	void clearSelection();
	void bringToFront(Figure* selectedFigure);
	void handleMousePress();
	void handleMouseMovement();
	void handleMouseRelease();
	void handleF1Key();
	void handleF2Key();
	void handleF3Key();
	void handleF4Key();
	void handleF5Key();
	void handleF7Key();
	void handleF8Key();
	void handleF9Key();
	void handleCtrlX();
	void handleCtrlC();
	void handleCtrlV();
	void handleDeleteKey();
	void handleCollisions();
	void handleKeyPress();
	void handleEvents();

public:
	SceneController(sf::RenderWindow*& window);
	~SceneController();
	
	void render();

};