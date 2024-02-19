#pragma once

class insertField
{
private:
	enum Button_State { IDLE = 0, ACTIVE };

	sf::RectangleShape Field;
	sf::Text Letter;
	unsigned short State;

	sf::Event* Event;

	short Key;

	float animationDelay;
public:
	//Constructor and Destructor
	insertField(short posX, short posY, unsigned short width, unsigned short height,
		short defaultKey,sf::Font &font,unsigned short fontSize,sf::Event *Event);
	~insertField();
	//Functions
	void render(sf::RenderTarget& Target);
	void update(sf::Vector2f& MouseViewPos);

	short getBind();

	void animation();
};