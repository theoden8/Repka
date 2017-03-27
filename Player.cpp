#include "Player.hpp"
#include "Headquarters.hpp"

int Player::g_color = 0;
Player::Player (Field *field, Position destination, Storage *storage):
	color(g_color),
	field(field), selected(NULL), money(Headquarters::COST), income(1)
{
	++g_color;
	city = new Headquarters(this, field, storage, destination);
}

Player::~Player() {
}

void Player::Stamina() {
}

void Player::Death() {
}

void Player::SetTargets() {
}
