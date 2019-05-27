#include "TxtAnimation.h"
#include <iostream>

TxtAnimation::TxtAnimation()
{
	if (!m_font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Can't find font Arial.ttf";
	}

	m_text.setFont(m_font);
	m_text.setString("Game Over");
	m_text.setCharacterSize(0);
	m_text.setFillColor(sf::Color::Red);
	m_text.setPosition(250, 250);
}

TxtAnimation::~TxtAnimation()
{
}

void TxtAnimation::update()
{
	if (m_text.getPosition().x > 150) {
		m_text.move(-2, 0);
		m_text.setCharacterSize(250 - m_text.getPosition().x);
	}
}

void TxtAnimation::draw(sf::RenderWindow& window)
{
	window.draw(m_text);
}
