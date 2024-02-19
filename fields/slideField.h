#pragma once

class slideField
{
private:
	sf::RectangleShape Field;
	sf::RectangleShape Slide;
	
	float pixelPerVolum;
	unsigned short State = IDLE;
	short minVolume, maxVolume;
	float Volume;
	float NewVolume;

	sf::Vector2f LastMousePos;

	bool isPressOutSide{false};
public:
	enum State{ IDLE = 0, HOVER, ACTIVE };
	//Constructor and Destructor
	slideField(short posX, short posY, unsigned short width, unsigned short height,short minVolume, short maxVolume,float defaultVolume);
	~slideField();
	//Functions
	void render(sf::RenderTarget* Target);
	void update(sf::Vector2f* MouseViewPos);

	unsigned short getVolume();
	void setPosition(int x, int y);
};