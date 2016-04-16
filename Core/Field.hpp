#pragma once

#include <map>
#include <vector>

#include "Object.hpp"

struct Object;

struct Field {
	std::vector <Position> moves;

	int width, height, turn;
	std::vector <Player *> players;
	std::vector <Object *> active_objects, passive_objects;

	Field(Storage *storage, int width, int height);

	Object * GetObject(const Position &position);
	Object * GetActiveObject(const Position &position);
	Object * GetPassiveObject(const Position &position);

	void SetObject(Object *object);
	void SetActiveObject(Object *object);
	void SetPassiveObject(Object *object);

	void RemoveObject(Object *object);
	bool CanHit(Object *object, Object *target);
	std::map <Position, int>  Bfs(Object *object, Position target);
	void Move(Object *obj);
	void Move(Player *player);
	void ResetStamina(Player *player);
	bool Free(Object *object, Position position);
	void NextPlayer();
	Player *GetActivePlayer();
	std::vector <Position> GetMoves(Object *object, const Position &position);
	Object * operator [] (const Position &position);
	bool Valid(const Position &position);
};
