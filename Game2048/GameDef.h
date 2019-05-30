#pragma once

const int INIT_X = 90;
const int INIT_Y = 60;

const int EXPEND_SPEED = 2;
const int MOVE_SPEED = 2;

namespace SQUARE {
	const int LENGTH = 140;
};
namespace LINE {
	const int LENGTH = 10;
}
enum  class Event {
	NONE, APPEAR, REPLACE, MOVE_RIGHT, MOVE_LEFT, MOVE_UP, MOVE_DOWN
};




