#include "scenecontroller.h"

SceneController::SceneController(RenderWindow *&window)
{
	this->window = window;
}

SceneController::~SceneController()
{
	for (auto& figure : vectorFigures)
		delete figure;

	vectorFigures.clear();
	vectorFigures.clear();
	vectorCutFigures.clear();
	vectorCopyFigures.clear();
}

void SceneController::render()
{
	handleEvents();
	window->clear();

	for (auto& figure : vectorFigures)
	{
		figure->draw(*window);
	}

	window->display();
}

void SceneController::clearSelection()
{
	for (auto& figure : vectorFigures)
	{
		figure->setOutline(0, sf::Color::Transparent);
		figure->setSelected(false);
	}
}

void SceneController::bringToFront(Figure* selectedFigure)
{
	if (selectedFigure != nullptr)
	{
		for (auto iter = vectorFigures.begin(); iter != vectorFigures.end(); ++iter)
		{
			if (*iter == selectedFigure)
			{
				vectorFigures.erase(iter);
				break;
			}
		}
		vectorFigures.push_back(selectedFigure);
	}
}

void SceneController::handleMousePress()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

		bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

		if (ctrlPressed)
		{
			bool found = false;
			for (auto& figure : vectorFigures)
			{
				if (figure->getGlobalBounds().contains(mousePos))
				{
					found = true;
					figure->setSelected(!figure->getSelected());
				}
			}

			if (!found)
			{
				clearSelection();
			}
		}
		else
		{
			Figure* selectedFigure = nullptr;

			for (auto& figure : vectorFigures)
			{
				if (figure->getGlobalBounds().contains(mousePos))
				{
					selectedFigure = figure;
					break;
				}

				Composite* compositeFigure = dynamic_cast<Composite*>(figure);

				if (compositeFigure != nullptr && compositeFigure->containsPoint(mousePos))
				{
					selectedFigure = figure;
					break;
				}

				CompositeComposite* compositeCompositeFigure = dynamic_cast<CompositeComposite*>(figure);

				if (compositeCompositeFigure != nullptr && compositeCompositeFigure->containsPoint(mousePos))
				{
					selectedFigure = figure;
					break;
				}
			}

			clearSelection();

			if (selectedFigure != nullptr)
			{
				isLeftDragging = true;
				offset = mousePos - selectedFigure->getPosition();
				selectedFigure->setSelected(true);
				selectedFigure->setOutline(2, sf::Color(0, 255, 255));

				bringToFront(selectedFigure);
			}
		}

		leftClickPos = mousePos;
	}
	else if (event.mouseButton.button == sf::Mouse::Right)
	{
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

		if (!ctrlPressed)
		{
			isRightDragging = true;
			rightClickPos = mousePos;
		}
	}
}

void SceneController::handleMouseMovement()
{
	if (isLeftDragging)
	{
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

		for (auto& figure : vectorFigures)
		{
			if (figure->getSelected())
			{
				figure->move(*window, mousePos.x - offset.x - figure->getPosition().x, mousePos.y - offset.y - figure->getPosition().y);
			}
		}

		leftClickPos = mousePos;

		if (isCollisions)
			handleCollisions();
	}

	if (isRightDragging)
	{
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

		for (auto& figure : vectorFigures)
		{
			if (figure->getSelected())
			{
				figure->move(*window, mousePos.x - rightClickPos.x, mousePos.y - rightClickPos.y);
			}
		}

		rightClickPos = mousePos;

		if (isCollisions)
			handleCollisions();
	}
}

void SceneController::handleMouseRelease()
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		isLeftDragging = false;
	}
	else if (event.mouseButton.button == sf::Mouse::Right)
	{
		isRightDragging = false;
	}
}

void SceneController::handleF1Key()
{
	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			figure->setDefaultStatus(*window);
		}
	}
}

void SceneController::handleF2Key()
{
	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			if (!figure->getTrailMovement())
			{
				figure->setTrailMovement(true);
			}
			else
			{
				figure->setTrailMovement(false);
			}
		}
	}
}

void SceneController::handleF3Key()
{
	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			figure->setColor(Color());
		}
	}
}

void SceneController::handleF4Key()
{
	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			if (figure->getVisible())
			{
				figure->hide();
			}
			else
			{
				figure->show();
			}
		}
	}
}

void SceneController::handleF5Key()
{
	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			if (!figure->getAutoMove())
			{
				figure->setAutoMove(true);
			}
			else
			{
				figure->setAutoMove(false);
			}
		}
	}
}

