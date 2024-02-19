#include "../stdafx.h"
#include "Tile.h"

//Constructors and destructors
Tile::Tile(float Size, float PosX, float PosY, sf::Texture& Texture, sf::IntRect TextureRect, sf::FloatRect OffSet, bool Collision, bool Obverse)
{
	this->Obverse = Obverse;
	this->Collision = Collision;
	this->Square.setTexture(&Texture);
	this->Square.setTextureRect(TextureRect);
	this->Square.setSize(sf::Vector2f(Size,Size));
	this->Square.setPosition(PosX,PosY);
	this->OffSet = OffSet;
}
Tile::~Tile()
{

}
//Main Functions
void Tile::update()
{

}
void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->Square);
}
//Accessors
//Modifiers
bool Tile::getCollision()
{
	return this->Collision;
}
bool Tile::getObverse()
{
	return this->Obverse;
}
sf::FloatRect Tile::getBounds()
{
	return this->Square.getGlobalBounds();
}
sf::FloatRect Tile::getCollisionBounds()
{
	return sf::FloatRect(this->Square.getPosition().x + this->OffSet.left, this->Square.getPosition().y + this->OffSet.top,
		this->Square.getSize().x - this->OffSet.width - this->OffSet.left, this->Square.getSize().y - this->OffSet.height - this->OffSet.top);
}
sf::FloatRect Tile::getOffSet()
{
	return this->OffSet;
}
sf::IntRect Tile::getTextureRect()
{
	return this->Square.getTextureRect();
}
sf::Vector2f Tile::getPosition()
{
	return this->Square.getPosition();
}
