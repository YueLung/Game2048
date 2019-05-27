#pragma once
#include <SFML/Graphics.hpp>

class TxtAnimation
{
public:
	TxtAnimation();
	~TxtAnimation();

	void update();
	void draw(sf::RenderWindow& window);

private:
	sf::Font m_font;
	sf::Text m_text;
};

