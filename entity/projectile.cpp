#include "../stdafx.h"
#include "projectile.h"

//Constructor and destructor
projectile::projectile(sf::Texture& Texture, sf::IntRect TextureRect, sf::Vector2f Pos,sf::IntRect Offset, float Scale, sf::Vector2f Destination,float dmg, float LifeTime)
{
	this->Projectile.setOrigin(20,20);
	this->LifeTime = LifeTime;
	this->Projectile.setTexture(Texture);
	this->Projectile.setTextureRect(TextureRect);
	this->dmg = dmg;

	this->Projectile.setPosition(Pos);
	
	float x, y;
	x = Destination.x - Pos.x;
	y = Destination.y - Pos.y;

	this->Projectile.rotate(atan2(y, x) * 57.29);

	float z = std::sqrt(std::pow(x,2)+ std::pow(y, 2))*2;
	this->QuantityMove.x = x/z;
	this->QuantityMove.y = y/z;
}
//Render
void projectile::render(sf::RenderTarget& Target)
{
	Target.draw(this->Projectile);
}
//Update
void projectile::update(float dt)
{
	this->LifeTime -= dt * 100;
	this->Projectile.move(this->QuantityMove.x*400*dt, this->QuantityMove.y*400*dt);
}

sf::FloatRect projectile::getGlobalBounds()
{
	return this->Projectile.getGlobalBounds();
}

float projectile::getLifeTime()
{
	return this->LifeTime;
}

short projectile::getDMG()
{
	return this->dmg;
}

