#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameStage
{
public:
	GameStage();
	~GameStage();

	void initTxt();
	void initBoard();

	void draw(sf::RenderWindow& window);

private:
	sf::Font m_font;
	sf::Text m_text;
	std::vector<sf::RectangleShape*> horizontal_line;
	std::vector<sf::RectangleShape*> vertical_line;

};

