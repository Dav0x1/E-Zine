#pragma once
class animation
{
private:
	sf::Sprite* Sprite;
	unsigned short FrameWidth;
	unsigned short FrameHeight;

	unsigned short FramesAmount;
	short FrameNumber;
	float Timer;
	float TimerMax;
	bool Reverse;
public:
	//Constructors and destructors
	animation(sf::Sprite &Sprite,unsigned short FrameWidth,unsigned short FrameHeight, unsigned short FramesAmount,float Speed);
	~animation();
	//Main Functions
	void update(unsigned short State, float& dt);
};