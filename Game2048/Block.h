#pragma once
#include <SFML/Graphics.hpp>

namespace SQUARE { 
	const int LENGTH = 140; 
};
namespace LINE {
	const int LENGTH = 10;
}
enum  class Event {
	NONE, APPEAR, REPLACE, MOVE_RIGHT, MOVE_LEFT, MOVE_UP, MOVE_DOWN
};

const int EXPEND_SPEED = 2;
const int MOVE_SPEED = 10;

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

	Event getEvent();
	int getNum();

	void setMovePos(int x, int y);

	//Animation
	void appearAnimation();
	void moveUpAnimation();
	void moveDownAnimation();
	void moveLeftAnimation();
	void moveRightAnimation();

	void draw(sf::RenderWindow& window);

	bool canMerge;
	void changeNum();

private:
	sf::Color getNumColor(int num);
	int getLength();

private:
	Event m_event;
	int m_num;
	sf::RectangleShape m_square;
	sf::Font m_font;
	sf::Text m_text;
	const int m_x;
	const int m_y;
	int m_moveX;
	int m_moveY;
	
};

