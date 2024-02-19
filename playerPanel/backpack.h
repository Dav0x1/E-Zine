#pragma once
#include "itemSlot.h"
#include "../shop/shop.h"
#include "../entity/statistics.h"

class backpack
{
private:
	sf::Texture* Texture;

	sf::RectangleShape Background;
	std::vector<itemSlot *> Slots;
	sf::IntRect ShopBounds;

	std::vector<itemSlot*>* EquipmentSlots;
	statistics* Stats;

	bool MousePressed = false;
	bool* isShopActive;
	//Initialization
	//Update
	//Render
public:
	//Constructors and destructors
	backpack(sf::IntRect Position,unsigned short Frequency,unsigned short Quantity,sf::Texture & Texture, sf::Font& Font, bool* isShopActive, std::vector<itemSlot*> *EquipmentSlots,statistics *Stats, sf::IntRect shopBounds);
	~backpack();
	//Main Functions
	void render(sf::RenderTarget& Target);
	void update(sf::Vector2i* MousePos, int* money);
	//Accessors
	sf::FloatRect getGlobalBounds();
	std::vector<itemSlot*>* GetSlots();
	//Modifiers
	void addItem(rpg::Item ItemStat);
	//Other
};