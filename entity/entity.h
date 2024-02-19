#pragma once
#include "movement.h"
#include "EntityParameters.h"
#include "animation.h"
#include "hitbox.h"

class entity;
class EntityParameters;
class movement;
class animation;

class entity
{
private:
	enum states { ILDE = 0, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, ATTACK_UP, ATTACK_DOWN, ATTACK_RIGHT, ATTACK_LEFT};
	unsigned short State{};

	sf::Font  *Font;
	sf::Sprite Entity;
	sf::Vector2i SpawnTile;
	//Entity bar with health and name
	sf::Text Name;
	sf::ConvexShape Health;
	float PixelPerHealth;
	//Entity components
	hitbox* Hitbox;
	EntityParameters *Parameters;
	movement* Movement;
	animation* Animation;
	//Display damage text
	std::vector<sf::Text*> DamageText;
	//Functions
	void updateName();
	void updateState();
	void updateMovement(float dt);
public:
	//Constructor and Destructor
	entity(sf::Texture& Texture, sf::Font& Font, sf::Vector2i Position, float Scale, EntityParameters Parameters);
	~entity();
	//Render
	void render(sf::RenderTarget &Target);
	//Update
	void update(float dt);
	void updateActiveMove(float dt,sf::FloatRect PlayerPos);
	//accessors
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getNextPositionBounds(float dt);
	short getHealth();
	short getMoney();
	//modifiers
	void setPosition(float x,float y);
	void stopVelocityX();
	void stopVelocityY();
	void move(float x, float y, float& dt);
	void decreaseHealth(short dmg);
};