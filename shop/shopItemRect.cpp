#include "../stdafx.h"
#include "shopItemRect.h"

//Constructors and destructors
shopItemRect::shopItemRect(sf::Texture* Texture, sf::Font* Font, sf::FloatRect Pos, rpg::Item *Item, backpack* Backpack, int* money)
{
	this->money = money;
	this->Backpack = Backpack;
	this->Item = Item;
	this->ActiveInfo = false;
	//Initialization item rectangle which will display
	this->ItemRect.setPosition(Pos.left,Pos.top);
	this->ItemRect.setSize(sf::Vector2f(Pos.width,Pos.height));
	this->ItemRect.setTexture(Texture);
	this->ItemRect.setTextureRect(sf::IntRect(Item->texturePos.x , Item->texturePos.y, 40, 40));
	this->ItemRect.setOutlineThickness(2);
	this->ItemRect.setOutlineColor(sf::Color::White);
	//Initialization item description
	this->InfoText.setFont(*Font);
	this->InfoText.setCharacterSize(15);
	//Diffrent for other items

	std::stringstream info;
	info << Item->name << "\n";
	if(Item->maxdmg!=0)
		info << "Damage:" << Item->mindmg << "-" << Item->maxdmg << "\n";
	if (Item->def != 0)
			info<<"Defense:"<<Item->def<<"\n";
	if (Item->hp != 0)
		info << "Health:" << Item->hp << "\n";
	if (Item->mp != 0)
		info << "Mana:" << Item->mp << "\n";
	if (Item->att != 0)
		info << "Attack:" << Item->spd << "\n";
	if (Item->attspd != 0)
		info << "Attack Speed:" << Item->attspd << "\n";
	if (Item->spd != 0)
		info << "Speed:" << Item->spd << "\n";
	if (Item->cost != 0)
		info << "Cost:" << Item->cost << "\n";
	this->InfoText.setString(info.str());
	//Initialization item info rectangle
	this->InfoRect.setFillColor(sf::Color(0, 0, 0,195));
	this->InfoRect.setOutlineThickness(2);
	this->InfoRect.setOutlineColor(sf::Color::Black);
	this->InfoRect.setSize(sf::Vector2f(this->InfoText.getGlobalBounds().width+10, this->InfoText.getGlobalBounds().height));
}
shopItemRect::~shopItemRect()
{

}
//Main Functions
void shopItemRect::render(sf::RenderTarget* Target)
{
	Target->draw(this->ItemRect);
}
void shopItemRect::renderInfo(sf::RenderTarget* Target)
{
	if (this->ActiveInfo) {
		Target->draw(this->InfoRect);
		Target->draw(this->InfoText);
	}
}
void shopItemRect::update(sf::Vector2i MousePos)
{
	if (this->ItemRect.getGlobalBounds().contains(sf::Vector2f(MousePos))) {
		this->ActiveInfo = true;
		this->InfoRect.setPosition(MousePos.x-this->InfoRect.getSize().x-2,MousePos.y+2);
		this->InfoText.setPosition(MousePos.x-this->InfoRect.getSize().x-2+5,MousePos.y+2);
		if ((*this->money)>=this->Item->cost) {
			if (!this->isPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->Backpack->addItem(*this->Item);
				(*this->money) -= this->Item->cost;
				this->isPressed = true;
			}
			else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->isPressed = false;
			}
		}
	}
	else
		this->ActiveInfo = false;
}
