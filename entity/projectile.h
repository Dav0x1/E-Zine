#pragma once

class projectile
{
private:
	sf::Sprite Projectile;
	float LifeTime;
	short dmg;
	sf::Vector2f QuantityMove;
public:
	//Constructor and destructor
	projectile(sf::Texture& Texture,sf::IntRect TextureRect,sf::Vector2f Pos, sf::IntRect Offset , float Scale ,sf::Vector2f Destination,float dmg,float LifeTime = 100);
	//Render Update
	void render(sf::RenderTarget& Target);
	void update(float dt);
	//Accessors
	sf::FloatRect getGlobalBounds();
	float getLifeTime();
	short getDMG();
};