#include "../stdafx.h"
#include "settingsState.h"

//Constructor and Destructor
settingsState::settingsState(StateData* stateData)
	:state(stateData)
{
	this->iniVariables();
	this->iniMenu();
	this->iniGUI();
}
settingsState::~settingsState()
{
	delete this->ResolutionField;
	delete this->Menu;
}
//Functions
void settingsState::update()
{
	this->updateDeltaTime();
	this->updateMousePosition();
	this->updateButtons();
	this->updateMenu();
	switch (this->State)
	{
	//Window
	case 0:
		this->updateResolution();
		break;
	//Controls
	case 1:
		this->updateKeyBinds();
		break;
	//Music
	case 2:
		this->updateAudioVolume();
		break;
	}
}
void settingsState::render()
{
	this->stateData->Window->draw(this->Background);
	this->Menu->render(*this->stateData->Window);
	switch (this->State)
	{
	//Window
	case 0:
		this->renderResolution();
		break;
	//Controls
	case 1:
		this->renderKeyBinds();
		break;
	//Music
	case 2:
		this->renderAudioVolume();
		break;
	}

	this->renderButtons();
}
void settingsState::renderButtons()
{
	for (auto& i : this->Buttons) {
		i.second->render(this->stateData->Window);
	}
}
void settingsState::renderResolution()
{
	this->stateData->Window->draw(this->ResolutionHeader);
	this->ResolutionField->render(*this->stateData->Window);

}
void settingsState::renderAudioVolume()
{
	this->stateData->Window->draw(this->AudioVolumeHeader);
	this->AudioVolume->render(this->stateData->Window);
}
void settingsState::renderKeyBinds()
{
	for (auto &i : this->KeyBinds) {
		i->render(*this->stateData->Window);
	}

	for (auto& i : this->KeyBindName) {
		this->stateData->Window->draw(i);
	}
}
//Update
void settingsState::updateButtons()
{
	for (auto& i : this->Buttons) {
		i.second->update(&this->MouseViewPos);
	}

	if (this->Buttons["EXIT"]->getState() == ACTIVE) {
		this->Buttons["EXIT"]->setIdle();
		this->stateData->States->pop();
	}

	if (this->Buttons["APPLY"]->getState() == ACTIVE) {
		////READ FROM FILE
		//std::string TextFromFile[2];
		//std::fstream file("config/config.ini");
		//std::getline(file, TextFromFile[0]);
		//std::getline(file, TextFromFile[1]);
		//file.close();

		////SET MUSIC VOLUME
		//std::stringstream volume;
		//volume << this->AudioVolume->getVolume();
		//TextFromFile[1] = volume.str();

		//file.open("config/config.ini", std::ios::trunc | std::ios::out);
		//file << TextFromFile[0] << "\n";
		//file << TextFromFile[1] << "\n";
		//file.close();
		////SET RESOLUTION
		//short ResActiveOption = this->ResolutionField->getActive();

		//if (this->stateData->Window->getSize().x != this->VideoModes[ResActiveOption].x) {

		//	std::fstream plik("config/config.ini");
		//	plik << this->VideoModes[ResActiveOption].x << " " << this->VideoModes[ResActiveOption].y << "  ";
		//	plik.close();

		//	this->stateData->Window->create(sf::VideoMode(this->VideoModes[ResActiveOption].x, this->VideoModes[ResActiveOption].y), "SFML window", sf::Style::None);
		//	this->stateData->States->pop();
		//	this->stateData->States->top() = new menuState(this->stateData);
		//}
		std::fstream file;
		//Save settings from window
		short ResNum = this->ResolutionField->getActive();
		file.open("config/window.ini");
		file << this->VideoModes[ResNum].x * 34 << " " << this->VideoModes[ResNum].y * 34;
		file.close();
		//Save setting from audio
		std::stringstream Volume;
		Volume << this->AudioVolume->getVolume()*34;
		file.open("config/audio.ini");
		file << Volume.str();
		file.close();
		//Save setting from controls
		file.open("config/keybinds.ini");
		file << KeyBinds[0]->getBind()*34 <<" "<< KeyBinds[1]->getBind() * 34 <<" " << KeyBinds[2]->getBind() * 34 << " " << KeyBinds[3]->getBind() * 34;
		file.close();

		this->stateData->Window->create(sf::VideoMode(this->VideoModes[ResNum].x, this->VideoModes[ResNum].y), "E-Zine", sf::Style::None);
		this->stateData->States->pop();
		this->stateData->States->top() = new menuState(this->stateData);
	}
}
void settingsState::updateResolution()
{
	this->ResolutionField->update(this->MouseViewPos);
	this->ResolutionHeader.setPosition(this->ResolutionHeader.getPosition().x,
		100);
	this->ResolutionField->setPosition(this->ResolutionHeader.getPosition().x, this->ResolutionHeader.getPosition().y + this->ResolutionHeader.getGlobalBounds().height + 20);
}
void settingsState::updateAudioVolume()
{
	this->AudioVolume->update(&this->MouseViewPos);

	if (this->AudioVolume->getVolume()!= this->stateData->Music->getVolume()) {
		this->stateData->Music->setVolume(this->AudioVolume->getVolume());
	}
}
void settingsState::updateKeyBinds()
{
	for (auto& i : this->KeyBinds) {
		i->update(this->MouseViewPos);
	}
}
void settingsState::updateMenu()
{
	this->Menu->update(this->MouseViewPos);
	this->Menu->setPosition(this->stateData->WindowSize.x / 2 - 400,0);
	this->State = this->Menu->getActive();
}
//Initialization
void settingsState::iniGUI()
{
	this->iniBackground();
	this->iniButtons();
	this->iniResolution();
	this->iniAudioVolume();
	this->iniInsertKeys();
}
void settingsState::iniVariables()
{
	//Video Modes for setting
	this->VideoModes[0] = sf::Vector2u(1080,610);
	this->VideoModes[1] = sf::Vector2u(1280,720);
	this->VideoModes[2] = sf::Vector2u(1320,750);
	this->VideoModes[3] = sf::Vector2u(1480,840);
	this->VideoModes[4] = sf::Vector2u(1720,970);
	this->VideoModes[5] = sf::Vector2u(1920,1080);

	this->FramesLimit[0] = 60;
	this->FramesLimit[1] = 120;
	this->FramesLimit[2] = 144;
	this->FramesLimit[3] = 244;
	this->FramesLimit[4] = 0;
}
void settingsState::iniBackground()
{
	this->Background.setTexture(&this->stateData->Texture["BG2"]);
	this->Background.setSize(sf::Vector2f(this->stateData->Window->getSize().x, this->stateData->Window->getSize().y));
}
void settingsState::iniButtons()
{
	this->Buttons["EXIT"] = new button(this->stateData->Window->getSize().x / 2 - 170, this->stateData->Window->getSize().y - 100, 160, 70, this->stateData->Font, 25,
		"Back", sf::Vector3i(240, 230, 140), &this->stateData->Texture["BUTTON"], &this->stateData->dt);

	this->Buttons["APPLY"] = new button(this->stateData->Window->getSize().x / 2 + 10, this->stateData->Window->getSize().y - 100, 160, 70, this->stateData->Font, 25,
		"Apply", sf::Vector3i(240, 230, 140), &this->stateData->Texture["BUTTON"], &this->stateData->dt);

}
void settingsState::iniResolution()
{
	//Resoultion Header
	this->ResolutionHeader.setFont(*this->stateData->Font);
	this->ResolutionHeader.setString("Resolution");
	this->ResolutionHeader.setCharacterSize(25);
	this->ResolutionHeader.setFillColor(sf::Color(240, 230, 140));
	this->ResolutionHeader.setOutlineColor(sf::Color::Black);
	this->ResolutionHeader.setOutlineThickness(1);
	this->ResolutionHeader.setPosition(this->Menu->getPosition().x
		, this->Menu->getPosition().y + this->Menu->getGlobalBounds().height+20);

	//Checking what video mode is active and convering mode to string array
	int Active{};
	std::string Modes[6];
	for (int i = 0; i < 6; i++) {
		if (this->VideoModes[i].x == this->stateData->Window->getSize().x) {
			Active = i;
		}
		Modes[i] = std::to_string(this->VideoModes[i].x)+"x"+ std::to_string(this->VideoModes[i].y);
	}
	this->ResolutionField = new selectField(6,Modes,20,*this->stateData->Font,Active,this->ResolutionHeader.getGlobalBounds().left+ this->ResolutionHeader.getGlobalBounds().width+15
		, this->ResolutionHeader.getPosition().y+45);
}
void settingsState::iniAudioVolume()
{
	//Resoultion Header
	this->AudioVolumeHeader.setFont(*this->stateData->Font);
	this->AudioVolumeHeader.setString("Audio volume");
	this->AudioVolumeHeader.setCharacterSize(25);
	this->AudioVolumeHeader.setFillColor(sf::Color(240, 230, 140));
	this->AudioVolumeHeader.setOutlineColor(sf::Color::Black);
	this->AudioVolumeHeader.setOutlineThickness(1);
	this->AudioVolumeHeader.setPosition(this->Menu->getPosition().x
		, this->Menu->getPosition().y + this->Menu->getGlobalBounds().height + 50);

	this->AudioVolume = new slideField(this->AudioVolumeHeader.getPosition().x+ this->AudioVolumeHeader.getGlobalBounds().width+20, this->AudioVolumeHeader.getPosition().y+10
		,150,14,0,100,this->stateData->Music->getVolume());
}
void settingsState::iniInsertKeys()
{
	//KeyBindName
	for (auto &i : this->KeyBindName) {
		i.setFont(*this->stateData->Font);
		i.setCharacterSize(25);
		i.setFillColor(sf::Color(240, 230, 140));
		i.setOutlineColor(sf::Color::Black);
		i.setOutlineThickness(1);
	}
	this->KeyBindName[0].setString("Move up");
	this->KeyBindName[1].setString("Move down");
	this->KeyBindName[2].setString("Move left");
	this->KeyBindName[3].setString("Move right");

	this->KeyBindName[0].setPosition(this->Menu->getPosition().x, this->Menu->getPosition().y + this->Menu->getGlobalBounds().height + 60);
	this->KeyBindName[1].setPosition(this->Menu->getPosition().x, this->KeyBindName[0].getPosition().y + this->KeyBindName[1].getGlobalBounds().height +20);
	this->KeyBindName[2].setPosition(this->Menu->getPosition().x, this->KeyBindName[1].getPosition().y + this->KeyBindName[2].getGlobalBounds().height + 20);
	this->KeyBindName[3].setPosition(this->Menu->getPosition().x, this->KeyBindName[2].getPosition().y + this->KeyBindName[3].getGlobalBounds().height + 20);
	//Get KeyBinds from file
	std::fstream filee("config/keybinds.ini");
	short binds[4];
	filee >> binds[0];
	binds[0] /= 34;
	filee >> binds[1];
	binds[1] /= 34;
	filee >> binds[2];
	binds[2] /= 34;
	filee >> binds[3];
	binds[3] /= 34;
	filee.close();
	//Binds
	this->KeyBinds[0] = new insertField(this->KeyBindName[0].getPosition().x + 200, this->KeyBindName[0].getPosition().y,
		30,30, binds[0],*this->stateData->Font,23,this->stateData->Event);
	this->KeyBinds[1] = new insertField(this->KeyBindName[1].getPosition().x + 200, this->KeyBindName[1].getPosition().y,
		30,30, binds[1],*this->stateData->Font,23,this->stateData->Event);
	this->KeyBinds[2] = new insertField(this->KeyBindName[2].getPosition().x + 200, this->KeyBindName[2].getPosition().y,
		30,30, binds[2],*this->stateData->Font,23,this->stateData->Event);
	this->KeyBinds[3] = new insertField(this->KeyBindName[3].getPosition().x + 200, this->KeyBindName[3].getPosition().y,
		30,30, binds[3],*this->stateData->Font,23,this->stateData->Event);
}
void settingsState::iniMenu()
{
	std::string Menu[3]{ "Window ","Controls ","Audio" };
	this->Menu = new choiceField(3, Menu, 50, *this->stateData->Font, sf::Color(255, 255, 255), sf::Color(125, 125, 125),
		0, this->stateData->WindowSize.x / 2 - 400, 0, false);
}