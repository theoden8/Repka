#include "Player.hpp"
#include "Headquarters.hpp"
#include "Knight.hpp"

Player::Player (Field *field, Position destination, Storage *storage):
	field(field), selected(NULL), gold(Headquarters::COST + Knight::COST), income(1)
{
	city = new Headquarters(this, field, storage, destination);
}

Player::~Player()
{}

void Player::stamina() {
}

void Player::death() {
}

void Player::SetTargets() {
}
