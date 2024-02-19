#pragma once
#include "../entity/statistics.h"
#include "backpack.h"
#include "itemSlot.h"

class playerInfo;

class playerInfo
{
private:
	statistics *Stats;

	sf::Texture IconsTexture;
	//Background
	sf::Texture BgTexture;
	sf::RectangleShape Background;
	//HP Bar
	sf::Text TextHP;
	sf::RectangleShape BarHP;
	sf::RectangleShape CurrentBarHP;
	//MP Bar
	sf::Text TextMP;
	sf::RectangleShape BarMP;
	sf::RectangleShape CurrentBarMP;
	//LVL Bar
	sf::Text TextLVL;
	sf::RectangleShape BarLVL;
	sf::RectangleShape CurrentBarLVL;
	//Statistics
	sf::RectangleShape StatsOutline;
	sf::RectangleShape StatsIcons[4];
	sf::Text StatsInfo[4];
	//Backpack
	backpack* Backpack;
	//Player Equipment
	std::vector<itemSlot*> EquipmentSlots;
	//-----------------------
	bool MousePressed = false;
	//Initialization
	void initBackground(sf::Vector2u WindowBounds);
	void initStats(sf::Font & Font);
	void initBackpack(sf::Texture& Texture, sf::Font& Font, bool* isShopActive, sf::IntRect shopBounds);
	//Money
	sf::Text Money;
	sf::RectangleShape MoneyIcon;
	//Update
	void updateEquipmentSlots(sf::Vector2i* MousePos);
	//Render
public:
	//Constructors and destructors
	playerInfo(sf::Vector2u WindowSize, sf::Font& Font,statistics *Stats, sf::Texture &Texture,bool *isShopActive, sf::IntRect shopBounds);
	~playerInfo();
	//Main Functions
	void render(sf::RenderTarget * Target);
	void update(sf::Vector2i* MousePos);
	//Accessors
	sf::Vector2f getSize();
	backpack* getBackpackPointer();
	itemSlot* getPointerToStaffSlot();
	//Modifiers
};