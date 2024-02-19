#include "../stdafx.h"
#include "entityHerd.h"

entityHerd::entityHerd(sf::Texture& Texture, sf::Font& Font, float Scale, unsigned int Quantity, EntityParameters& Parameters, sf::IntRect RenderBounds)
{
	this->Texture = &Texture;
	this->Font = &Font;
	this->Scale = Scale;
	this->MaxQuantity = Quantity;
	this->Parameters = &Parameters;
	this->RenderBounds = RenderBounds;

	int x, y;
	while (this->CurrentQuantity<this->MaxQuantity) {
		this->CurrentQuantity++;
		x = std::rand()%this->RenderBounds.width+this->RenderBounds.left;
		y = std::rand()%this->RenderBounds.height+this->RenderBounds.top;
		this->Entities.push_back(new entity(*this->Texture,*this->Font,sf::Vector2i(x,y),this->Scale,*this->Parameters));
	}
}
entityHerd::~entityHerd()
{
}
//Render
void entityHerd::render(sf::RenderTarget& Target)
{
	for (auto &i:this->Entities) {
		i->render(Target);
	}
}
void entityHerd::updateEntities(float dt)
{
	if (this->CurrentQuantity<this->MaxQuantity) {
		this->RespawnTime += 10 * dt;
		if (this->RespawnTime>10.f) {
			this->RespawnTime = 0.f;
			//Spawn Mob
			int x, y;
			x = std::rand() % this->RenderBounds.width + this->RenderBounds.left;
			y = std::rand() % this->RenderBounds.height + this->RenderBounds.top;
			try
			{
				//to fix
				EntityParameters Parameters{ "Orc Micha³a",sf::IntRect(0,0,58,58),sf::Vector2i(15,15),sf::IntRect(7,2,40,54),500,50,50,50,25 };
				this->Entities.push_back(new entity(*this->Texture, *this->Font, sf::Vector2i(x, y), this->Scale, Parameters));
			}
			catch (std::bad_alloc& ba)
			{
				std::cerr << "bad_alloc caught: " << ba.what() << '\n';
			}
			this->CurrentQuantity++;
		}
	}

	for (auto& i : this->Entities) {
		i->update(dt);
	}
}
void entityHerd::updateEntitiesMove(float dt, sf::FloatRect PlayerPos)
{
	for (auto& i : this->Entities) {
		i->updateActiveMove(dt,PlayerPos);
	}
}
bool entityHerd::checkShotsCollision(std::vector<projectile*>* Projectiles, int* money)
{
	int x{};
	int y{};
	for (auto &i : *Projectiles) {
		y = 0;
		for (auto& j : this->Entities) {
			if (i->getGlobalBounds().intersects(j->getGlobalBounds())) {
				j->decreaseHealth(i->getDMG());
				if (j->getHealth() <= 0) {
					*money += j->getMoney();
					delete j;
					this->Entities.erase(this->Entities.begin() + y);
					this->CurrentQuantity--;
				}
				delete i;
				Projectiles->erase((*Projectiles).begin() + x);
				return true;
			}
			y++;
		}
		x++;
	}
	return false;
}
std::vector<entity*>* entityHerd::GetPointerToEntities()
{
	return &this->Entities;
}
