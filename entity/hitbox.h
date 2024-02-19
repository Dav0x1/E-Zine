#pragma once
class hitbox
{
private:
	sf::Sprite * Sprite;
	sf::RectangleShape Rect;

	float OffSetX;
	float OffSetY;
	float Width;
	float Height;

	sf::FloatRect NextPosition;
public:
	//Constructors and destructors
	hitbox(sf::Sprite &Sprite,float OffSetX,float OffSetY,float Width,float Height);
	~hitbox();
	//Main Functions
	void update();
	//Accessors
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	float getRotation();
	sf::Vector2f getOrigin();
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getNextPosition(const sf::Vector2f& velocity, float& dt);
	//Modifiers
	void setPosition(float x, float y);
};

