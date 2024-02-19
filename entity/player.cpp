#include "../stdafx.h"
#include "player.h"
//Constructors and destructors
player::player(sf::Texture& PlayerTexture,sf::Vector2f Pos,sf::Texture& ShotTexture)
{	
	this->PosX = Pos.x;
	this->PosY = Pos.y;
	this->initVariables();
	this->initStats();

	this->State = states::ILDE;
	this->Sprite.setPosition(this->PosX,this->PosY);
	this->Sprite.setTexture(PlayerTexture);

	this->initMovement();
	this->initAnimation();
	this->initHitbox();
	this->initShooting(ShotTexture);
}
player::~player()
{
	delete this->Stats;
	delete this->Movement;
	delete this->Animation;
	delete this->Hitbox;
}
//Main Functions
void player::render(sf::RenderTarget& Target)
{
	this->renderSprite(Target);
	this->Shooting->render(Target);
}
void player::update(float& dt,sf::Vector2f MousePos, itemSlot* StaffSlot, std::map<int, sf::IntRect>* ShotsOffset)
{
	this->updateMovement(dt);
	this->updateState();
	this->updateAnimation(dt);
	this->updateHitbox();
	this->Shooting->update(sf::Vector2f(this->Sprite.getPosition().x+ this->Sprite.getGlobalBounds().width/2, this->Sprite.getPosition().y + this->Sprite.getGlobalBounds().height / 2),MousePos,StaffSlot,ShotsOffset,dt);
	this->updateRegeneration(dt);
}
//Initialization
void player::initVariables()
{
	this->DecreaseSpd = 600.f;
	this->IncreaseSpd = 900.f;

	this->FrameHeight = 48;
	this->FrameWidth = 32;
}
void player::initStats()
{
	this->Stats = new statistics(100,75,0,30,35,100,22300,0,0,1000);
}
void player::initMovement()
{
	this->Movement = new movement(this->Stats->speed,this->IncreaseSpd,this->DecreaseSpd);
}
void player::initAnimation()
{
	this->Animation = new animation(this->Sprite,this->FrameWidth,this->FrameHeight,3,2.f);
}
void player::initShooting(sf::Texture& ShotTexture)
{
	this->Shooting = new shooting(ShotTexture,this->Stats);
}
void player::initHitbox()
{
	int OffSetX{}, OffSetY{}, Width{}, Height{};

	std::fstream file;
	file.open("config/ClassOffset.ini");
	if (file.good()) {
		file >> OffSetX >> OffSetY >> Width >> Height;
		file.close();
	}
	this->Hitbox = new hitbox(this->Sprite,OffSetX,OffSetY,Width,Height);
}
//Update
void player::updateMovement(float& dt)
{
	//When speed change, update maxSpeed in Movement compoment
	if (this->Movement->getMaxSpeed() != this->Stats->speed ) {
		this->Movement->changeMaxSpeed(this->Stats->speed);
	}
	//Move physics and change player position
	this->Movement->updatePhysics(dt);
	this->Sprite.move(this->Movement->getVelocity().x*dt, this->Movement->getVelocity().y*dt);
}
void player::updateState()
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
void player::updateAnimation(float& dt)
{
	this->Animation->update(this->State,dt);
}
void player::updateHitbox()
{
	this->Hitbox->update();
}
void player::updateRegeneration(float& dt)
{
	if (this->Stats->mana > this->Stats->maxmana) {
		this->Stats->mana = this->Stats->maxmana;
	}
	if (this->Stats->health > this->Stats->maxhealth) {
		this->Stats->health = this->Stats->maxhealth;
	}
	this->RegenerationCooldown += dt;
	if (this->RegenerationCooldown > 0.5f) {
		if (this->Stats->health < this->Stats->maxhealth) {
			this->Stats->health++;
		}
		if (this->Stats->mana < this->Stats->maxmana) {
			this->Stats->mana++;
		}
		this->RegenerationCooldown = 0;
	}
	if (this->Stats->health > this->Stats->maxhealth)
		this->Stats->health = this->Stats->maxhealth;
}
//Render
void player::renderSprite(sf::RenderTarget& Target)
{
	Target.draw(this->Sprite);
}
//Accessors
sf::Vector2f player::getPosition()
{
	return this->Hitbox->getPosition();
}
sf::Vector2f player::getSize()
{
	return this->Hitbox->getSize();
}
sf::FloatRect player::getGlobalBounds()
{
	return this->Hitbox->getGlobalBounds();
}
sf::FloatRect player::getNextPositionBounds(float &dt)
{
	return this->Hitbox->getNextPosition(this->Movement->getVelocity(), dt);
}
statistics* player::getStatsPointer()
{
	return this->Stats;
}
//Modifiers
void player::setPosition(float x, float y)
{
	this->Hitbox->setPosition(x, y);
}
void player::stopVelocityX()
{
	this->Movement->stopVelocityX();
}
void player::stopVelocityY()
{
	this->Movement->stopVelocityY();
}
void player::move(float x, float y, float& dt)
{
	this->Movement->move(x, y, dt);
}
std::vector<projectile*>* player::GetProjectilesPointer()
{
	return this->Shooting->GetProjectilesPointer();
}
