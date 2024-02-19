#include "../stdafx.h"
#include "state.h"

//Constructor and Destructor
state::state(StateData* stateData)
{
	this->keyTimeMax = 10.f;
	this->keyTime = 0.f;

	this->stateData = stateData;

	this->MouseWindowPos = sf::Vector2i(0,0);
	this->MouseViewPos = sf::Vector2f(0.f,0.f);

	//Set FPS text
	this->fpsUpdateDelay = 0.f;
	this->fps.setFont(*this->stateData->Font);
	this->fps.setFillColor(sf::Color::White);
	this->fps.setString("[INVALID]");
	this->fps.setCharacterSize(10);
}


state::~state()
{

}

//Functions
void state::updateMousePosition(sf::View *View)
{
	this->MouseWindowPos = sf::Mouse::getPosition(*this->stateData->Window);

	if (View!=NULL) {
		this->stateData->Window->setView(*View);

		this->MouseViewPos = this->stateData->Window->mapPixelToCoords(this->MouseWindowPos);

		this->stateData->Window->setView(this->stateData->Window->getDefaultView());
	}
	else {
		this->MouseViewPos = this->stateData->Window->mapPixelToCoords(this->MouseWindowPos);
	}
}

void state::updateDeltaTime()
{
	this->stateData->dt = this->dtClock.restart().asSeconds();
}

void state::updateKeyTime()
{
	this->keyTime += 80.f*this->stateData->dt;
}

void state::updateFps()
{
	if (this->fpsUpdateDelay > 0.3f) {
		std::stringstream temp;
		temp << "[" << std::ceil(1 / this->stateData->dt) << "]";
		this->fps.setString(temp.str());
		this->fpsUpdateDelay = 0.f;
	}
	this->fpsUpdateDelay += this->stateData->dt;
}

bool state::getKeyTime()
{
	if (this->keyTime > this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}