void SceneController::handleF7Key()
{
	std::vector<Figure*> selectedFigures;

	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			selectedFigures.push_back(figure);
		}
	}

	if (!selectedFigures.empty())
	{
		Composite* composite = new Composite();

		for (auto& figure : selectedFigures)
		{
			composite->addFigure(figure);
		}

		for (auto& figure : selectedFigures)
		{
			auto it = std::find(vectorFigures.begin(), vectorFigures.end(), figure);
			if (it != vectorFigures.end())
			{
				vectorFigures.erase(it);
			}
		}

		vectorFigures.push_back(composite);
	}
}

void SceneController::handleF8Key()
{
	std::vector<Figure*> selectedFigures;

	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			selectedFigures.push_back(figure);
		}
	}

	if (!selectedFigures.empty())
	{
		CompositeComposite* compositeComposite = new CompositeComposite(); 

		for (auto& figure : selectedFigures)
		{
			Composite* compositeFigure = dynamic_cast<Composite*>(figure);
			if (compositeFigure != nullptr)
			{
				compositeComposite->addComposite(compositeFigure);
			}
		}

		vectorFigures.erase(
			std::remove_if(
				vectorFigures.begin(),
				vectorFigures.end(),
				[&selectedFigures](Figure* figure) {
			return std::find(selectedFigures.begin(), selectedFigures.end(), figure) != selectedFigures.end();
		}),
			vectorFigures.end());

		vectorFigures.push_back(compositeComposite);
	}
}

void SceneController::handleF9Key()
{
	std::vector<Figure*> individualFigures;

	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			Composite* compositeFigure = dynamic_cast<Composite*>(figure);
			if (compositeFigure != nullptr)
			{
				std::vector<Figure*> parts = compositeFigure->getFigures();
				individualFigures.insert(individualFigures.end(), parts.begin(), parts.end());
			}
			else
			{
				individualFigures.push_back(figure);
			}

			CompositeComposite* compositeCompositeFigure = dynamic_cast<CompositeComposite*>(figure);
			if (compositeCompositeFigure != nullptr)
			{
				std::vector<Composite*> subparts = compositeCompositeFigure->getCompositeFigures();
				for (auto& subpart : subparts)
				{
					std::vector<Figure*> subFigures = subpart->getFigures();
					individualFigures.insert(individualFigures.end(), subFigures.begin(), subFigures.end());
				}
			}
		}
	}

	vectorFigures.clear();
	vectorFigures = individualFigures;
}

void SceneController::handleCtrlX()
{
	vectorCutFigures.clear();

	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			vectorCutFigures.push_back(figure);
		}
	}

	for (auto& figure : vectorCutFigures)
	{
		auto it = std::find(vectorFigures.begin(), vectorFigures.end(), figure);
		if (it != vectorFigures.end())
		{
			vectorFigures.erase(it);
		}
	}
}

void SceneController::handleCtrlC()
{
	vectorCopyFigures.clear();

	for (auto& figure : vectorFigures)
	{
		if (figure->getSelected())
		{
			Figure* copy = figure->clone();
			if (copy)
				vectorCopyFigures.push_back(copy);
		}
	}
}

void SceneController::handleCtrlV()
{
	if (!vectorCutFigures.empty())
	{
		vectorFigures.insert(vectorFigures.end(), vectorCutFigures.begin(), vectorCutFigures.end());
		vectorCutFigures.clear();
	}

	if (!vectorCopyFigures.empty())
	{
		vectorFigures.insert(vectorFigures.end(), vectorCopyFigures.begin(), vectorCopyFigures.end());
		vectorCopyFigures.clear();
	}
}

void SceneController::handleDeleteKey()
{
	std::vector<Figure*> figuresToKeep;

	for (auto& figure : vectorFigures)
	{
		if (!figure->getSelected())
		{
			figuresToKeep.push_back(figure);
		}
		else
		{
			delete figure;
		}
	}

	vectorFigures.clear();

	vectorFigures = figuresToKeep;
}

