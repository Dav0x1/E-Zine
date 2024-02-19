#include "../stdafx.h"
#include "choiceField.h"


//Constructor and Destructor
choiceField::choiceField(std::string t1, std::string t2, int fontSize, sf::Font& font, sf::Color onColor, sf::Color offColor,
	unsigned short active, int x, int y, bool vertical)
{
	this->Vertical = vertical;
	this->Quantity = 2;
	this->FontSize = fontSize;
	this->OnColor = onColor;
	this->OffColor = offColor;
	this->Active = active;

	this->Field = new sf::Text[Quantity];
	this->State = new short[Quantity];
	this->IncreaseSize = new float[Quantity];
	
	std::string Text[2]{t1,t2};
	for (int i = 0; i < this->Quantity; i++) {
		this->State[i] = IDLE;
		this->IncreaseSize[i] = 0.f;
		this->Field[i].setFont(font);
		this->Field[i].setString(Text[i]);
		this->Field[i].setCharacterSize(FontSize);
		this->Field[i].setFillColor(OffColor);
		this->Field[i].setOutlineThickness(1);
	}
	this->Field[Active].setFillColor(OnColor);

	if (vertical) {
		this->Field[0].setPosition(x, y);
		for (int i = 1; i < this->Quantity; i++) {
			this->Field[i].setPosition(x, y + this->Field[i - 1].getGlobalBounds().height + 10);
		}
	}
	else {
		this->Field[0].setPosition(x, y);
		for (int i = 1; i < this->Quantity; i++) {
			this->Field[i].setPosition(x + this->Field[i - 1].getGlobalBounds().width + 10, y);
		}
	}
	
}
choiceField::choiceField(unsigned short Quantity, std::string Text[], int FontSize, sf::Font& Font, sf::Color OnColor, sf::Color OffColor, unsigned short Active, int x, int y, bool vertical)
{
	this->Vertical = vertical;
	this->Quantity = Quantity;
	this->FontSize = FontSize;
	this->OnColor = OnColor;
	this->OffColor = OffColor;
	this->Active = Active;

	this->Field = new sf::Text[Quantity];
	this->State = new short[Quantity];
	this->IncreaseSize = new float[Quantity];

	for (int i = 0;i<this->Quantity; i++) {
		this->State[i] = IDLE;
		this->IncreaseSize[i] = 0.f;
		this->Field[i].setFont(Font);
		this->Field[i].setString(Text[i]);
		this->Field[i].setCharacterSize(FontSize);
		this->Field[i].setFillColor(OffColor);
		this->Field[i].setOutlineThickness(1);
	}
	this->Field[Active].setFillColor(OnColor);

	if (this->Vertical) {
		this->Field[0].setPosition(x, y);
		for (int i = 1; i < this->Quantity; i++) {
			this->Field[i].setPosition(x, this->Field[i - 1].getGlobalBounds().top + this->Field[i-1].getGlobalBounds().height + 10);
		}
	}
	else {
		this->Field[0].setPosition(x, y);
		for (int i = 1; i < this->Quantity; i++) {
			this->Field[i].setPosition(this->Field[i - 1].getGlobalBounds().left + this->Field[i - 1].getGlobalBounds().width + 10, y);
		}
	}
}
choiceField::~choiceField()
{
	delete this->Field;
	delete this->State;
	delete this->IncreaseSize;
}
//Functions
void choiceField::render(sf::RenderTarget& Target)
{
	for (int i = 0; i < this->Quantity; i++) {
		Target.draw(this->Field[i]);
	}
}
void choiceField::update(sf::Vector2f& MouseViewPos)
{
	for (int i = 0; i < this->Quantity; i++) {
		if (this->Field[i].getGlobalBounds().contains(MouseViewPos)) {
			if (this->State[i] != HOVER) {
				this->State[i] = HOVER;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->Active = i;
				for (int i = 0; i < this->Quantity; i++) {
					this->Field[i].setFillColor(OffColor);

				}
				this->Field[i].setFillColor(OnColor);
			}

		}
		else
		{
			if (this->State[i] == HOVER) {
				this->State[i] = IDLE;
			}
		}
	}
	this->animation();
}
unsigned short choiceField::getActive()
{
	return this->Active;
}
void choiceField::setPosition(int x, int y)
{
	if (this->Vertical) {
		this->Field[0].setPosition(x, y);
		for (int i = 1; i < this->Quantity; i++) {
			this->Field[i].setPosition(x, this->Field[i - 1].getGlobalBounds().top + this->Field[i - 1].getGlobalBounds().height + 10);
		}
	}
	else {
		this->Field[0].setPosition(x, y);
		for (int i = 1; i < this->Quantity; i++) {
			this->Field[i].setPosition(this->Field[i - 1].getGlobalBounds().left + this->Field[i - 1].getGlobalBounds().width + 10, y);
		}
	}
}
sf::Vector2f choiceField::getPosition()
{
	return this->Field[0].getPosition();
}
sf::FloatRect choiceField::getGlobalBounds()
{
	return this->Field[0].getGlobalBounds();
}
void choiceField::animation()
{
	for (int i = 0; i < this->Quantity; i++) {
		if (this->State[i] == HOVER && this->IncreaseSize[i] != 2.f) {
			this->IncreaseSize[i] += 1.0f;
			if (this->IncreaseSize[i] >= 2.f)
				this->IncreaseSize[i] = 2.f;
		}
		if (this->IncreaseSize[i] != 0.f && this->State[i] == IDLE) {
			this->IncreaseSize[i] -= 0.1f;
			if (this->IncreaseSize[i] <= 0.f)
				this->IncreaseSize[i] = 0.f;
		}
		if (this->IncreaseSize[i] != 0) {
			this->Field[i].setCharacterSize(this->FontSize + this->IncreaseSize[i]);
		}
	}
}