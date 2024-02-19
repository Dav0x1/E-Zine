#include "../stdafx.h"
#include "shop.h"
//Initialization
void shop::initHeader(sf::Font& Font, std::string Header)
{
	this->Header.setFont(Font);
	this->Header.setString(Header);
	this->Header.setPosition(this->Background.getPosition().x + this->Background.getSize().x/2 - this->Header.getGlobalBounds().width/2,
		this->Background.getPosition().y+10);
}
void shop::initBackground(sf::Vector2u WindowSize,sf::Vector2f PlayerInfoSize)
{
	this->Background.setSize(sf::Vector2f(350,450));
	std::cout << PlayerInfoSize.x;
	this->Background.setPosition(WindowSize.x  -360 - PlayerInfoSize.x ,WindowSize.y - 450);

	this->Background.setOutlineColor(sf::Color(57,15,35));
	this->Background.setOutlineThickness(3);
	this->Background.setFillColor(sf::Color(68,18,42));
}
void shop::initItems(sf::Font& Font, std::vector<rpg::Item*>* Items, short itemType,int* money)
{
	this->Texture.loadFromFile("resources/image/items.png");
	int x=0, y=0;
	int width = this->Background.getSize().x/5;
	x = this->Background.getPosition().x + width/2 - 20;
	y = this->Background.getPosition().y +100;
	for (auto &i : *Items) {
		if (i->typeId == itemType) {
			//sf::Texture *Texture,sf::Font *Font, sf::FloatRect Pos, sf::FloatRect TextureRect , rpg::Item *Item
			this->Itemss.push_back(new shopItemRect(&this->Texture, &Font, sf::FloatRect(x, y, 40, 40), i, this->Backpackk, money));
			x += width;
			if (x > this->Background.getPosition().x + width * 5)
			{
				x = this->Background.getPosition().x + width / 2 - 20;
				y += 80;
			}
		}
	}
}
//Update
void shop::updateArmors(sf::Vector2i MousePos)
{
	for (auto& i : this->Itemss) {
		i->update(MousePos);
	}
}
//Render
void shop::renderArmors(sf::RenderTarget* Target)
{
	for (auto& i : this->Itemss) {
		i->render(Target);
	}
	for (auto& i : this->Itemss) {
		i->renderInfo(Target);
	}
}
//Constructors and destructors
shop::shop(sf::Font& Font, std::string Header, sf::FloatRect ActivePlace, sf::Vector2u WindowSize, std::vector<rpg::Item*>* Items, short itemType, backpack* backpack,int* money,sf::Vector2f PlayerInfo)
{
	this->Backpackk = backpack;
	this->Active = false;
	this->ActivePlace = ActivePlace;
	this->initBackground(WindowSize,PlayerInfo);
	this->initHeader(Font,Header);
	this->initItems(Font,Items,itemType,money);
}
shop::~shop()
{

}
//Main Functions
void shop::render(sf::RenderTarget* Target)
{
	if (this->Active) {
		Target->draw(this->Background);
		Target->draw(this->Header);
		this->renderArmors(Target);
	}
}
void shop::update(sf::FloatRect PlayerPosition, sf::Vector2i MousePos)
{
	if (this->ActivePlace.intersects(PlayerPosition)) {
		this->Active = true;
		this->updateArmors(MousePos);
	}
	else
	{
		this->Active = false;
	}
}
// Accessors
bool shop::isActive()
{
	return this->Active;
}
sf::IntRect shop::getGlobalBounds()
{
	return sf::IntRect(this->Background.getGlobalBounds());
}
