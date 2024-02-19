#include "../stdafx.h"
#include "hitbox.h"

//Constructors and destructors
hitbox::hitbox(sf::Sprite& Sprite, float OffSetX, float OffSetY, float Width, float Height)
{
	this->Sprite = &Sprite;

	this->OffSetX = OffSetX;
	this->OffSetY = OffSetY;
	this->Width = Width;
	this->Height = Height;
	this->NextPosition.width = Width;
	this->NextPosition.height = Height;

	this->Rect.setSize(sf::Vector2f(Width,Height));
}
hitbox::~hitbox()
{
}
//Main Functions
void hitbox::update()
{
	this->Rect.setPosition(this->Sprite->getPosition().x + this->OffSetX, this->Sprite->getPosition().y + this->OffSetY);
}
//Accessors
sf::Vector2f hitbox::getPosition()
{
	return this->Rect.getPosition();
}
sf::FloatRect hitbox::getGlobalBounds()
{
	return this->Rect.getGlobalBounds();
}
sf::Vector2f hitbox::getSize()
{
	return this->Rect.getSize();
}
float hitbox::getRotation()
{
	return this->Rect.getRotation();
}
sf::Vector2f hitbox::getOrigin()
{
	return this->Rect.getOrigin();
}
sf::FloatRect hitbox::getNextPosition(const sf::Vector2f& velocity, float& dt)
{
	this->NextPosition.left = this->Rect.getPosition().x + velocity.x * dt;
	this->NextPosition.top = this->Rect.getPosition().y + velocity.y * dt;
	return this->NextPosition;
}
//Modifiers
void hitbox::setPosition(float x, float y)
{
	this->Sprite->setPosition(x - this->OffSetX , y - this->OffSetY);
	this->Rect.setPosition(x,y);
}
