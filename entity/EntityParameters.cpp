#include "../stdafx.h"
#include "EntityParameters.h"
//Constructors and destructors
EntityParameters::EntityParameters(std::string name, sf::IntRect textureRect , sf::Vector2i moveRange, sf::IntRect Offset,short hp, unsigned short att, unsigned short attspd, unsigned short spd,short money)
{
	this->name = name;
	this->textureRect = textureRect;
	this->moveRange = moveRange;
	this->Offset = Offset;
	this->hp = hp;
	this->att = att;
	this->attspd = attspd;
	this->spd = spd;
	this->money = money;
}
