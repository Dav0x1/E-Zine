#include "../stdafx.h"
#include "playerInfo.h"
//Initialization
void playerInfo::initBackground(sf::Vector2u WindowBounds)
{
	this->BgTexture.loadFromFile("resources/image/bg1.png");
	this->Background.setTexture(&this->BgTexture);
	this->Background.setSize(sf::Vector2f(WindowBounds.x*0.25,WindowBounds.y));
	this->Background.setPosition(WindowBounds.x-this->Background.getSize().x,0);
}
void playerInfo::initStats(sf::Font& Font)
{
	//Rectangle
	this->StatsOutline.setOutlineColor(sf::Color::Black);
	this->StatsOutline.setOutlineThickness(3);
	this->StatsOutline.setFillColor(sf::Color(0,0,0,100));

	this->StatsOutline.setSize(sf::Vector2f(this->Background.getSize().x*0.8 , 70));
	this->StatsOutline.setPosition(this->Background.getPosition().x + this->Background.getSize().x * 0.1,this->BarLVL.getPosition().y+ this->BarLVL.getSize().y+10);
	//Stats icons
	this->IconsTexture.loadFromFile("resources/image/statsIcons.png");

	for (int i = 0;i<4; i++) {
		this->StatsIcons[i].setTexture(&this->IconsTexture);
		this->StatsIcons[i].setTextureRect(sf::IntRect((i+2)*19,0,18,18));
		this->StatsIcons[i].setSize(sf::Vector2f(30,30));
	} 
	this->StatsIcons[0].setPosition(this->StatsOutline.getPosition().x + 5, this->StatsOutline.getPosition().y + (this->StatsOutline.getSize().y/2)/2 - this->StatsIcons[0].getSize().y/2);
	this->StatsIcons[1].setPosition(this->StatsOutline.getPosition().x + 5, this->StatsIcons[0].getPosition().y + (this->StatsOutline.getSize().y / 2));

	this->StatsIcons[2].setPosition(this->StatsOutline.getPosition().x + 5 + this->StatsOutline.getSize().x/2, this->StatsOutline.getPosition().y + (this->StatsOutline.getSize().y / 2) / 2 - this->StatsIcons[0].getSize().y / 2);
	this->StatsIcons[3].setPosition(this->StatsOutline.getPosition().x + 5 + this->StatsOutline.getSize().x / 2, this->StatsIcons[2].getPosition().y + (this->StatsOutline.getSize().y / 2));

	//Stats Text
	for (int i = 0; i < 4; i++) {
		this->StatsInfo[i].setFont(Font);
		this->StatsInfo[i].setCharacterSize(15);
		this->StatsInfo[i].setPosition(this->StatsIcons[i].getPosition().x + this->StatsIcons[i].getSize().x + 5, this->StatsIcons[i].getPosition().y);
	}
	std::stringstream txt;
	txt << this->Stats->def;
	this->StatsInfo[0].setString(txt.str());
	txt.str("");
	txt << this->Stats->att;
	this->StatsInfo[1].setString(txt.str());
	txt.str("");
	txt << this->Stats->speed;
	this->StatsInfo[2].setString(txt.str());
	txt.str("");
	txt << this->Stats->attspd;
	this->StatsInfo[3].setString(txt.str());
}
void playerInfo::initBackpack(sf::Texture& Texture,sf::Font&Font,bool* isShopActive, sf::IntRect shopBounds)
{
	this->Backpack = new backpack(sf::IntRect(this->StatsOutline.getPosition().x, this->StatsOutline.getPosition().y+ this->StatsOutline.getSize().y+20,this->StatsOutline.getSize().x,0),5,15,Texture,Font,isShopActive,&this->EquipmentSlots,this->Stats,shopBounds);
}
//Update
void playerInfo::updateEquipmentSlots(sf::Vector2i* MousePos)
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))this->MousePressed = false;

	for (auto& i : this->EquipmentSlots) {
		if (!i->isEmpty()) {
			i->update(*MousePos);
			if (!this->MousePressed && i->getGlobalBounds().contains((*MousePos).x, (*MousePos).y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				i->setActive();
			}
			if (i->isActive() && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				//Check equipment swap
				for (auto& j : *this->Backpack->GetSlots()) {
					if (j->getGlobalBounds().contains(i->getItemGlobalBounds().left + i->getItemGlobalBounds().width / 2, i->getItemGlobalBounds().top + i->getItemGlobalBounds().height / 2)) {
						if (j->isEmpty()) {
							//Remove old stats
							this->Stats->maxhealth -= i->getItemStat().hp;
							this->Stats->maxmana -= i->getItemStat().mp;
							this->Stats->att -= i->getItemStat().att;
							this->Stats->attspd -= i->getItemStat().attspd;
							this->Stats->def -= i->getItemStat().def;
							this->Stats->speed -= i->getItemStat().spd;
							j->addItem(i->getItemStat());
							i->clearItem();
						}
						else if (i->getItemStat().typeId == j->getItemStat().typeId) {
							rpg::Item Temp;
							Temp = i->getItemStat();
							//Remove old stats
							this->Stats->maxhealth -= i->getItemStat().hp;
							this->Stats->maxmana -= i->getItemStat().mp;
							this->Stats->att -= i->getItemStat().att;
							this->Stats->attspd -= i->getItemStat().attspd;
							this->Stats->def -= i->getItemStat().def;
							this->Stats->speed -= i->getItemStat().spd;
							i->addItem(j->getItemStat());
							j->addItem(Temp);
							//add new stats
							this->Stats->maxhealth += i->getItemStat().hp;
							this->Stats->maxmana += i->getItemStat().mp;
							this->Stats->att += i->getItemStat().att;
							this->Stats->attspd += i->getItemStat().attspd;
							this->Stats->def += i->getItemStat().def;
							this->Stats->speed += i->getItemStat().spd;
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
//Constructors and destructors
playerInfo::playerInfo(sf::Vector2u WindowBounds, sf::Font& Font, statistics* Stats, sf::Texture& Texture,bool* isShopActive,sf::IntRect shopBounds)
{
	this->initBackground(WindowBounds);
	this->Stats = Stats;
	//HP Bar
	this->BarHP.setOutlineThickness(3);
	this->BarHP.setOutlineColor(sf::Color::Black);
	this->BarHP.setFillColor(sf::Color(102,0,0));
	this->BarHP.setSize(sf::Vector2f(this->Background.getSize().x*0.6,20));
	this->BarHP.setPosition(this->Background.getPosition().x + this->Background.getSize().x*0.25
		,10);
	this->CurrentBarHP.setFillColor(sf::Color(255, 0, 0));
	this->CurrentBarHP.setPosition(this->BarHP.getPosition());
	this->CurrentBarHP.setSize(sf::Vector2f((this->BarHP.getSize().x/this->Stats->maxhealth)*this->Stats->health, 20)); //To update when hp go lower
	this->TextHP.setFont(Font);
	this->TextHP.setCharacterSize(15);
		std::stringstream Temp;
		Temp << "HP  "<<this->Stats->health<<"/"<<this->Stats->maxhealth;
	this->TextHP.setString(Temp.str()); //To update when hp go lower
	this->TextHP.setStyle(sf::Text::Bold);
	this->TextHP.setPosition(this->BarHP.getPosition().x-38,this->BarHP.getPosition().y);
	//MP Bar
	this->BarMP.setOutlineThickness(3);
	this->BarMP.setOutlineColor(sf::Color::Black);
	this->BarMP.setFillColor(sf::Color(0, 0, 102));
	this->BarMP.setSize(sf::Vector2f(this->Background.getSize().x * 0.6, 20));
	this->BarMP.setPosition(this->Background.getPosition().x + this->Background.getSize().x * 0.25
		, this->BarHP.getPosition().y+this->BarHP.getSize().y+10);
	this->CurrentBarMP.setFillColor(sf::Color(0, 0, 200));
	this->CurrentBarMP.setPosition(this->BarMP.getPosition());
	this->CurrentBarMP.setSize(sf::Vector2f((this->BarMP.getSize().x / this->Stats->maxmana) * this->Stats->mana, 20)); //To update when mp go lower/highier
	this->TextMP.setFont(Font);
	this->TextMP.setCharacterSize(15);
		Temp.str("");
		Temp << "MP  " << this->Stats->mana << "/" << this->Stats->maxmana;
	this->TextMP.setString(Temp.str()); //To update when mp go lower/highier
	this->TextMP.setStyle(sf::Text::Bold);
	this->TextMP.setPosition(this->BarMP.getPosition().x - 38, this->BarMP.getPosition().y);
	//LVL Bar
	this->BarLVL.setOutlineThickness(3);
	this->BarLVL.setOutlineColor(sf::Color::Black);
	this->BarLVL.setFillColor(sf::Color(255, 140, 0));
	this->BarLVL.setSize(sf::Vector2f(this->Background.getSize().x * 0.6, 20));
	this->BarLVL.setPosition(this->Background.getPosition().x + this->Background.getSize().x * 0.25
		, this->BarMP.getPosition().y + this->BarMP.getSize().y + 10);
	this->CurrentBarLVL.setFillColor(sf::Color(255, 215, 0));
	this->CurrentBarLVL.setPosition(this->BarLVL.getPosition());
	this->CurrentBarLVL.setSize(sf::Vector2f((this->BarLVL.getSize().x / this->Stats->maxExp) * this->Stats->currentExp, 20)); //To update when LVL change
	this->TextLVL.setFont(Font);
	this->TextLVL.setCharacterSize(15);
	Temp.str("");
	Temp << "LV  " << this->Stats->level <<" "<<this->Stats->currentExp << "/" << this->Stats->maxExp;
	this->TextLVL.setString(Temp.str()); //To update when LVL change
	this->TextLVL.setStyle(sf::Text::Bold);
	this->TextLVL.setPosition(this->BarLVL.getPosition().x - 38, this->BarLVL.getPosition().y);
	//Statistic
	this->initStats(Font);
	this->initBackpack(Texture, Font,isShopActive,shopBounds);
	//Money
	this->MoneyIcon.setTexture(&this->IconsTexture);
	this->MoneyIcon.setTextureRect(sf::IntRect(19*6,0,18,18));
	this->MoneyIcon.setSize(sf::Vector2f(24,24));
	this->MoneyIcon.setPosition(this->Backpack->getGlobalBounds().left, this->Backpack->getGlobalBounds().top + this->Backpack->getGlobalBounds().height);

	this->Money.setFont(Font);
	this->Money.setCharacterSize(15);
	this->Money.setString(std::to_string(this->Stats->money));
	this->Money.setPosition(this->MoneyIcon.getGlobalBounds().left+ this->MoneyIcon.getGlobalBounds().width+3, this->Backpack->getGlobalBounds().top + this->Backpack->getGlobalBounds().height+2);
	//Player Equipment
		//Helm
		this->EquipmentSlots.push_back(new itemSlot(sf::IntRect(this->Background.getPosition().x+ this->Background.getSize().x/2-25,400,50,50),Texture,Font,2));
		//Robe
		this->EquipmentSlots.push_back(new itemSlot(sf::IntRect(this->EquipmentSlots[0]->getGlobalBounds().left, this->EquipmentSlots[0]->getGlobalBounds().top+100, 50, 50), Texture, Font, 0));
		//Boots
		this->EquipmentSlots.push_back(new itemSlot(sf::IntRect(this->EquipmentSlots[1]->getGlobalBounds().left, this->EquipmentSlots[1]->getGlobalBounds().top + 100, 50, 50), Texture, Font, 3));
		//Staff
		this->EquipmentSlots.push_back(new itemSlot(sf::IntRect(this->EquipmentSlots[1]->getGlobalBounds().left-100, this->EquipmentSlots[1]->getGlobalBounds().top, 50, 50), Texture, Font, 1));
		//Ring
		this->EquipmentSlots.push_back(new itemSlot(sf::IntRect(this->EquipmentSlots[1]->getGlobalBounds().left + 100, this->EquipmentSlots[1]->getGlobalBounds().top, 50, 50), Texture, Font, 4));
}
playerInfo::~playerInfo()
{
	delete this->Stats;
}
//Main Functions
void playerInfo::render(sf::RenderTarget* Target)
{
	Target->draw(this->Background);
	Target->draw(this->StatsOutline);
	for (int i = 0; i < 4; i++) {
		Target->draw(this->StatsIcons[i]);
		Target->draw(this->StatsInfo[i]);
	}
	Target->draw(this->Money);
	Target->draw(this->MoneyIcon);
	this->Backpack->render(*Target);
	//HP Bar
	Target->draw(this->BarHP);
	Target->draw(this->CurrentBarHP);
	Target->draw(this->TextHP);
	//MP Bar
	Target->draw(this->BarMP);
	Target->draw(this->CurrentBarMP);
	Target->draw(this->TextMP);
	//LVL Bar
	Target->draw(this->BarLVL);
	Target->draw(this->CurrentBarLVL);
	Target->draw(this->TextLVL);
	//Player Equipment
	for (auto &i:this->EquipmentSlots) {
		i->renderSlot (*Target);
	}
	for (auto& i : this->EquipmentSlots) {
		i->renderItem(*Target);
	}
	if(!this->MousePressed)
	for (auto& i : this->EquipmentSlots) {
		i->renderInfo(*Target);
	}
}
void playerInfo::update(sf::Vector2i* MousePos)
{
	this->Backpack->update(MousePos,&this->Stats->money);
	this->Money.setString(std::to_string(this->Stats->money));
	this->updateEquipmentSlots(MousePos);
	std::stringstream Temp;
	this->CurrentBarHP.setSize(sf::Vector2f((this->BarHP.getSize().x / this->Stats->maxhealth) * this->Stats->health, 20));
	Temp << "HP  " << this->Stats->health << "/" << this->Stats->maxhealth;
	this->TextHP.setString(Temp.str());

	this->CurrentBarMP.setSize(sf::Vector2f((this->BarMP.getSize().x / this->Stats->maxmana) * this->Stats->mana, 20));
	Temp.str("");
	Temp << "MP  " << this->Stats->mana << "/" << this->Stats->maxmana;
	this->TextMP.setString(Temp.str());

	this->CurrentBarLVL.setSize(sf::Vector2f((this->BarLVL.getSize().x / this->Stats->maxExp) * this->Stats->currentExp, 20));
	Temp.str("");
	Temp << "LV  " << this->Stats->level << " " << this->Stats->currentExp << "/" << this->Stats->maxExp;
	this->TextLVL.setString(Temp.str());

	std::stringstream txt;
	txt << this->Stats->def;
	this->StatsInfo[0].setString(txt.str());
	txt.str("");
	txt << this->Stats->att;
	this->StatsInfo[1].setString(txt.str());
	txt.str("");
	txt << this->Stats->speed;
	this->StatsInfo[2].setString(txt.str());
	txt.str("");
	txt << this->Stats->attspd;
	this->StatsInfo[3].setString(txt.str());
}
//Accessors
sf::Vector2f playerInfo::getSize()
{
	return this->Background.getSize();
}
backpack* playerInfo::getBackpackPointer()
{
	return this->Backpack;
}

itemSlot* playerInfo::getPointerToStaffSlot()
{
	for (auto& i : this->EquipmentSlots)
	{
		if (i->getSlotType() == 1) {
			return i;
		}
	}
}
