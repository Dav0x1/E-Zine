#include "../stdafx.h"
#include "slideField.h"

void slideField::setPosition(int x, int y)
{
	this->Field.setPosition(x, y);
	this->Slide.setPosition(this->Field.getPosition().x, this->Field.getPosition().y);

}

//Constructor and Destructor
slideField::slideField(short posX, short posY, unsigned short width, unsigned short height, short minVolume, short maxVolume, float defaultVolume)
{
	this->pixelPerVolum = (float)width / maxVolume;
	//Field
	this->Field.setPosition(posX,posY);
	this->Field.setSize(sf::Vector2f(width,height));

	this->Field.setFillColor(sf::Color(255,255,255,100));
	this->Field.setOutlineColor(sf::Color::Black);
	this->Field.setOutlineThickness(1);
	//Slide
	this->minVolume = minVolume;
	this->maxVolume = maxVolume;
	this->Volume = defaultVolume;
	this->NewVolume = defaultVolume;

	this->Slide.setPosition(this->Field.getPosition().x,this->Field.getPosition().y);

	this->Slide.setSize(sf::Vector2f(this->Volume*this->pixelPerVolum,this->Field.getSize().y));
	this->Slide.setFillColor(sf::Color::White);
}

slideField::~slideField()
{

}

//Functions
void slideField::render(sf::RenderTarget* Target)
{
	Target->draw(this->Slide);
	Target->draw(this->Field);
}

void slideField::update(sf::Vector2f* MouseViewPos)
{
	if (isPressOutSide == false && this->Field.getGlobalBounds().contains(*MouseViewPos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&this->State != ACTIVE) {
			this->State = ACTIVE;
			this->LastMousePos = *MouseViewPos;
		}
	}
	if (this->State == ACTIVE && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->Volume = this->NewVolume;
		this->State = IDLE;
	}

	//Change volume
	if (this->State == ACTIVE) {
		this->NewVolume = this->Volume + (*MouseViewPos).x - this->LastMousePos.x;
		if (this->NewVolume > this->maxVolume)this->NewVolume = this->maxVolume;
		if (this->NewVolume < this->minVolume)this->NewVolume = this->minVolume;
		this->Slide.setSize(sf::Vector2f(this->NewVolume * this->pixelPerVolum, this->Slide.getSize().y));
	}
}

unsigned short slideField::getVolume()
{
	return this->NewVolume;
}