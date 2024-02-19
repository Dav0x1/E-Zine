#pragma once

class choiceField
{
private:
	enum Button_State { IDLE = 0, HOVER, ACTIVE };
	unsigned short Quantity;
	int FontSize;
	sf::Color OnColor;
	sf::Color OffColor;
	unsigned short Active;
	bool Vertical;


	sf::Text *Field;
	short *State;
	float *IncreaseSize;
public:
	//Constructor and Destructor
	choiceField(std::string t1, std::string t2, int fontSize, sf::Font& font, sf::Color onColor,sf::Color offColor,
		unsigned short active,int x,int y,bool vertical = true);
	choiceField(unsigned short Quantity, std::string Text[], int FontSize, sf::Font& Font, sf::Color OnColor, sf::Color OffColor,
		unsigned short active, int x, int y, bool vertical = true);
	~choiceField();
	//Functions
	void render(sf::RenderTarget& Target);
	void update(sf::Vector2f & MouseViewPos);

	unsigned short getActive();

	void setPosition(int x, int y);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	void animation();
};