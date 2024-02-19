#include "../stdafx.h"
#include "menuState.h"

//Constructor and Destructor
menuState::menuState(StateData* stateData)
	:state(stateData)
{
	this->iniButtons();
	this->iniGUI();
}

//Functions
menuState::~menuState()
{
	for (auto &i : this->Buttons) {
		delete i.second;
	}
}

void menuState::update()
{
	//State Function
	this->updateDeltaTime();
	this->updateMousePosition();
	//Self State Functions
	this->updateButtons();
}

void menuState::render()
{
	this->renderGUI();
}

void menuState::renderButtons()
{
	for (auto& i : this->Buttons) {
		i.second->render(this->stateData->Window);
	}
}

void menuState::renderGUI()
{
	this->stateData->Window->draw(this->Background);
	this->renderButtons();
}

void menuState::updateButtons()
{
	//Update
	for (auto& i : this->Buttons) {
		i.second->update(&this->MouseViewPos);
	}
	//Check press
	if (this->Buttons["EXIT"]->getState() == ACTIVE) {
		this->Buttons["EXIT"]->setIdle();
		this->stateData->States->pop();
	}
	else if (this->Buttons["SETTING"]->getState() == ACTIVE) {
		this->Buttons["SETTING"]->setIdle();
		this->stateData->States->push(new settingsState(this->stateData));
	}
	else if (this->Buttons["NEW_GAME"]->getState() == ACTIVE) {
		this->Buttons["NEW_GAME"]->setIdle();
		this->stateData->States->push(new GameState(this->stateData));
	}
}

//Initialization
void menuState::iniButtons()
{
	this->Buttons["EXIT"] = new button(this->stateData->Window->getSize().x/4-80,this->stateData->Window->getSize().y/2 + 270,160,70,this->stateData->Font,25,
		"Quit",sf::Vector3i(240,230,140),&this->stateData->Texture["BUTTON"],&this->stateData->dt);

	this->Buttons["SETTING"] = new button(this->stateData->Window->getSize().x/4-130, this->stateData->Window->getSize().y/2 + 180, 260, 70, this->stateData->Font, 25,
		"Setting", sf::Vector3i(240, 230, 140), &this->stateData->Texture["BUTTON"], &this->stateData->dt);

	this->Buttons["CONTINUE"] = new button(this->stateData->Window->getSize().x/4-130, this->stateData->Window->getSize().y/2 + 90, 260, 70, this->stateData->Font, 25,
		"Continue", sf::Vector3i(240, 230, 140), &this->stateData->Texture["BUTTON"], &this->stateData->dt,false);

	this->Buttons["NEW_GAME"] = new button(this->stateData->Window->getSize().x/4-130, this->stateData->Window->getSize().y/2, 260, 70, this->stateData->Font, 25,
		"New Game", sf::Vector3i(240, 230, 140), &this->stateData->Texture["BUTTON"], &this->stateData->dt);

}


void menuState::iniGUI()
{
	//Background
	this->Background.setTexture(&this->stateData->Texture["BACKGROUND"]);
	this->Background.setSize(sf::Vector2f(this->stateData->Window->getSize().x, this->stateData->Window->getSize().y));
}
