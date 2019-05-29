#include "BlockMgr.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>   

#include "Block.h"

BlockMgr::BlockMgr():isPressAnyKey(false), isCreateBlock(false)
{
	Block* p;
	for (int i = 0; i < 4; ++i) {
		std::vector<Block*> vec;

		for (int j = 0; j < 4; ++j) {
			p = new Block(INIT_X + LINE::LENGTH / 2 + (SQUARE::LENGTH + LINE::LENGTH) * j, \
						  INIT_Y + LINE::LENGTH / 2 + (SQUARE::LENGTH + LINE::LENGTH) * i);
			vec.push_back(p);
		}
		m_blockVec.push_back(vec);
	}
}
BlockMgr::~BlockMgr()
{
}

void BlockMgr::init()
{
	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = 0; j < m_blockVec[0].size(); ++j) {
			m_blockVec[i][j]->setNum(0);
			m_blockVec[i][j]->changeNum();
			m_blockVec[i][j]->setEvent(Event::NONE);
		}
	}
	//first time appear block amount
	int count = 1 + rand() % 2;

	for (int i = 0; i < count; ++i) {
		createNewBlock();
	}
}

void BlockMgr::createNewBlock()
{
	srand(time(NULL));

	bool isPos2Create = false;
	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = 0; j < m_blockVec[0].size(); ++j) {
			if (m_blockVec[i][j]->getNum() == 0) {
				isPos2Create = true;
				break;
			}	
		}
	}
	if (!isPos2Create)
		return;

	int x, y;
	do {
		x = rand() % 4;
		y = rand() % 4;
	} while (m_blockVec[x][y]->getNum() != 0);

	int num = 2 * (1 + rand() % 2);

	m_blockVec[x][y]->setNum(num);

	if(m_blockVec[x][y]->getEvent() ==	Event::NONE) {
		m_blockVec[x][y]->popEvent();
	}
	
	m_blockVec[x][y]->setEvent(Event::APPEAR);
}

void BlockMgr::moveRight()
{
	bool isAnyMove = false;

	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = m_blockVec[0].size() - 1; j >= 0; --j) {
			for (int k = j - 1; k >= 0; --k){
				if (m_blockVec[i][k]->getNum() != 0 && (m_blockVec[i][j]->getNum() ==0 || m_blockVec[i][k]->getNum() == m_blockVec[i][j]->getNum())) {
					isAnyMove = true;
					m_blockVec[i][k]->popEvent();
					m_blockVec[i][k]->setEvent(Event::MOVE_RIGHT);
					m_blockVec[i][k]->setMovePos(m_blockVec[i][j]->getInitPosX(), 0);

					if (m_blockVec[i][j]->getEvent() == Event::NONE ) {
						m_blockVec[i][j]->popEvent();
					}
					m_blockVec[i][j]->setEvent(Event::REPLACE);
					m_blockVec[i][j]->setReplacePos(i, k);

					if (m_blockVec[i][j]->getNum() == 0) {
						m_blockVec[i][j]->setNum(m_blockVec[i][k]->getNum());
						j++;
					}
					else {
						m_blockVec[i][j]->setNum(m_blockVec[i][k]->getNum() * 2);
					}					
					m_blockVec[i][k]->setNum(0);
					break;
				}
				else if (m_blockVec[i][k]->getNum() != 0 && m_blockVec[i][k]->getNum() != m_blockVec[i][j]->getNum()) {
					break;
				}
			}
		}
	}

	if (isAnyMove)
		isCreateBlock = false;
}

void BlockMgr::moveLeft()
{
	bool isAnyMove = false;

	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = 0 ; j < m_blockVec[0].size(); ++j) {
			for (int k = j + 1; k < m_blockVec[0].size(); ++k) {
				if (m_blockVec[i][k]->getNum() != 0 && (m_blockVec[i][j]->getNum() == 0 || m_blockVec[i][k]->getNum() == m_blockVec[i][j]->getNum())) {
					isAnyMove = true;
					m_blockVec[i][k]->popEvent();
					m_blockVec[i][k]->setEvent(Event::MOVE_LEFT);
					m_blockVec[i][k]->setMovePos(m_blockVec[i][j]->getInitPosX(), 0);

					if (m_blockVec[i][j]->getEvent() == Event::NONE) {
						m_blockVec[i][j]->popEvent();
					}
					m_blockVec[i][j]->setEvent(Event::REPLACE);
					m_blockVec[i][j]->setReplacePos(i, k);

					if (m_blockVec[i][j]->getNum() == 0) {
						m_blockVec[i][j]->setNum(m_blockVec[i][k]->getNum());
						j--;
					}
					else {
						m_blockVec[i][j]->setNum(m_blockVec[i][k]->getNum() * 2);
					}
					m_blockVec[i][k]->setNum(0);
					break;
				}
				else if (m_blockVec[i][k]->getNum() != 0 && m_blockVec[i][k]->getNum() != m_blockVec[i][j]->getNum()) {
					break;
				}
			}
		}
	}

	if (isAnyMove)
		isCreateBlock = false;
}

