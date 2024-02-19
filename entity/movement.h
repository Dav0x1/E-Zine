#pragma once
class movement
{
private:
	sf::Vector2f Velocity;
	float MaxSpeed;
	float Acceleration;
	float Deceleration;
public:
	//Constructors and destructors
	movement(float MaxSpeed,float Acceleration, float Deceleration);
	~movement();
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