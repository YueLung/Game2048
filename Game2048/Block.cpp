#include "Block.h"
#include <iostream>
#include <string> 

Block::Block(int x,int y):m_num(0), m_x(x), m_y(y), canMerge(true)
{
	if (!m_font.loadFromFile( "Arial.ttf" ))
	{
		std::cout << "Can't find font Arial.ttf";
	}

	initTxt();
	initSquare();
}

Block::~Block()
{
}

void Block::initSquare()
{
	m_square.setSize({ 0, 0 });
	m_square.setPosition(m_x + (SQUARE::LENGTH + LINE::LENGTH) / 2, m_y + (SQUARE::LENGTH + LINE::LENGTH) / 2);
	m_square.setFillColor(sf::Color(250, 100, 1000));
}

void Block::initTxt()
{
	m_text.setFont(m_font);
	m_text.setString("");
	m_text.setCharacterSize(0);
	m_text.setFillColor(sf::Color::Black);
	m_text.setStyle(sf::Text::Bold);
	m_text.setPosition(m_x + SQUARE::LENGTH * 0.9, m_y + SQUARE::LENGTH * 0.75);
}

void Block::moveUpAnimation()
{
	if (m_moveY < getCurPosY()) {
		m_square.move(0, -MOVE_SPEED);
		m_text.move(0, -MOVE_SPEED);
	}
	else {
		initSquare();
		initTxt();
		setEvent(Event::NONE);
	}

}

void Block::moveDownAnimation()
{
	if (m_moveY > getCurPosY()) {
		m_square.move(0, MOVE_SPEED);
		m_text.move(0, MOVE_SPEED);
	}
	else {
		initSquare();
		initTxt();
		setEvent(Event::NONE);
	}
}

void Block::moveLeftAnimation()
{
	if (m_moveX < getCurPosX()) {
		m_square.move(-MOVE_SPEED, 0);
		m_text.move(-MOVE_SPEED, 0);
	}
	else {
		initSquare();
		initTxt();
		setEvent(Event::NONE);
	}
}

void Block::moveRightAnimation()
{
	if (m_moveX > getCurPosX()) {
		m_square.move(MOVE_SPEED, 0);
		m_text.move(MOVE_SPEED, 0);
	}
	else {
		initSquare();
		initTxt();
		setEvent(Event::NONE);
	}
}

void Block::changeNum()
{
	setEvent(Event::NONE);

	if (m_num == 0) {
		initSquare();
		initTxt();
	}
	else {
		m_square.setPosition(m_x + LINE::LENGTH / 2, m_y + LINE::LENGTH / 2);
		m_square.setSize(sf::Vector2f(SQUARE::LENGTH, SQUARE::LENGTH));

		m_text.setString(std::to_string(m_num));
		m_text.setPosition(m_x + SQUARE::LENGTH * 0.4, m_y + SQUARE::LENGTH * 0.25 );
		if (m_num > 1000) {
			m_text.move(-45, 0);
		}
		else if (m_num > 100) {
			m_text.move(-30, 0);
		}
		else if (m_num > 10) {
			m_text.move(-15, 0);
		}
		m_text.setCharacterSize(57);
	}
	
}

void Block::setNum(int num)
{
	m_num = num;
	m_square.setFillColor(getNumColor(m_num));
}

void Block::appearAnimation()
{
	if (getLength() < SQUARE::LENGTH){
		m_text.setString(std::to_string(m_num));
		m_text.setCharacterSize((getLength() + EXPEND_SPEED)*0.4);
		m_text.move(-1, -1);

		m_square.setSize(sf::Vector2f(getLength() + EXPEND_SPEED, getLength() + EXPEND_SPEED));
		m_square.move(-1, -1);
	}
	else {
		m_event = Event::NONE;
	}
}

int Block::getLength()
{
	return m_square.getSize().x;
}

int Block::getCurPosX()
{
	return m_square.getPosition().x;
}

int Block::getCurPosY()
{
	return m_square.getPosition().y;
}

int Block::getInitPosX()
{
	return m_x;
}

int Block::getInitPosY()
{
	return m_y;
}

sf::Color Block::getNumColor(int num)
{
	switch (num)
	{
	case 2:
		return sf::Color(177,252,78);
		break;
	case 4:
		return sf::Color(164, 226, 82);
		break;
	case 8:
		return sf::Color(70, 192, 147);
		break;
	case 16:
		return sf::Color(180, 255, 8);
		break;
	case 32:
		return sf::Color(0, 255, 50);
		break;
	case 64:
		return sf::Color(120, 192, 255);
		break;
	case 128:
		return sf::Color(143, 108, 255);
		break;
	case 256:
		return sf::Color(60, 0, 255);
		break;
	case 512:
		return sf::Color(233, 87, 255);
		break;
	case 1024:
		return sf::Color(255, 0, 205);
		break;
	case 2048:
		return sf::Color(255, 0, 0);
		break;
	default:
		return sf::Color(0, 0, 0);
	}
}

void Block::setEvent(Event event)
{
	m_event = event;
}

void Block::setMovePos(int x, int y)
{
	m_moveX = x;
	m_moveY = y;
}

int Block::getNum()
{
	return m_num;
}

Event Block::getEvent()
{
	return m_event;
}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(m_square);
	window.draw(m_text);
}
