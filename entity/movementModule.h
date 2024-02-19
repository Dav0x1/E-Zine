#pragma once
class movementModule
{
private:
	sf::Vector2f Velocity;
	float MaxSpeed;
	float Acceleration;
	float Deceleration;
public:
	//Constructors
	movementModule(float MaxSpeed,float Acceleration, float Deceleration);
	//Main Functions
	void updatePhysics(float& dt);
	void move(float x,float y, float& dt);
	//Accessors
	sf::Vector2f getVelocity();
	float getMaxSpeed();
	//Modifiers
	void stopVelocityX();
	void stopVelocityY();
	void changeMaxSpeed(float MaxSpeed);
};