#pragma once
#include "../playerPanel/backpack.h"

class backpack;
class shopItemRect;

class shopItemRect
{
protected:
	sf::RectangleShape ItemRect;
	bool ActiveInfo;
	sf::RectangleShape InfoRect;
	sf::Text InfoText;

	rpg::Item *Item;
	backpack* Backpack;

	bool isPressed;
	int* money;
	//Initialization
	//Update
	//Render
public:
	//Constructors and destructors
	shopItemRect(sf::Texture *Texture,sf::Font *Font, sf::FloatRect Pos, rpg::Item *Item,backpack *Backpack, int* money);
	~shopItemRect();
	//Main Functions
	void render(sf::RenderTarget* Target);
	void renderInfo(sf::RenderTarget* Target);
	void update(sf::Vector2i MousePos);
	//Accessors
	//Modifiers
};