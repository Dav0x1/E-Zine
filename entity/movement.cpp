#include "../stdafx.h"
#include "movement.h"

//Constructors and destructors
movement::movement(float MaxSpeed, float Acceleration,float Deceleration)
{
	this->Velocity = {};
	this->MaxSpeed = MaxSpeed;
	this->Acceleration = Acceleration;
	this->Deceleration = Deceleration;
}
movement::~movement()
{

}
//Main Functions
void movement::updatePhysics(float & dt)
{
	//Vertical move
	if (this->Velocity.y > 0.f) {
		this->Velocity.y -= this->Deceleration * dt;

		if (this->Velocity.y < 0.f)
			this->Velocity.y = 0.f;
	}
	else if (this->Velocity.y < 0.f) {
		this->Velocity.y += this->Deceleration * dt;

		if (this->Velocity.y > 0.f)
			this->Velocity.y = 0.f;
	}
	//Horizontal move
	if (this->Velocity.x > 0.f) {
		this->Velocity.x -= this->Deceleration * dt;

		if (this->Velocity.x < 0.f)
			this->Velocity.x = 0.f;
	}
	else if (this->Velocity.x < 0.f) {
		this->Velocity.x += this->Deceleration * dt;

		if (this->Velocity.x > 0.f)
			this->Velocity.x = 0.f;
	}
}
void movement::move(float x, float y, float& dt)
{
	this->Velocity.x += this->Acceleration * x * dt;
	this->Velocity.y += this->Acceleration * y * dt;

	if (std::abs(this->Velocity.x) > this->MaxSpeed)
		this->Velocity.x = this->MaxSpeed * x;
	if (std::abs(this->Velocity.y) > this->MaxSpeed)
		this->Velocity.y = this->MaxSpeed * y;
}
//Accessors
sf::Vector2f movement::getVelocity()
{
	return this->Velocity;
}
float movement::getMaxSpeed()
{
	return this->MaxSpeed;
}
//Modifiers
void movement::stopVelocityX()
{
	this->Velocity.x = 0.f;
}
void movement::stopVelocityY()
{
	this->Velocity.y = 0.f;
}

void movement::changeMaxSpeed(float MaxSpeed)
{
	this->MaxSpeed = MaxSpeed;
}
