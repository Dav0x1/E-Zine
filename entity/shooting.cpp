#include "../stdafx.h"
#include "shooting.h"


//Constructor and destructor
shooting::shooting(sf::Texture& Texture, statistics* Stats)
{
	this->ShotCooldown = 0;
	this->Texture = &Texture;
	this->Stats = Stats;
}
//Update
void shooting::update(sf::Vector2f PlayerPos, sf::Vector2f MousePos,itemSlot* StaffSlot, std::map<int, sf::IntRect> *ShotsOffset,float dt)
{

	for (int i = 0;i<this->Projectiles.size();i++) {
		this->Projectiles[i]->update(dt);
		if (this->Projectiles[i]->getLifeTime() < 0.f) {
			delete this->Projectiles[i];
			this->Projectiles.erase(this->Projectiles.begin() + i);
		}
	}

	this->ShotCooldown += dt * this->Stats->attspd;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->ShotCooldown > 10.f) {
		if (!StaffSlot->isEmpty()) {
			this->Offset = (*ShotsOffset)[StaffSlot->getItemStat().Id];
			short damage = std::rand()%(StaffSlot->getItemStat().maxdmg- StaffSlot->getItemStat().mindmg+1)+StaffSlot->getItemStat().mindmg+this->Stats->att;
			this->Projectiles.push_back(new projectile(*this->Texture, sf::IntRect(StaffSlot->getItemStat().texturePos.x, StaffSlot->getItemStat().texturePos.y + 40, 40, 40), PlayerPos, this->Offset, 1, MousePos,damage));
		}
		this->ShotCooldown = 0;
	}
}
//Render
void shooting::render(sf::RenderTarget& Target)
{
	for (auto &i : this->Projectiles) {
		i->render(Target);
	}
}

std::vector<projectile*>* shooting::GetProjectilesPointer()
{
	return &this->Projectiles;
}
