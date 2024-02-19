#pragma once
class EntityParameters
{
private:

public:
	//Constructors and destructors
	EntityParameters(std::string name,sf::IntRect textureRect, sf::Vector2i moveRange, sf::IntRect Offset,short hp, unsigned short att, unsigned short attspd, unsigned short spd,short money);
	//Parameters
	std::string name;
	sf::IntRect textureRect;
	sf::Vector2i moveRange;
	sf::IntRect Offset;
	short hp;
	unsigned short att;
	unsigned short attspd;
	unsigned short spd;
	short money;
};

