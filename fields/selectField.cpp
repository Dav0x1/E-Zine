#include "../stdafx.h"
#include "selectField.h"
//Constructor and Destructor
selectField::selectField(unsigned short Quantity, std::string Text[], int FontSize, sf::Font& Font, unsigned short Active, int x, int y)
{
	this->FontSize = FontSize;
	this->Active = Active;
	this->Quantity = Quantity;

	this->Fields = new sf::Text[Quantity];
	this->FieldState = 0;
	this->ActiveField = Active;
	this->HoverField = 0;

	this->Overlay.setOutlineThickness(2);
	this->Overlay.setOutlineColor(sf::Color::Black);
	this->Overlay.setFillColor(sf::Color(125,125,125));
	this->Overlay.setPosition(x,y);

	int MaxWidth=0;
	int j = 1;
	for (int i = 0; i < this->Quantity; i++) {
		this->Fields[i].setFont(Font);
		this->Fields[i].setString(Text[i]);
		this->Fields[i].setCharacterSize(FontSize);
		this->Fields[i].setFillColor(sf::Color::White);
		this->Fields[i].setOutlineThickness(1);

		if (i != this->Active) {
			this->Fields[i].setPosition(x, y+((this->Fields[0].getGlobalBounds().height+5)*j));
			j++;
		}
		else
		{
			this->Fields[i].setPosition(x, y);
		}

		if (MaxWidth < this->Fields[i].getGlobalBounds().width){
			MaxWidth = this->Fields[i].getGlobalBounds().width; 
		}
	}

	this->Overlay.setSize(sf::Vector2f(MaxWidth, this->Fields[0].getGlobalBounds().height+5));
}
selectField::~selectField()
{
}
//Render
void selectField::render(sf::RenderTarget& Target)
{
	Target.draw(this->Overlay);
	if (this->FieldState == ACTIVE) {
		for (int i = 0; i < this->Quantity; i++) {
			Target.draw(this->Fields[i]);
		}
	}
	else
	{
		Target.draw(this->Fields[this->Active]);
	}
}
//Update
void selectField::update(sf::Vector2f& MouseWindowPos)
{
		if ( !this->MousePressed &&this->Overlay.getGlobalBounds().contains(MouseWindowPos)) {
			if (this->FieldState != ACTIVE && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->FieldState = ACTIVE;
				this->Overlay.setSize(sf::Vector2f(this->Overlay.getSize().x, this->Overlay.getSize().y * this->Quantity));
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				for (int i = 0; i < this->Quantity; i++) {
					if (this->Fields[i].getGlobalBounds().contains(MouseWindowPos)) {
						this->Active = i;

						this->Fields[this->Active].setPosition(this->Overlay.getPosition().x, this->Overlay.getPosition().y);
						for (int i = 0,j = 1; i < this->Quantity; i++) {
							if (i != this->Active) {
								this->Fields[i].setPosition(this->Overlay.getPosition().x, this->Overlay.getPosition().y + ((this->Fields[0].getGlobalBounds().height + 5) * j));
								j++;
							}

						}
						this->MousePressed = false;
						this->FieldState = IDLE;
						this->Overlay.setSize(sf::Vector2f(this->Overlay.getSize().x, this->Fields[0].getGlobalBounds().height + 5));
						break;
					}
				}
			}
		}
		else if (!this->MousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->FieldState = IDLE;
			this->Overlay.setSize(sf::Vector2f(this->Overlay.getSize().x, this->Fields[0].getGlobalBounds().height + 5));
		}

		if (!this->MousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->MousePressed = true;
		else if (this->MousePressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->MousePressed = false;
}

unsigned short selectField::getActive()
{
	return this->Active;
}

void selectField::setPosition(int x, int y)
{
}
