#include <iostream>
#include <SFML/Graphics.hpp>

#include "TxtAnimation.h"
#include "BlockMgr.h"
#include "Block.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "2048");

	BlockMgr mgr;
	TxtAnimation txtAn;
	mgr.init();

	//***********4X4 Board***********
	sf::RectangleShape horizontal_line[5];
	sf::RectangleShape vertical_line[5];

	for (int i = 0; i < 5; ++i) {
		horizontal_line[i].setSize(sf::Vector2f(SQUARE::LENGTH * 4 + LINE::LENGTH * 5, LINE::LENGTH));
		horizontal_line[i].setPosition(INIT_X, INIT_Y + (SQUARE::LENGTH + LINE::LENGTH )* i);
	}

	for (int i = 0; i < 5; ++i) {
		vertical_line[i].setSize(sf::Vector2f(LINE::LENGTH, SQUARE::LENGTH * 4 + LINE::LENGTH * 5));
		vertical_line[i].setPosition(INIT_X + (SQUARE::LENGTH + LINE::LENGTH) * i, INIT_Y);
	}
	//*******************************

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
				mgr.moveRight();
				mgr.isPressAnyKey = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				mgr.moveLeft();
				mgr.isPressAnyKey = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				mgr.moveUp();
				mgr.isPressAnyKey = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				mgr.moveDown();
				mgr.isPressAnyKey = true;
			}
		}

		mgr.update();

		window.clear();
		
		for (int i = 0; i < 5; ++i)
		{
			window.draw(horizontal_line[i]);
			window.draw(vertical_line[i]);
		}

		mgr.draw(window);

		if (mgr.isGameOver()) {
			txtAn.update();
			txtAn.draw(window);
		}
		window.display();
	}

	return 0;
}