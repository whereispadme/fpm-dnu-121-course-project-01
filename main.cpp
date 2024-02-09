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
	SetConsoleTitle("���������� �����������");

	auto printHorizontalLine = []()
	{
		std::cout << "+----------------------------------------+" << std::endl;
	};

	printHorizontalLine();
	std::cout << "|              ���� ������               |" << std::endl;
	printHorizontalLine();
	std::cout << "| 1 - �������                            |" << std::endl;
	std::cout << "| 2 - ����                               |" << std::endl;
	std::cout << "| 3 - ���������                          |" << std::endl;
	printHorizontalLine();
	std::cout << "|              ����������                |" << std::endl;
	printHorizontalLine();
	std::cout << "| F1 - ³��������� ����������� �����     |" << std::endl;
	std::cout << "| F2 - ���������� � �����/���         |" << std::endl;
	std::cout << "| F3 - ���� �������                     |" << std::endl;
	std::cout << "| F4 - ���� ����� �������/���������     |" << std::endl;
	std::cout << "| F5 - ��� �ᒺ��� � ������������� �����|" << std::endl;
	std::cout << "|      �� ������������ �������      |" << std::endl;
	std::cout << "| F6 - ���/���� ���������� ��'����      |" << std::endl;
	std::cout << "| F7 - ���������� �������                |" << std::endl;
	std::cout << "| F8 - ���������� ������� ��������      |" << std::endl;
	std::cout << "| F9 - ������������ ��'���               |" << std::endl;
	printHorizontalLine();
	std::cout << "|             �������� �������          |" << std::endl;
	printHorizontalLine();
	std::cout << "| Ctrl + X          - �������           |" << std::endl;
	std::cout << "| Ctrl + C          - ���������         |" << std::endl;
	std::cout << "| Ctrl + V          - ��������           |" << std::endl;
	std::cout << "| DEL               - ��������           |" << std::endl;
	std::cout << "| Hold Ctrl + Click - �������� ��'���� |" << std::endl;
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

	sf::RenderWindow *window = new RenderWindow(sf::VideoMode(1280, 960), sf::String(L"���������������, ��-23�-1 | lab04"), sf::Style::Titlebar | sf::Style::Close, settings);
	SceneController *sceneController = new SceneController(window);

	while (window->isOpen())
	{
		sceneController->render();
	}

	return 0;
}