void BlockMgr::moveUp()
{
	bool isAnyMove = false;

	for (int i = 0; i < m_blockVec[0].size(); ++i) {
		for (int j = 0; j < m_blockVec.size(); ++j) {
			for (int k = j + 1; k < m_blockVec.size(); ++k) {
				if (m_blockVec[k][i]->getNum() != 0 && (m_blockVec[j][i]->getNum() == 0 || m_blockVec[k][i]->getNum() == m_blockVec[j][i]->getNum())) {
					isAnyMove = true;
					m_blockVec[k][i]->popEvent();
					m_blockVec[k][i]->setEvent(Event::MOVE_UP);
					m_blockVec[k][i]->setMovePos(0, m_blockVec[j][i]->getInitPosY());

					if (m_blockVec[j][i]->getEvent() == Event::NONE) {
						m_blockVec[j][i]->popEvent();
					}
					m_blockVec[j][i]->setEvent(Event::REPLACE);
					m_blockVec[j][i]->setReplacePos(k, i);

					if (m_blockVec[j][i]->getNum() == 0) {
						m_blockVec[j][i]->setNum(m_blockVec[k][i]->getNum());
						j--;
					}
					else {
						m_blockVec[j][i]->setNum(m_blockVec[k][i]->getNum() * 2);
					}
					m_blockVec[k][i]->setNum(0);
					break;
				}
				else if (m_blockVec[k][i]->getNum() != 0 && m_blockVec[k][i]->getNum() != m_blockVec[j][i]->getNum()) {
					break;
				}
			}
		}
	}

	if (isAnyMove)
		isCreateBlock = false;
}

void BlockMgr::moveDown()
{
	bool isAnyMove = false;

	for (int i = 0; i < m_blockVec[0].size(); ++i) {
		for (int j = m_blockVec.size() - 1; j >= 0; --j) {
			for (int k = j - 1; k >= 0; --k) {
				if (m_blockVec[k][i]->getNum() != 0 && (m_blockVec[j][i]->getNum() == 0 || m_blockVec[k][i]->getNum() == m_blockVec[j][i]->getNum())) {
					isAnyMove = true;
					m_blockVec[k][i]->popEvent();
					m_blockVec[k][i]->setEvent(Event::MOVE_DOWN);
					m_blockVec[k][i]->setMovePos(0, m_blockVec[j][i]->getInitPosY());

					if (m_blockVec[j][i]->getEvent() == Event::NONE) {
						m_blockVec[j][i]->popEvent();
					}
					m_blockVec[j][i]->setEvent(Event::REPLACE);
					m_blockVec[j][i]->setReplacePos(k, i);

					if (m_blockVec[j][i]->getNum() == 0) {
						m_blockVec[j][i]->setNum(m_blockVec[k][i]->getNum());
						j++;
					}
					else {
						m_blockVec[j][i]->setNum(m_blockVec[k][i]->getNum() * 2);
					}
					m_blockVec[k][i]->setNum(0);
					break;
				}
				else if (m_blockVec[k][i]->getNum() != 0 && m_blockVec[k][i]->getNum() != m_blockVec[j][i]->getNum()) {
					break;
				}
			}
		}
	}

	if (isAnyMove)
		isCreateBlock = false;
}

void BlockMgr::update()
{
	bool isAnyEvent = false;

	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = 0; j < m_blockVec[0].size(); ++j) {
			switch (m_blockVec[i][j]->getEvent() )
			{
			case Event::APPEAR:
					m_blockVec[i][j]->appearAnimation();
				break;
			case Event::MOVE_RIGHT:
					m_blockVec[i][j]->moveRightAnimation();
					isAnyEvent = true;
				break;
			case Event::MOVE_LEFT:
					m_blockVec[i][j]->moveLeftAnimation();
					isAnyEvent = true;
				break;
			case Event::MOVE_UP:
					m_blockVec[i][j]->moveUpAnimation();
					isAnyEvent = true;
				break;
			case Event::MOVE_DOWN:
					m_blockVec[i][j]->moveDownAnimation();
					isAnyEvent = true;
				break;
			case Event::REPLACE:
				if (m_blockVec[m_blockVec[i][j]->m_replaceX][m_blockVec[i][j]->m_replaceY]->getEvent() == Event::NONE) {
					m_blockVec[i][j]->changeNum();
				}
				isAnyEvent = true;
					
				break;
			
			}
		}
	}

	if (!isAnyEvent && isPressAnyKey && !isCreateBlock) {
		createNewBlock();
		isCreateBlock = true;
	}
	
}

bool BlockMgr::isAnyEvent()
{
	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = 0; j < m_blockVec[0].size(); ++j) {
			if (m_blockVec[i][j]->getEvent() != Event::NONE) {
				return true;
			}
		}
	}
	return false;
}

bool BlockMgr::isGameOver()
{
	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = 0; j < m_blockVec[0].size(); ++j) {

			if (m_blockVec[i][j]->getNum() == 0) {
				return false;
			}

			if (j == 3 && i < 3) {
				if (m_blockVec[i][j]->getNum() == m_blockVec[i + 1][j]->getNum()) {
					return false;
				}
			}

			if (i == 3 && j < 3) {
				if (m_blockVec[i][j]->getNum() == m_blockVec[i][j + 1]->getNum()) {
					return false;
				}
			}

			if (i < 3 && j < 3) {
				if (m_blockVec[i][j]->getNum() == m_blockVec[i][j + 1]->getNum() ||
					m_blockVec[i][j]->getNum() == m_blockVec[i + 1][j]->getNum()) {
					return false;
				}
			}
		}
	}

	return true;
}

void BlockMgr::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_blockVec.size(); ++i) {
		for (int j = 0; j < m_blockVec[0].size(); ++j) {
			m_blockVec[i][j]->draw(window);
		}
	}
}


