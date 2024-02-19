#pragma once
#include "entity.h"
#include "projectile.h"

class entity;
class entityHerd;

class entityHerd
{
private:
	//Area where mobs might spawn
	sf::IntRect RenderBounds;
	//Mobs quantity
	unsigned short MaxQuantity;
	unsigned short CurrentQuantity{};
	//Mobs Herd
	std::vector<entity *> Entities;
	//Variables needed to respawn entity
	sf::Texture* Texture;
	sf::Font* Font;
	float Scale;
	EntityParameters *Parameters;

	float RespawnTime{};
public:
	//Constructors and Destructors
	entityHerd(sf::Texture& Texture, sf::Font& Font,float Scale,unsigned int Quantity , EntityParameters& Parameters, sf::IntRect RenderBounds);
	~entityHerd();
	//Render
	void render(sf::RenderTarget &Target);
	//update
	void updateEntities(float dt);
	void updateEntitiesMove(float dt,sf::FloatRect PlayerPos);
	bool checkShotsCollision(std::vector<projectile*>* Projectiles,int *money);
	//Accessors
	std::vector<entity*>* GetPointerToEntities();
};