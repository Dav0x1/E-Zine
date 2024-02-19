#include "../stdafx.h"
#include "insertField.h"

//Constructor and Destructor
insertField::insertField(short posX, short posY, unsigned short width, unsigned short height,
	short defaultKey, sf::Font& font, unsigned short fontSize, sf::Event* Event)
{
	this->animationDelay = 1000;
	this->State = IDLE;
	this->Key = defaultKey;
	this->Event = Event;
	//Field
	this->Field.setSize(sf::Vector2f(width,height));
	this->Field.setPosition(posX,posY);

	this->Field.setFillColor(sf::Color(255,255,255,120));
	this->Field.setOutlineColor(sf::Color::White);
	this->Field.setOutlineThickness(4);
	//TEXT
	this->Letter.setFont(font);
	this->Letter.setCharacterSize(fontSize);
	this->Letter.setString((char)defaultKey);
	this->Letter.setPosition(this->Field.getPosition().x+this->Field.getSize().x/2-this->Letter.getLocalBounds().width/2,
		this->Field.getPosition().y);
}
insertField::~insertField()
{

}
//Functions
void insertField::render(sf::RenderTarget& Target)
{
	Target.draw(this->Field);
	Target.draw(this->Letter);
}
void insertField::update(sf::Vector2f& MouseViewPos)
{
	if (this->Field.getGlobalBounds().contains(MouseViewPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->State = ACTIVE;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->State = IDLE;
	}

	if (this->State == ACTIVE) {
		if (this->Event->type == sf::Event::TextEntered){
			if (this->Event->text.unicode < 123 && this->Event->text.unicode>64) {

				this->Key = static_cast<char>(this->Event->text.unicode);
				this->Letter.setString((char)this->Key);
				this->State = IDLE;
			}
		}
	}


	this->animation();
}
short insertField::getBind()
{
	return this->Key;
}
void insertField::animation()
{
	if (this->State == ACTIVE) {
		if (this->animationDelay > 1000) {
			if(this->Field.getFillColor() == sf::Color(255, 255, 255, 120))
				this->Field.setFillColor(sf::Color(255, 255, 255, 180));
			else if(this->Field.getFillColor() == sf::Color(255, 255, 255, 180))
				this->Field.setFillColor(sf::Color(255, 255, 255, 120));
			this->animationDelay = 0;
		}
		this->animationDelay++;
	}
	else if (this->Field.getFillColor() == sf::Color(255, 255, 255, 180)) {
		this->Field.setFillColor(sf::Color(255, 255, 255, 120));
	}
}