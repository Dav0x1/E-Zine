#pragma once
#include "state.h"
#include "../fields/button.h"
#include "settingsState.h"
#include "GameState.h"

class menuState :
    public state
{
private:
    //GUI
    sf::RectangleShape Background;
    std::map <std::string, button *> Buttons;
public:
    //Constructor and Destructor
    menuState(StateData *stateData);
    ~menuState();
    //Functions
    void update();
    void render();

    void renderButtons();
    void renderGUI();

    void updateButtons();
    //Initialization
    void iniButtons();
    void iniGUI();
};