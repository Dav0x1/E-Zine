#pragma once

enum Button_State { DISACTIVE = 0, IDLE, HOVER, ACTIVE };

class button
{
private:
	sf::RectangleShape Shape;
	sf::Text Text;
	int fontSize;
	float x, y;
	int width, height;
	float ExtraSize;

	float* dt;

	unsigned short state;

	bool IsPressOutside;
	//Functions
	void animation();
public:
	//Constructor and Destructor
	button(float x, float y, int width, int height, sf::Font* font, int fontSize, std::string string,
		sf::Vector3i fontColor, sf::Texture *bgTexture,float *dt,bool active = true);
	~button();
	//Functions
	void render(sf::RenderTarget * Target);
	void update(sf::Vector2f* MouseViewPos);
	unsigned short getState();
	void setIdle();
};

