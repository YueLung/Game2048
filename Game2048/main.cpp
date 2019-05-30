#include <iostream>
#include <SFML/Graphics.hpp>

#include "TxtAnimation.h"
#include "BlockMgr.h"
#include "Block.h"
#include "GameStage.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 700), "2048");

	GameStage stage;
	BlockMgr mgr;
	TxtAnimation gameOverAn; 

	mgr.init();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (!mgr.isAnyEvent()) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
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
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					mgr.init();
					mgr.isPressAnyKey = false;
				}
			}
		}

		mgr.update();

		window.clear();

		mgr.draw(window);	

		if (mgr.isGameOver()) {
			gameOverAn.update();
			gameOverAn.draw(window);
		}
		stage.draw(window);

		window.display();
	}

	return 0;
}