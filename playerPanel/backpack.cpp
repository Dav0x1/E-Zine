#include "../stdafx.h"
#include "backpack.h"

//Constructors and destructors
backpack::backpack(sf::IntRect Position, unsigned short Frequency, unsigned short Quantity, sf::Texture& Texture, sf::Font &Font, bool* isShopActive, std::vector<itemSlot*>* EquipmentSlots, statistics* Stats, sf::IntRect shopBounds)
{
	this->ShopBounds = shopBounds;
	this->Stats = Stats;
	this->EquipmentSlots = EquipmentSlots;
	this->isShopActive = isShopActive;
	this->Texture = &Texture;
	
	unsigned short space = 10;
	unsigned short width = (Position.width-(Frequency-1)*space)/Frequency;
	
	unsigned short x{}, y{};

	for (int i = 0 ; i<Quantity ; i++) {
		this->Slots.push_back(new itemSlot(sf::IntRect(Position.left + x*(width+space),Position.top + y*(width + space),width,width),Texture,Font));
		x++;
		if (i != 0) {
			if ((i + 1) % Frequency == 0) y++;
			if (x >= Frequency) x = 0;
		}
	}

	//Background
	this->Background.setPosition(static_cast<float>(Position.left-4), static_cast<float>(Position.top));
	this->Background.setSize(sf::Vector2f(static_cast<float>(Position.width+8),y*(width+space)));
}
backpack::~backpack()
{
	delete this->Texture;
}
//Main Functions
void backpack::render(sf::RenderTarget& Target)
{
	//Render Slot
	for (auto &i : this->Slots) {
		i->renderSlot(Target);
	}
	//Render Items
	for (auto& i : this->Slots) {
		i->renderItem(Target);
	}
	//Render Item Info
	if(!this->MousePressed)
	for (auto& i : this->Slots) {
		i->renderInfo(Target);
	}
}
void backpack::update(sf::Vector2i *MousePos,int *money)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))this->MousePressed = false;

	for (auto& i : this->Slots) {
		if (!i->isEmpty()) {
			i->update(*MousePos);
			if (!this->MousePressed && i->getGlobalBounds().contains((*MousePos).x, (*MousePos).y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				i->setActive();
			}
			if (i->isActive() && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				//Check backpack swap
				bool end=false;
				for (auto& j : this->Slots) {
					if (j->getGlobalBounds().contains(i->getItemGlobalBounds().left + i->getItemGlobalBounds().width / 2, i->getItemGlobalBounds().top + i->getItemGlobalBounds().height / 2))
					{
						rpg::Item Temp;
						Temp = i->getItemStat();
						if (j->isEmpty()) {
							i->clearItem();
						}
						else {
							i->addItem(j->getItemStat());
						}
						j->addItem(Temp);
						end = true;
						break;
					}
				}
				//Check sell item
				if (!end &&*this->isShopActive) {
					if (i->getItemGlobalBounds().intersects(sf::FloatRect(this->ShopBounds))) {
						*money += i->getItemStat().sell;
						i->clearItem();
						end = true;
					}
				}
				//Check equipment swap
				if(!end)
				for (auto& j : *this->EquipmentSlots) {
					if (j->getGlobalBounds().contains(i->getItemGlobalBounds().left + i->getItemGlobalBounds().width / 2, i->getItemGlobalBounds().top + i->getItemGlobalBounds().height / 2)) {
						if (i->getItemStat().typeId == j->getSlotType()) {
							rpg::Item Temp;
							Temp = i->getItemStat();
							if (j->isEmpty()) {
								i->clearItem();
							}
							else {
								//Remove old stats
								this->Stats->maxhealth -= j->getItemStat().hp;
								this->Stats->maxmana -= j->getItemStat().mp;
								this->Stats->att -= j->getItemStat().att;
								this->Stats->attspd -= j->getItemStat().attspd;
								this->Stats->def -= j->getItemStat().def;
								this->Stats->speed -= j->getItemStat().spd;
								i->addItem(j->getItemStat());
							}
							j->addItem(Temp);
							//add new stats
							this->Stats->maxhealth += j->getItemStat().hp;
							this->Stats->maxmana += j->getItemStat().mp;
							this->Stats->att += j->getItemStat().att;
							this->Stats->attspd += j->getItemStat().attspd;
							this->Stats->def += j->getItemStat().def;
							this->Stats->speed += j->getItemStat().spd;
						}
						break;
					}
				}
				i->disableActive();
				break;
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))this->MousePressed = true;
}
sf::FloatRect backpack::getGlobalBounds()
{
	return this->Background.getGlobalBounds();
}
std::vector<itemSlot*>* backpack::GetSlots()
{
	return &this->Slots;
}
//Modifiers
void backpack::addItem(rpg::Item ItemStat)
{
	for (auto& i : this->Slots) {
		if (i->isEmpty()) {
			i->addItem(ItemStat);
			break;
		}
	}
}
