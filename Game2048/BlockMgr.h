#pragma once
#include <SFML/Graphics.hpp>
#include <vector>



class Block;

class BlockMgr
{
public:
	BlockMgr();
	~BlockMgr();

	void init();
	void createNewBlock();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	bool isAnyEvent();
	bool isGameOver();
	void update();

	void draw(sf::RenderWindow& window);

	bool isPressAnyKey;
private:
	std::vector<std::vector<Block*>> m_blockVec;
	bool isCreateBlock;
};


