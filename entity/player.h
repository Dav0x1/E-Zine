#pragma once
#include "movement.h"
#include "animation.h"
#include "hitbox.h"
#include "statistics.h"
#include "shooting.h"
#include "../playerPanel/itemSlot.h"

class player
{
private:
	enum states { ILDE = 0, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, MOVE_UP };
	unsigned short State;

	statistics *Stats;

	sf::Sprite Sprite;
	hitbox* Hitbox;

	movement *Movement;
	animation* Animation;
	shooting* Shooting;

	float RegenerationCooldown{1.f};
	//Default Variables
	float PosX, PosY;
	float DecreaseSpd, IncreaseSpd;
	unsigned short FrameWidth, FrameHeight;
	//Initialization
	void initVariables();
	void initStats();
	void initMovement();
	void initAnimation();
	void initShooting(sf::Texture& ShotTexture);
	void initHitbox();
	//Update
	void updateMovement(float& dt);
	void updateState();
	void updateAnimation(float& dt);
	void updateHitbox();
	void updateRegeneration(float& dt);
	//Render
	void renderSprite(sf::RenderTarget &Target);
public:
	//Constructors and destructors
	player(sf::Texture & PlayerTexture, sf::Vector2f Pos, sf::Texture& ShotTexture);
	~player();
	//Main Functions
	void render(sf::RenderTarget &Target);
	void update(float& dt,sf::Vector2f MousePos, itemSlot* StaffSlot,std::map<int, sf::IntRect>* ShotsOffset);
	//Accessors
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getNextPositionBounds(float &dt);
	statistics* getStatsPointer();
	//Modifiers
	void setPosition(float x, float y);
	void stopVelocityX();
	void stopVelocityY();
	void move(float x,float y, float &dt);
	std::vector<projectile*>* GetProjectilesPointer();
};