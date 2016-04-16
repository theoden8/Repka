#include <queue>
#include <iostream>
#include <cstdlib>

#include "Storage.hpp"
#include "Field.hpp"
#include "Grass.hpp"
#include "Player.hpp"

Field::Field(Storage *storage, int width, int height):
	width(width), height(height), turn(0),
	active_objects(width * height, NULL),
	passive_objects(width * height, NULL)
{
	moves.push_back(Position(-1, 0));
	moves.push_back(Position(0, 1));
	moves.push_back(Position(1, 0));
	moves.push_back(Position(0, -1));
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++)
			new Grass(this, storage, Position(x, y));
	}
}

Object * Field::GetObject(const Position &position) {
	int index = position.index(width, height);
	if(active_objects[index] != NULL)
		return active_objects[index];
	return passive_objects[index];
}

Object * Field::GetActiveObject(const Position &position) {
	return active_objects[position.index(width, height)];
}

Object * Field::GetPassiveObject(const Position &position) {
	return passive_objects[position.index(width, height)];
}

void Field::SetObject(Object *object) {
	if(object->active)
		SetActiveObject(object);
	else
		SetPassiveObject(object);
}

void Field::SetActiveObject(Object *object) {
	int index = object->position.index(width, height);
	if(active_objects[index] == NULL)
		active_objects[index] = object;
}

void Field::SetPassiveObject(Object *object) {
	int index = object->position.index(width, height);
	if(passive_objects[index] == NULL)
		passive_objects[index] = object;
}

void Field::RemoveObject(Object *object) {
	int index = object->position.index(width, height);
	if(active_objects[index] == object)
		active_objects[index] = NULL;
	else if(passive_objects[index] == object)
		passive_objects[index] = NULL;
}

bool Field::CanHit(Object *object, Object *target) {
	return (
				(object->idTexture == Storage::KNIGHT && target->idTexture == Storage::DRAGON)
				|| (object->idTexture == Storage::PRINCESS && target->idTexture == Storage::KNIGHT)
				|| (object->idTexture == Storage::DRAGON && target->idTexture == Storage::PRINCESS)
				|| (target->idTexture == Storage::HEADQUARTERS)
			) && object->owner != object->target->owner;
}

std::map <Position, int> Field::Bfs(Object *object, Position target) {
	std::queue <Position> sequence;
	std::map <Position, int>  shortest;
	sequence.push(target);
	shortest[target] = 0;

	while(!sequence.empty()) {
		Position t = sequence.front();
		sequence.pop();
		std::vector <Position> moves = GetMoves(object, t);
		for(const auto &it : moves)
			if(shortest.count(it) == 0) {
				shortest[it] = shortest[t] + 1;
				sequence.push(*it);
			}
	}
	return shortest;
}

void Field::Move(Object *object) {
	if(object == NULL || object->target == NULL)
		return;

	RemoveObject(object);
	std::map <Position, int> shortest = Bfs(object, object->target->position);
	while (object->stamina > 0 && object->target->position != object->position) {
		std::vector <Position> moves = GetMoves(object, object->position);
		for(const auto &it : moves) {
			if(
				(shortest.count(it) == 1)
				&& (shortest[it] == shortest[object->position] - 1)
			) {
				object->position = it;
				break;
			}
		}
		object->stamina--;
	}
	SetObject(object);

	if(
		shortest[object->position] == 1
			&& CanHit(object, object->target)
			&& --object->target->hitpoints == 0
	)
	{
		delete object->target;
	}
	if(object->position == object->target->position)
		object->target = NULL;
}

void Field::Move(Player *player) {
	for(const auto &it : active_objects) {
		if(it != NULL && player == it->owner)
			Move(it);
	}
}

void Field::ResetStamina(Player *player) {
	for(const auto &it : active_objects) {
		if(it != NULL && player == it->owner)
			it->ResetStamina();
	}
}

bool Field::Free(Object *object, Position target) {
	Object *aim = GetActiveObject(target);
	return Valid(target) && aim == NULL;
}

void Field::NextPlayer() {
	Player *player = GetActivePlayer();
	player->SetTargets();
	Move(player);
	player->gold += player->income;
	ResetStamina(player);
	turn = (turn + 1) % players.size();
}

Player *Field::GetActivePlayer() {
	return players[turn];
}

std::vector <Position> Field::GetMoves(Object *object, const Position &position) {
	std::vector <Position> valid_moves;
	for(int i = 0; i < moves.size(); ++i) {
		Position tmp = position + moves[i];
		if(Free(object, tmp))
			valid_moves.push_back(tmp);
	}
	return valid_moves;
}

Object * Field::operator [] (const Position &position) {
	return GetObject(position);
}

bool Field::Valid (const Position &position) {
	return
		position.x >= 0
		&& position.y >= 0
		&& position.x < width
		&& position.y < height;
}
