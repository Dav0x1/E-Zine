#pragma once
#include <iostream>
//TypeId | Id | name | maxdmg | mindmg | def | hp | mp | spd | att | attspd | cost | texturePos(x,y)
namespace rpg{
	struct Item{
		short typeId;
		short Id;
		std::string name;
		short maxdmg;
		short mindmg;
		short def;
		short hp;
		short mp;
		short spd;
		short att;
		short attspd;
		short cost;
		short sell;
		sf::Vector2f texturePos;
	};
}