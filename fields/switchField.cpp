#include "../stdafx.h"
#include "switchField.h"

switchField::switchField(sf::Font& Font, sf::Vector2f Position, bool State)
{
	this->active = sf::Color::White;
	this->normal = sf::Color(200,200,200);
	this->State = State;

	this->OnRect.setPosition(Position);
	this->OnRect.setSize(sf::Vector2f(50,25));
	this->OnRect.setOutlineThickness(4);
	this->OnRect.setFillColor(sf::Color::Transparent);

	this->OffRect.setPosition(Position.x+50+8,Position.y);
	this->OffRect.setSize(sf::Vector2f(50, 25));
	this->OffRect.setOutlineThickness(4);
	this->OffRect.setFillColor(sf::Color::Transparent);

	this->On.setFont(Font);
	this->On.setString("On");
	this->On.setCharacterSize(18);
	this->On.setPosition(this->OnRect.getPosition().x+(this->OnRect.getSize().x/2)-(this->On.getGlobalBounds().width/2), this->OnRect.getPosition().y);
	this->Off.setFont(Font);
	this->Off.setString("Off");
	this->Off.setCharacterSize(18);
	this->Off.setPosition(this->OffRect.getPosition().x + (this->OffRect.getSize().x / 2) - (this->Off.getGlobalBounds().width / 2), this->OffRect.getPosition().y);


	if (State == 0) {
		this->OffRect.setOutlineColor(this->active);
		this->OffRect.setFillColor(sf::Color(this->active.r, this->active.g, this->active.b,80));
		this->Off.setFillColor(this->active);
		this->OnRect.setOutlineColor(this->normal);
		this->OnRect.setFillColor(sf::Color(this->normal.r, this->normal.g, this->normal.b, 80));
		this->On.setFillColor(this->normal);
	}
	else {
		this->OffRect.setOutlineColor(this->normal);
		this->OffRect.setFillColor(sf::Color(this->normal.r, this->normal.g, this->normal.b, 80));
		this->Off.setFillColor(this->normal);
		this->OnRect.setOutlineColor(this->active);
		this->OnRect.setFillColor(sf::Color(this->active.r, this->active.g, this->active.b, 80));
		this->On.setFillColor(this->active);

	}
}

void switchField::render(sf::RenderTarget& target)
{
	target.draw(this->OnRect);
	target.draw(this->On);
	target.draw(this->OffRect);
	target.draw(this->Off);
}

void switchField::update(sf::Vector2f MousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!this->MousePressed) {
			if (this->OffRect.getGlobalBounds().contains(MousePos)) {
				//Set Off
				this->State = 0;
				if (State == 0) {
					this->OffRect.setOutlineColor(this->active);
					this->OffRect.setFillColor(sf::Color(this->active.r, this->active.g, this->active.b, 80));
					this->Off.setFillColor(this->active);
					this->OnRect.setOutlineColor(this->normal);
					this->OnRect.setFillColor(sf::Color(this->normal.r, this->normal.g, this->normal.b, 80));
					this->On.setFillColor(this->normal);
				}
				else {
					this->OffRect.setOutlineColor(this->normal);
					this->OffRect.setFillColor(sf::Color(this->normal.r, this->normal.g, this->normal.b, 80));
					this->Off.setFillColor(this->normal);
					this->OnRect.setOutlineColor(this->active);
					this->OnRect.setFillColor(sf::Color(this->active.r, this->active.g, this->active.b, 80));
					this->On.setFillColor(this->active);

				}
			}
			else if (this->OnRect.getGlobalBounds().contains(MousePos)) {
				//Set On
				this->State = 1;
				if (State == 0) {
					this->OffRect.setOutlineColor(this->active);
					this->OffRect.setFillColor(sf::Color(this->active.r, this->active.g, this->active.b, 80));
					this->Off.setFillColor(this->active);
					this->OnRect.setOutlineColor(this->normal);
					this->OnRect.setFillColor(sf::Color(this->normal.r, this->normal.g, this->normal.b, 80));
					this->On.setFillColor(this->normal);
				}
				else {
					this->OffRect.setOutlineColor(this->normal);
					this->OffRect.setFillColor(sf::Color(this->normal.r, this->normal.g, this->normal.b, 80));
					this->Off.setFillColor(this->normal);
					this->OnRect.setOutlineColor(this->active);
					this->OnRect.setFillColor(sf::Color(this->active.r, this->active.g, this->active.b, 80));
					this->On.setFillColor(this->active);

				}
			}
		}
		this->MousePressed = true;
	}
	else if (this->MousePressed) {
		this->MousePressed = false;
	}
}
