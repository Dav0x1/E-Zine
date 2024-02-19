#include "../stdafx.h"
#include "button.h"

//Constructor and Destructor
button::button(float x, float y, int width, int height, sf::Font* font, int fontSize, std::string string, sf::Vector3i fontColor, sf::Texture * bgTexture, float* dt, bool active)
{
	this->IsPressOutside = false;
	this->ExtraSize = 0.f;
	this->dt = dt;

	this->fontSize = fontSize;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	this->Shape.setPosition(x, y);
	this->Shape.setSize(sf::Vector2f(width, height));
	this->Shape.setTexture(bgTexture);

	this->Text.setFont(*font);
	this->Text.setString(string);
	this->Text.setCharacterSize(fontSize);
	this->Text.setPosition(this->Shape.getPosition().x + (this->Shape.getGlobalBounds().width / 2 - this->Text.getGlobalBounds().width / 2),
		this->Shape.getPosition().y + (this->Shape.getGlobalBounds().height / 2) - (this->Text.getGlobalBounds().height / 1.3));

	if (active) {
		this->state = IDLE;
		this->Text.setFillColor(sf::Color(fontColor.x,fontColor.y,fontColor.z,255));
	}
	else
	{
		this->state = DISACTIVE;
		this->Text.setFillColor(sf::Color(fontColor.x, fontColor.y, fontColor.z, 100));
		this->Shape.setFillColor(sf::Color(255, 255, 255, 100));
	}
}

button::~button()
{
	delete this->dt;
}

//Functions
void button::render(sf::RenderTarget* Target)
{
	Target->draw(this->Shape);
	Target->draw(this->Text);
}

void button::update(sf::Vector2f * MouseViewPos)
{
	if (this->state != DISACTIVE) {
		if (this->Shape.getGlobalBounds().contains(*MouseViewPos)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if(!this->IsPressOutside)
					this->state = ACTIVE;
			}
			else if (this->state != HOVER){
				this->state = HOVER;
			}
		}
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				this->IsPressOutside = true;
			}

			if (this->state == HOVER) {
				this->state = IDLE;
			}
		}

		if (this->IsPressOutside && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->IsPressOutside = false;
		}
	}
	this->animation();
}

unsigned short button::getState()
{
	return this->state;
}

void button::setIdle()
{
	this->state = IDLE;
}

void button::animation()
{
	if (this->state == HOVER && this->ExtraSize!= 10.f) {
		ExtraSize +=(double) 50.f * (*this->dt);
		if (this->ExtraSize >= 6.f)
			this->ExtraSize = 6.f;
	}

	if (this->ExtraSize != 0.f && this->state == IDLE) {
		ExtraSize -= (double)50.f * (*this->dt);
		if (this->ExtraSize <= 0.f)
			this->ExtraSize = 0.f;
	}

	if (this->ExtraSize !=0) {
		this->Shape.setSize(sf::Vector2f(width + this->ExtraSize, height + this->ExtraSize));
		this->Shape.setPosition(this->x - this->ExtraSize / 2, this->y - this->ExtraSize / 2);
	}
}