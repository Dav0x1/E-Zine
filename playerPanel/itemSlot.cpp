#include "../stdafx.h"
#include "itemSlot.h"

//Constructors and destructors
itemSlot::itemSlot(sf::IntRect Position, sf::Texture& Texture, sf::Font& Font, int Type)
{
	this->Type = Type;
	this->Item = NULL;
	this->Hover = false;
	this->Active = false;

	this->Font = &Font;
	this->Texture = &Texture;

	this->Slot.setPosition(Position.left, Position.top);
	this->Slot.setSize(sf::Vector2f(Position.width,Position.height));

	this->Slot.setOutlineColor(sf::Color::Black);
	this->Slot.setOutlineThickness(4);
	this->Slot.setFillColor(sf::Color(0, 0, 0, 100));

}
itemSlot::~itemSlot()
{
	delete this->Item;
}
//Main Functions
void itemSlot::render(sf::RenderTarget& Target)
{
	Target.draw(this->Slot);
	if (this->Item != NULL) {
		Target.draw(*this->Item); 
	}
	
}
void itemSlot::renderSlot(sf::RenderTarget& Target)
{
	Target.draw(this->Slot);
}
void itemSlot::renderItem(sf::RenderTarget& Target)
{
	if (this->Item != NULL) {
		Target.draw(*this->Item);
	}
}
void itemSlot::renderInfo(sf::RenderTarget& Target)
{
	if (this->Item != NULL) {
		if (!this->Active && this->Hover) {
			Target.draw(this->InfoBox);
			Target.draw(this->InfoText);
		}
	}
}
void itemSlot::update(sf::Vector2i& MousePos)
{
	if (this->Item != NULL) {
		if (this->Item->getGlobalBounds().contains(sf::Vector2f(MousePos.x, MousePos.y))) {
			this->Hover = true;
			this->InfoBox.setPosition(MousePos.x - this->InfoBox.getSize().x - 2, MousePos.y + 2);
			this->InfoText.setPosition(MousePos.x - this->InfoBox.getSize().x - 2 + 5, MousePos.y + 2);
		}
		else
		{
			this->Hover = false;
		}
		if (this->Active) {
			this->Item->setPosition(MousePos.x - this->Item->getSize().x/2, MousePos.y - this->Item->getSize().y / 2);
		}
	}
}
//Accessors
bool itemSlot::isEmpty()
{
	if (this->Item == NULL)
		return true;
	return false;
}
bool itemSlot::isActive()
{
	return this->Active;
}
sf::FloatRect itemSlot::getGlobalBounds()
{
	return this->Slot.getGlobalBounds();
}
sf::FloatRect itemSlot::getItemGlobalBounds()
{
	return this->Item->getGlobalBounds();
}
rpg::Item itemSlot::getItemStat()
{
	return this->ItemStat;
}
int itemSlot::getSlotType()
{
	return this->Type;
}
//Modifiers
void itemSlot::addItem(rpg::Item ItemStat)
{
	this->Item = new sf::RectangleShape;
	this->Item->setSize(this->Slot.getSize());
	this->Item->setPosition(this->Slot.getPosition());
	this->Item->setTexture(this->Texture);
	this->Item->setTextureRect(sf::IntRect(ItemStat.texturePos.x, ItemStat.texturePos.y,40,40));
	this->ItemStat = ItemStat;

	//Initialization Info Box
	this->InfoText.setFont(*this->Font);
	std::stringstream info;
	info << this->ItemStat.name << "\n";
	if (this->ItemStat.maxdmg != 0)
		info << "Damage:" << this->ItemStat.mindmg << "-" << this->ItemStat.maxdmg << "\n";
	if (this->ItemStat.def != 0)
		info << "Defense:" << this->ItemStat.def << "\n";
	if (this->ItemStat.hp != 0)
		info << "Health:" << this->ItemStat.hp << "\n";
	if (this->ItemStat.mp != 0)
		info << "Mana:" << this->ItemStat.mp << "\n";
	if (this->ItemStat.att != 0)
		info << "Attack:" << this->ItemStat.spd << "\n";
	if (this->ItemStat.attspd != 0)
		info << "Attack Speed:" << this->ItemStat.attspd << "\n";
	if (this->ItemStat.spd != 0)
		info << "Speed:" << this->ItemStat.spd << "\n";
	if (this->ItemStat.sell != 0)
		info << "Sell:" << this->ItemStat.sell << "\n";

	this->InfoText.setString(info.str());
	this->InfoText.setCharacterSize(15);

	this->InfoBox.setFillColor(sf::Color(128, 128, 128));
	this->InfoBox.setOutlineThickness(2);
	this->InfoBox.setOutlineColor(sf::Color(169, 169, 169));
	this->InfoBox.setSize(sf::Vector2f(this->InfoText.getGlobalBounds().width + 10, this->InfoText.getGlobalBounds().height));
}

void itemSlot::setActive()
{
	this->Active = true;
}
void itemSlot::disableActive(bool RefreshPos)
{
	if (this->Item != NULL) {
	this->Active = false;
	if(RefreshPos)
		this->Item->setPosition(this->Slot.getPosition().x, this->Slot.getPosition().y);
	}
}

void itemSlot::clearItem()
{
	delete this->Item;
	this->Item = NULL;
}
