#pragma once
class selectField
{
	enum ButtonState { IDLE = 0, HOVER, ACTIVE };
	unsigned short Quantity;
	int FontSize;
	unsigned short Active;

	short FieldState;
	short ActiveField;
	short HoverField;
	sf::RectangleShape Overlay;
	sf::Text* Fields;

	bool MousePressed{false};
public:
	//Constructor and Destructor
	selectField(unsigned short Quantity, std::string Text[], int FontSize, sf::Font& Font,
		unsigned short active, int x, int y);
	~selectField();
	//Render
	void render(sf::RenderTarget& Target);
	//Update
	void update(sf::Vector2f& MouseWindowPos);
	//Accessors
	unsigned short getActive();
	//Modifiers
	void setPosition(int x, int y);
};

