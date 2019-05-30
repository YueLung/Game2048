#include "GameStage.h"
#include <iostream>

#include "GameDef.h"

GameStage::GameStage()
{
	initBoard();
	initTxt();
}

GameStage::~GameStage()
{
	int size = horizontal_line.size();

	for (int i = 0; i < size; ++i) {
		delete horizontal_line[i];
		delete vertical_line[i];
	}
}

void GameStage::initBoard()
{
	for (int i = 0; i < 5; ++i) {
		sf::RectangleShape* p = new sf::RectangleShape();
		p->setSize(sf::Vector2f(SQUARE::LENGTH * 4 + LINE::LENGTH * 5, LINE::LENGTH));
		p->setPosition(INIT_X, INIT_Y + (SQUARE::LENGTH + LINE::LENGTH) * i);

		horizontal_line.push_back(p);
	}

	for (int i = 0; i < 5; ++i) {
		sf::RectangleShape* p = new sf::RectangleShape();
		p->setSize(sf::Vector2f(LINE::LENGTH, SQUARE::LENGTH * 4 + LINE::LENGTH * 5));
		p->setPosition(INIT_X + (SQUARE::LENGTH + LINE::LENGTH) * i, INIT_Y);

		vertical_line.push_back(p);
	}

}

void GameStage::initTxt()
{
	if (!m_font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Can't find font Arial.ttf";
	}

	m_text.setFont(m_font);
	m_text.setString("Press Space To Restart");
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(135, 0);
}

void GameStage::draw(sf::RenderWindow& window)
{
	window.draw(m_text);

	for (int i = 0; i < 5; ++i)
	{
		window.draw(*(horizontal_line[i]));
		window.draw(*(vertical_line[i]));
	}
}
