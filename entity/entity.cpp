#include "../stdafx.h"
#include "entity.h"

//Constructor and Destructor
entity::entity(sf::Texture &Texture,sf::Font &Font, sf::Vector2i Position, float Scale, EntityParameters Parameters)
{
	this->Font = &Font;
	this->SpawnTile = Position;
	//Entity sprite initialization
	this->Entity.setTexture(Texture);
	this->Entity.setTextureRect(Parameters.textureRect);
	this->Entity.setScale(Scale,Scale);
	this->Entity.setPosition((Position.x*50+25)-this->Entity.getGlobalBounds().width/2, (Position.y*50+25) - this->Entity.getGlobalBounds().height / 2);
	//Parameters initialization
	this->Parameters = new EntityParameters(Parameters);
	//Movement initialization
	this->Movement = new movement(Parameters.spd,900.f,600.f);
	//Animation initialization
	this->Animation = new animation(this->Entity,Parameters.textureRect.width,Parameters.textureRect.height,3,2.f);
	//Hitbox initialization
	this->Hitbox = new hitbox(this->Entity, Parameters.Offset.left*Scale, Parameters.Offset.top * Scale, Parameters.Offset.width * Scale, Parameters.Offset.height * Scale);
	//Entity bar initialization
	this->PixelPerHealth = this->Hitbox->getGlobalBounds().width/this->Parameters->hp;
	this->Health.setPointCount(6);
	this->Health.setPoint(0,sf::Vector2f(5,0));
	this->Health.setPoint(1,sf::Vector2f(0,2));
	this->Health.setPoint(2,sf::Vector2f(5,4));
	this->Health.setPoint(3,sf::Vector2f(this->Hitbox->getGlobalBounds().width,4));
	this->Health.setPoint(4,sf::Vector2f(this->Hitbox->getGlobalBounds().width+5,2));
	this->Health.setPoint(5,sf::Vector2f(this->Hitbox->getGlobalBounds().width,0));
	this->Health.setFillColor(sf::Color::Red);
	this->Health.setOutlineColor(sf::Color::Black);
	this->Health.setOutlineThickness(1);

	this->Name.setFont(Font);
	this->Name.setString(Parameters.name);
	this->Name.setCharacterSize(8);
}
entity::~entity()
{
	delete this->Parameters;
	delete this->Movement;
	delete this->Hitbox;
	delete this->Animation;

	for (auto &i : this->DamageText) {
		delete i;
	}
}
//Render
void entity::render(sf::RenderTarget& Target)
{
	Target.draw(this->Entity);
	Target.draw(this->Name);
	Target.draw(this->Health);
	for (auto &i: this->DamageText) {
		Target.draw(*i);
	}
}
//Update
void entity::update(float dt)
{
	for (int i = 0;i<this->DamageText.size(); i++) {
		this->DamageText[i]->setFillColor(sf::Color(255, 169, 0, this->DamageText[i]->getFillColor().a - 250 * dt));
		if (this->DamageText[i]->getFillColor().a<10) {
			delete this->DamageText[i];
			this->DamageText.erase(this->DamageText.begin() + i);
			i--;
		}
	}

	this->updateState();
	this->Movement->updatePhysics(dt);
	this->updateMovement(dt);
	this->Animation->update(this->State,dt);
	this->Hitbox->update();
	this->updateName();
}
void entity::updateName()
{
	if(this->State!=0){
		this->Health.setPosition(this->Hitbox->getGlobalBounds().left + this->Hitbox->getGlobalBounds().width / 2 - this->Health.getGlobalBounds().width / 2+3, this->Hitbox->getGlobalBounds().top - this->Health.getGlobalBounds().height - 4);
		this->Name.setPosition(this->Hitbox->getGlobalBounds().left+ (this->Hitbox->getGlobalBounds().width/2)-this->Name.getGlobalBounds().width/2, this->Health.getGlobalBounds().top-this->Name.getGlobalBounds().height-3);
	}
}
void entity::updateState()
{
	//IDLE
	if (this->Movement->getVelocity().x == 0.f && this->Movement->getVelocity().y == 0.f)
		this->State = states::ILDE;
	else {
		//LEFT
		if (this->Movement->getVelocity().x < 0.f)
			this->State = states::MOVE_LEFT;
		//RIGHT
		else if (this->Movement->getVelocity().x > 0.f)
			this->State = states::MOVE_RIGHT;
		//UP
		else if (this->Movement->getVelocity().y < 0.f)
			this->State = states::MOVE_UP;
		//DOWN
		else if (this->Movement->getVelocity().y > 0.f)
			this->State = states::MOVE_DOWN;
	}
}
void entity::updateMovement(float dt)
{
	//Checking if entity is moving
	if (this->State != 0) {
		//Check if entity go away from spawn place
		if (this->Hitbox->getNextPosition(this->Movement->getVelocity(), dt).left < (this->SpawnTile.x - this->Parameters->moveRange.x) * 50) {
			this->stopVelocityX();
		}
		else if (this->Hitbox->getNextPosition(this->Movement->getVelocity(), dt).left + this->Hitbox->getGlobalBounds().width > (this->SpawnTile.x + this->Parameters->moveRange.x) * 50) {
			this->stopVelocityX();
		}
		if (this->Hitbox->getNextPosition(this->Movement->getVelocity(), dt).top < (this->SpawnTile.y - this->Parameters->moveRange.y) * 50) {
			this->stopVelocityY();
		}
		else if (this->Hitbox->getNextPosition(this->Movement->getVelocity(), dt).top + this->Hitbox->getGlobalBounds().height > (this->SpawnTile.y + this->Parameters->moveRange.y) * 50) {
			this->stopVelocityY();
		}
		//Move Entity
		this->Entity.move(this->Movement->getVelocity().x * dt, this->Movement->getVelocity().y * dt);
	}
}
void entity::updateActiveMove(float dt, sf::FloatRect PlayerPos)
{
	float distanceFromPlayer = std::sqrt(
		std::pow((this->Hitbox->getGlobalBounds().left + (this->Hitbox->getGlobalBounds().width / 2))- (PlayerPos.left + (PlayerPos.width / 2)),2)
		+std::pow((this->Hitbox->getGlobalBounds().top + (this->Hitbox->getGlobalBounds().height / 2))- (PlayerPos.top + (PlayerPos.height / 2)),2)
	);
	//Raid on the player
	if (distanceFromPlayer < 150) {
		if (PlayerPos.left> this->Hitbox->getGlobalBounds().left + (this->Hitbox->getGlobalBounds().width / 2)) { this->Movement->move(1.f, 0.f, dt); }
		else if (PlayerPos.left + (PlayerPos.width / 2) < this->Hitbox->getGlobalBounds().left) { this->Movement->move(-1.f, 0.f, dt); }
		if (PlayerPos.top > this->Hitbox->getGlobalBounds().top + (this->Hitbox->getGlobalBounds().height / 2)) { this->Movement->move(0.f, 1.f, dt); }
		else if (PlayerPos.top + (PlayerPos.height / 2) < this->Hitbox->getGlobalBounds().top) { this->Movement->move(0.f, -1.f, dt); }
	}
	//Back to spawn
	else {
		//Check if entity is from left side from spawn
		if (this->Entity.getGlobalBounds().left +  this->Entity.getGlobalBounds().width / 2 < this->SpawnTile.x*50 ) {
			this->Movement->move(1.f, 0.f, dt);
		}
		//Check if entity is from right side from spawn
		else if (this->Entity.getGlobalBounds().left + this->Entity.getGlobalBounds().width / 2 > this->SpawnTile.x * 50 +50) {
			this->Movement->move(-1.f, 0.f, dt);
		}
		//Check if entity is from top side from spawn
		if (this->Entity.getGlobalBounds().top + this->Entity.getGlobalBounds().height / 2 < this->SpawnTile.y * 50) {
			this->Movement->move(0.f, 1.f, dt);
		}
		//Check if entity is from down side from spawn
		else if (this->Entity.getGlobalBounds().top + this->Entity.getGlobalBounds().height / 2 > this->SpawnTile.y * 50 + 50) {
			this->Movement->move(0.f, -1.f, dt);
		}
	}
}
//accessors
sf::FloatRect entity::getGlobalBounds()
{
	return this->Hitbox->getGlobalBounds();
}
sf::FloatRect entity::getNextPositionBounds(float dt)
{
	return this->Hitbox->getNextPosition(this->Movement->getVelocity(),dt);
}
short entity::getHealth()
{
	return this->Parameters->hp;
}
short entity::getMoney()
{
	return this->Parameters->money;
}
//Modifiers
void entity::setPosition(float x, float y)
{
		this->Hitbox->setPosition(x, y);
}
void entity::stopVelocityX()
{
	this->Movement->stopVelocityX();
}
void entity::stopVelocityY()
{
	this->Movement->stopVelocityY();
}
void entity::move(float x, float y, float& dt)
{
	this->Movement->move(x, y, dt);
}
void entity::decreaseHealth(short dmg)
{
	//Decrease	HP
	this->Parameters->hp -= dmg;
	//Change health bar width
	this->Health.setPoint(3, sf::Vector2f(this->PixelPerHealth*this->Parameters->hp, 4));
	this->Health.setPoint(4, sf::Vector2f(this->PixelPerHealth * this->Parameters->hp + 5, 2));
	this->Health.setPoint(5, sf::Vector2f(this->PixelPerHealth * this->Parameters->hp, 0));
	//Add Damage Text
	std::stringstream dmgString;
	dmgString << dmg;
	this->DamageText.push_back(new sf::Text(dmgString.str(),*this->Font));
	this->DamageText.back()->setCharacterSize(10);
	this->DamageText.back()->setPosition(this->Entity.getGlobalBounds().left+(std::rand()%(int)this->Entity.getGlobalBounds().width), this->Entity.getGlobalBounds().top + (std::rand() % (int)this->Entity.getGlobalBounds().height/2));
	this->DamageText.back()->setFillColor(sf::Color(255,169,0,255));
}
