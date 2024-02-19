#pragma once
#include "shopItemRect.h"
#include "../playerPanel/backpack.h"

class shop;
class backpack;
class shopItemRect;

class shop
{
protected:
	sf::Texture Texture;
	//Header
	sf::Text Header;
	//Background
	sf::RectangleShape Background;
	//Items to buy
	std::vector<shopItemRect*> Itemss;
	//Variables
	sf::FloatRect ActivePlace;
	bool Active;

	backpack* Backpackk;
	//Initialization
	void initHeader(sf::Font& Font, std::string Header);
	void initBackground(sf::Vector2u WindowSize, sf::Vector2f PlayerInfoSize);
	void initItems(sf::Font& Font, std::vector<rpg::Item*>* Items, short itemType, int* money);
	//Update
	void updateArmors(sf::Vector2i MousePos);
	//Render
	void renderArmors(sf::RenderTarget *Target);
public:
	//Constructors and destructors
	shop(sf::Font& Font, std::string Header, sf::FloatRect ActivePlace, sf::Vector2u WindowSize,std::vector<rpg::Item *> *Items,short itemType,backpack * backpack,int *money, sf::Vector2f PlayerInfo);
	~shop();
	//Main Functions
	void render(sf::RenderTarget *Target);
	void update(sf::FloatRect PlayerPosition,sf::Vector2i MousePos);
	//Accessors
	bool isActive();
	sf::IntRect getGlobalBounds();
	//Modifiers
};