#ifndef __POSITION__
#define __POSITION__

#include <ostream>

struct Position {
	int x, y;

	Position(int x, int y);

	Position operator + (const Position &position) const;
	Position operator - (const Position &position) const;
	bool operator < (const Position &position) const;
	bool operator > (const Position &position) const;
	bool operator == (const Position &position) const;
	bool operator != (const Position &position) const;
	void operator += (const Position &position);

	int index(int width, int height) const;
	double length() const;

	friend std::ostream &operator << (std::ostream &os, const Position &position);
};

#endif
