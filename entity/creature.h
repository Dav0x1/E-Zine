#pragma once
#include "movement.h"
#include "animation.h"
#include "hitbox.h"

class creature;
class movement;
class animation;
class hitbox;

class creature
{
protected:
	enum states { ILDE = 0, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_UP };
	unsigned short State;
	short MaxHealth;
	short Health;

	movement Movement;
	animation Animation;
	hitbox Hitbox;
	sf::Texture* TextureSheet;
public:
};