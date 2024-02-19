#include "../stdafx.h"
#include "animation.h"

//Constructors and destructors
animation::animation(sf::Sprite& Sprite, unsigned short FrameWidth, unsigned short FrameHeight, unsigned short FramesAmount, float Speed)
{
	this->FrameNumber = 0;
	this->Timer = 0.f;
	this->Reverse = false;

	this->Sprite = &Sprite;
	this->FrameWidth = FrameWidth;
	this->FrameHeight = FrameHeight;

	this->FramesAmount = FramesAmount;
	this->TimerMax = Speed;
}

animation::~animation()
{
	
}

//Main Functions
void animation::update(unsigned short State, float& dt)
{
	this->Timer += 10.f * dt;

	if (this->Timer > this->TimerMax) {
		this->Timer = 0.f;
		
		if (!this->Reverse)
			this->FrameNumber++;
		else
			this->FrameNumber--;

		if (this->FrameNumber == this->FramesAmount-1)
			this->Reverse = true;
		if (this->FrameNumber == 0)
			this->Reverse = false;
	}

	this->Sprite->setTextureRect(sf::IntRect(this->FrameNumber * this->FrameWidth, State * this->FrameHeight, this->FrameWidth, this->FrameHeight));

}