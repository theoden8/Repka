#include "Position.hpp"

Position::Position (int x, int y):
	x(x), y(y) {};

Position Position::operator + (const Position &position) const {
	return Position(position.x + x, position.y + y);
}

bool Position::operator < (const Position &position) const {
	if (x != position.x)
		return x < position.x;
	return y < position.y;
}

bool Position::operator > (const Position &position) const {
	if (x != position.x)
		return x > position.x;
	return y > position.y;
}

bool Position::operator == (const Position &position) const {
	return (x == position.x) && (y == position.y);
}

bool Position::operator != (const Position &position) const {
	return (x != position.x) || (y != position.y);
}

std::ostream &operator << (std::ostream &os, const Position &position) {
	return os << "(" << position.x << ", " << position.y << ")";
}

void Position::operator += (const Position &position) {
	x += position.x;
	y += position.y;
}

int Position::index(int width, int height) const {
	return width * y + x;
}

