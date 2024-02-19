#pragma once
#include "statistics.h"
#include "../playerPanel/itemSlot.h"
#include "projectile.h"
class shooting
{
private:
	std::vector<projectile*> Projectiles;

	sf::Texture* Texture;
	statistics* Stats;

	sf::IntRect Offset;
	float ShotCooldown;
public:
	//Constructor and destructor
	shooting(sf::Texture &Texture,statistics * Stats);
	//Update
	void update(sf::Vector2f PlayerPos,sf::Vector2f MousePos,itemSlot *StaffSlot, std::map<int, sf::IntRect>* ShotsOffset, float dt);
	//Render
	void render(sf::RenderTarget &Target);
	//Accessors
	std::vector<projectile*>* GetProjectilesPointer();
};