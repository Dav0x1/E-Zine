#include "../stdafx.h"
#include "statistics.h"
//Constructors and destructors
statistics::statistics(unsigned short health, unsigned short mana, unsigned short def, unsigned short att, unsigned short attspd, unsigned short spd, int money, short lvl, int currentExp, int maxExp)
{
	this->health = health;
	this->maxhealth = health;
	this->speed = spd;
	this->att = att;
	this->attspd = attspd;
	this->def = def;
	this->mana = mana;
	this->maxmana = mana;
	this->money = money;

	this->level = lvl;
	this->maxExp = maxExp;
	this->currentExp = currentExp;
}
