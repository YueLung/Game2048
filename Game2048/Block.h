#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

#include "GameDef.h""

class Block
{
public:
	Block(int x,int y);
	~Block();

	void initSquare();
	void initTxt();

	int getCurPosX();
	int getCurPosY();
	int getInitPosX();
	int getInitPosY();

	void setEvent(Event event);
	void setNum(int num);

	void popEvent();

	Event getEvent();
	int getNum();

	void setMovePos(int x, int y);
	void setReplacePos(int x, int y);

	//Animation
	void appearAnimation();
	void moveUpAnimation();
	void moveDownAnimation();
	void moveLeftAnimation();
	void moveRightAnimation();

	void draw(sf::RenderWindow& window);

	bool canMerge;
	void changeNum();

	int m_replaceX;
	int m_replaceY;
private:
	sf::Color getNumColor(int num);
	int getLength();

private:
	std::queue<Event> m_event;
	int m_num;
	sf::RectangleShape m_square;
	sf::Font m_font;
	sf::Text m_text;
	const int m_x;
	const int m_y;
	int m_moveX;
	int m_moveY;

};

