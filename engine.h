 #pragma once
#include "states/menuState.h"
#include "states/editMapState.h"

class engine
{
private:
	sf::RenderWindow* Window;
	sf::Event Event;
	sf::Font Font;
	sf::Music Music;
	std::stack<state*> States;
	
	StateData stateData;
public:
	//Constructor and Destructor
	engine();
	~engine();
	//Functions
	void loop();
	void render();
	void update();
	void poolEvent();
	//Initizalization
	void iniFont();
	void iniState();
	void iniMusic();
	void iniTexture();
	void iniStateData();
	void iniItemsDetails();
};