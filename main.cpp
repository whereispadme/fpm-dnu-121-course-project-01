#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
#include <Windows.h>
using namespace std;

#include "scenecontroller.h"
#include "figure.h"
#include "circle.h"
#include "triangle.h"
#include "square.h"

void displayConsoleMenu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle("Керівництво користувача");

	auto printHorizontalLine = []()
	{
		std::cout << "+----------------------------------------+" << std::endl;
	};

	printHorizontalLine();
	std::cout << "|              Меню вибору               |" << std::endl;
	printHorizontalLine();
	std::cout << "| 1 - Квадрат                            |" << std::endl;
	std::cout << "| 2 - Круг                               |" << std::endl;
	std::cout << "| 3 - Трикутник                          |" << std::endl;
	printHorizontalLine();
	std::cout << "|              Функціонал                |" << std::endl;
	printHorizontalLine();
	std::cout << "| F1 - Відновлення початкового стану     |" << std::endl;
	std::cout << "| F2 - Переміщення зі слідом/без         |" << std::endl;
	std::cout << "| F3 - Зміна кольору                     |" << std::endl;
	std::cout << "| F4 - Зміна стану видимий/невидимий     |" << std::endl;
	std::cout << "| F5 - Рух об’єкта в автоматичному режимі|" << std::endl;
	std::cout << "|      по запам’ятованій траєкторії      |" << std::endl;
	std::cout << "| F6 - Вкл/викл деформацію об'єктів      |" << std::endl;
	std::cout << "| F7 - Сформувати агрегат                |" << std::endl;
	std::cout << "| F8 - Сформувати агрегат агрегатів      |" << std::endl;
	std::cout << "| F9 - Розформувати об'єкт               |" << std::endl;
	printHorizontalLine();
	std::cout << "|             Додаткові функції          |" << std::endl;
	printHorizontalLine();
	std::cout << "| Ctrl + X          - Вирізати           |" << std::endl;
	std::cout << "| Ctrl + C          - Скопіювати         |" << std::endl;
	std::cout << "| Ctrl + V          - Вставити           |" << std::endl;
	std::cout << "| DEL               - Видалити           |" << std::endl;
	std::cout << "| Hold Ctrl + Click - Виділення об'єктів |" << std::endl;
	printHorizontalLine();

	_CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

int main()
{
	displayConsoleMenu();

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow *window = new RenderWindow(sf::VideoMode(1280, 960), sf::String(L"КущевськийАндрій, ПЗ-23у-1 | lab04"), sf::Style::Titlebar | sf::Style::Close, settings);
	SceneController *sceneController = new SceneController(window);

	while (window->isOpen())
	{
		sceneController->render();
	}

	return 0;
}