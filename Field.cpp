#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <queue>

#include "Storage.hpp"
#include "Field.hpp"
#include "Grass.hpp"
#include "Player.hpp"

Field::Field(Storage *storage, int width, int height):
	width(width), height(height), turn(0),
	activeObjects(width * height, NULL),
	passiveObjects(width * height, NULL)
{
	for(const auto &p: {
		Position(-1, 0),
		Position(0, 1),
		Position(1, 0),
		Position(0, -1)
	})
	{
		moves.push_back(p);
	}
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++)
			new Grass(this, storage, Position(x, y));
	}
}

Field::~Field() {
	for(const auto &a : activeObjects) {
		delete a;
	}
	for(const auto &p : passiveObjects) {
		delete p;
	}
}

Object *Field::GetObject(const Position &position) {
	int index = position.index(width, height);
	if(activeObjects[index] != NULL)
		return activeObjects[index];
	return passiveObjects[index];
}

Object *Field::GetActiveObject(const Position &position) {
	return activeObjects[position.index(width, height)];
}

Object *Field::GetPassiveObject(const Position &position) {
	return passiveObjects[position.index(width, height)];
}

void Field::SetObject(Object *object) {
	if(object->active)
		SetActiveObject(object);
	else
		SetPassiveObject(object);
}

void Field::SetActiveObject(Object *object) {
	int index = object->position.index(width, height);
	if(activeObjects[index] == NULL)
		activeObjects[index] = object;
}

void Field::SetPassiveObject(Object *object) {
	int index = object->position.index(width, height);
	if(passiveObjects[index] == NULL)
		passiveObjects[index] = object;
}

void Field::RemoveObject(Object *object) {
	int index = object->position.index(width, height);
	if(activeObjects[index] == object)
		activeObjects[index] = NULL;
	else if(passiveObjects[index] == object)
		passiveObjects[index] = NULL;
}

bool Field::CanHit(Object *object, Object *target) {
	return object->owner != object->target->owner && (
				object->idTexture == Storage::KNIGHT &&
				target->idTexture == Storage::DRAGON
			||
				object->idTexture == Storage::PRINCESS &&
				target->idTexture == Storage::KNIGHT
			||
				object->idTexture == Storage::DRAGON &&
				target->idTexture == Storage::PRINCESS
			||
				target->idTexture == Storage::HEADQUARTERS
	);
}

std::map <Position, int> Field::BFS(Object *object, const Position &target) {
	std::queue <Position> sequence;
	std::map <Position, int>  shortest;
	sequence.push(target);
	shortest[target] = 0;

	while(!sequence.empty()) {
		Position t = sequence.front();
		sequence.pop();
		for(const auto &step : GetMoves(object, t)) {
			if(shortest.count(step) == 0) {
				shortest[step] = shortest[t] + 1;
				sequence.push(step);
			}
		}
	}
	return shortest;
}

void Field::Move(Object *object) {
	if(object == NULL || object->target == NULL)
		return;

	RemoveObject(object);
	std::map <Position, int> shortest = BFS(object, object->target->position);
	while(object->stamina > 0 && object->target->position != object->position) {
		for(const auto &step : GetMoves(object, object->position)) {
			if(
				shortest.count(step) == 1
				&& shortest[step] == shortest[object->position] - 1
			)
			{
				object->position = step;
				break;
			}
		}
		--object->stamina;
	}
	SetObject(object);

	if(shortest[object->position] == 1) {
		object->target = GetObject(object->target->position);
		if(
			CanHit(object, object->target)
			&& --object->target->hitpoints == 0
		)
		{
			Position target_pos = object->target->position;
			bool is_city = object->target->idTexture == Storage::HEADQUARTERS;
			Player *owner_of_dead = object->target->owner;
			delete object->target;
			if(is_city) {
				DefeatPlayer(owner_of_dead);
			}
			object->target = GetObject(target_pos);
		}
	}
}

void Field::Move(Player *player) {
	for(const auto &it : activeObjects) {
		if(it != NULL && player == it->owner)
			Move(it);
	}
}

void Field::ResetStamina(Player *player) {
	for(const auto &it : activeObjects) {
		if(it != NULL && player == it->owner)
			it->ResetStamina();
	}
}

bool Field::Free(Position pos) {
	return Valid(pos) && GetActiveObject(pos) == NULL;
}

void Field::NextPlayer() {
	Player *player = GetActivePlayer();
	player->SetTargets();
	Move(player);
	player->money += player->income;
	ResetStamina(player);
	turn = (turn + 1) % players.size();
}

void Field::DefeatPlayer(Player *p) {
	p->Death();
	for(auto &a : activeObjects) {
		if(a != NULL && a->owner == p) {
			RemoveObject(a);
			delete a;
		}
	}
	players.erase(std::remove(players.begin(), players.end(), p));
	delete p;
	if(players.size() < 2) {
		winner = players.back();
	}
}

Player *Field::GetActivePlayer() {
	return players[turn];
}

std::vector <Position> Field::GetMoves(Object *object, const Position &position) {
	std::vector <Position> valid_moves;
	for(int i = 0; i < moves.size(); ++i) {
		Position tmp = position + moves[i];
		if(Free(tmp))
			valid_moves.push_back(tmp);
	}
	return valid_moves;
}

Object *Field::operator[] (const Position &position) {
	return GetObject(position);
}

bool Field::Valid(const Position &position) {
	return
		position.x >= 0
		&& position.y >= 0
		&& position.x < width
		&& position.y < height;
}
