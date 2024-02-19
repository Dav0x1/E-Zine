#pragma once
class statistics
{
private:

public:
	//Constructors and destructors
	statistics(unsigned short health, unsigned short mana, unsigned short def, unsigned short att, unsigned short attspd, unsigned short spd, int money, short lvl, int currentExp,int maxExp);
	//Stats
	unsigned short maxhealth;
	unsigned short health;
	unsigned short maxmana;
	unsigned short mana;
	unsigned short def;
	unsigned short att;
	unsigned short attspd;
	unsigned short speed;
	//Other
	int money;
	short level;
	int currentExp;
	int maxExp;
};