void SceneController::handleCollisions()
{
	if (!isCollisions)
		return;

	for (size_t i = 0; i < vectorFigures.size(); ++i)
	{
		for (size_t j = i + 1; j < vectorFigures.size(); ++j)
		{
			if (vectorFigures[i]->getGlobalBounds().intersects(vectorFigures[j]->getGlobalBounds()))
			{
				if (vectorFigures[i]->getSelected() && dynamic_cast<Square*>(vectorFigures[j]))
				{
					dynamic_cast<Square*>(vectorFigures[j])->setSize(dynamic_cast<Square*>(vectorFigures[j])->getSize().x - 1);
				}
				else if (dynamic_cast<Square*>(vectorFigures[i]) && vectorFigures[j]->getSelected())
				{
					dynamic_cast<Square*>(vectorFigures[i])->setSize(dynamic_cast<Square*>(vectorFigures[i])->getSize().x - 1);
				}
				else if (dynamic_cast<Square*>(vectorFigures[i]) && dynamic_cast<Square*>(vectorFigures[j]))
				{
					dynamic_cast<Square*>(vectorFigures[i])->setSize(dynamic_cast<Square*>(vectorFigures[i])->getSize().x - 1);
				}

				if (vectorFigures[i]->getSelected() && dynamic_cast<Circle*>(vectorFigures[j]))
				{
					dynamic_cast<Circle*>(vectorFigures[j])->setRadius(dynamic_cast<Circle*>(vectorFigures[j])->getRadius() - 1);
				}
				else if (dynamic_cast<Circle*>(vectorFigures[i]) && vectorFigures[j]->getSelected())
				{
					dynamic_cast<Circle*>(vectorFigures[i])->setRadius(dynamic_cast<Circle*>(vectorFigures[i])->getRadius() - 1);
				}
				else if (dynamic_cast<Circle*>(vectorFigures[i]) && dynamic_cast<Circle*>(vectorFigures[j]))
				{
					dynamic_cast<Circle*>(vectorFigures[i])->setRadius(dynamic_cast<Circle*>(vectorFigures[i])->getRadius() - 0.75);
				}

				if (vectorFigures[i]->getSelected() && dynamic_cast<Triangle*>(vectorFigures[j]))
				{
					dynamic_cast<Triangle*>(vectorFigures[j])->setRadius(dynamic_cast<Triangle*>(vectorFigures[j])->getRadius() - 1);
				}
				else if (dynamic_cast<Triangle*>(vectorFigures[i]) && vectorFigures[j]->getSelected())
				{
					dynamic_cast<Triangle*>(vectorFigures[i])->setRadius(dynamic_cast<Triangle*>(vectorFigures[i])->getRadius() - 1);
				}
				else if (dynamic_cast<Triangle*>(vectorFigures[i]) && dynamic_cast<Triangle*>(vectorFigures[j]))
				{
					dynamic_cast<Triangle*>(vectorFigures[i])->setRadius(dynamic_cast<Triangle*>(vectorFigures[i])->getRadius() - 1);
				}
			}
		}
	}
}

void SceneController::handleKeyPress()
{
	if (event.key.code == sf::Keyboard::Num1 ||
		event.key.code == sf::Keyboard::Num2 ||
		event.key.code == sf::Keyboard::Num3)
	{
		if (event.key.code == sf::Keyboard::Num1)
		{
			vectorFigures.push_back(new Square(100, sf::Color::White));
		}
		else if (event.key.code == sf::Keyboard::Num2)
		{
			vectorFigures.push_back(new Circle(50, sf::Color::White));
		}
		else if (event.key.code == sf::Keyboard::Num3)
		{
			vectorFigures.push_back(new Triangle(66.6, sf::Color::White));
		}
	}
	else if (event.key.code == sf::Keyboard::F1)
	{
		handleF1Key();
	}
	else if (event.key.code == sf::Keyboard::F2)
	{
		handleF2Key();
	}
	else if (event.key.code == sf::Keyboard::F3)
	{
		handleF3Key();
	}
	else if (event.key.code == sf::Keyboard::F4)
	{
		handleF4Key();
	}
	else if (event.key.code == sf::Keyboard::F5)
	{
		handleF5Key();
	}
	else if (event.key.code == sf::Keyboard::F6)
	{
		isCollisions = !isCollisions;
	}
	else if (event.key.code == sf::Keyboard::F7)
	{
		handleF7Key();
	}
	else if (event.key.code == sf::Keyboard::F8)
	{
		handleF8Key();
	}
	else if (event.key.code == sf::Keyboard::F9)
	{
		handleF9Key();
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		handleCtrlX();
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		handleCtrlC();
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		handleCtrlV();
	}
	else if (event.key.code == sf::Keyboard::Delete)
	{
		handleDeleteKey();
	}
}

void SceneController::handleEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{

		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::MouseButtonPressed:
			handleMousePress();
			break;

		case sf::Event::MouseMoved:
			handleMouseMovement();
			break;

		case sf::Event::MouseButtonReleased:
			handleMouseRelease();
			break;

		case sf::Event::KeyPressed:
			handleKeyPress();
			break;

		default:
			break;
		}
	}
}