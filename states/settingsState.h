#pragma once
#include "state.h"
#include "../fields/button.h"
#include "../fields/choiceField.h"
#include "menuState.h"
#include "../fields/slideField.h"
#include "../fields/insertField.h"
#include "../fields/selectField.h"

class settingsState;
class choiceField;
class slideField;
class insertField;

class settingsState :
    public state
{
private:
    //Background
    sf::RectangleShape Background;
    //Menu to chosse type of options
    choiceField* Menu;
    //Window
    sf::Vector2u VideoModes[6];
    short FramesLimit[5];
    
    sf::Text ResolutionHeader;
    selectField* ResolutionField;
    //Audio
    sf::Text AudioVolumeHeader;
    slideField* AudioVolume;

    //KeyBinds
    sf::Text KeyBindName[4];
    insertField* KeyBinds[4];
    
    unsigned short State{};
    //Save and Exit button
    std::map <std::string, button*> Buttons;
public:
    //Constructor and Destructor
    settingsState(StateData *stateData);
    ~settingsState();
    //Functions
    void update();
    void render();

    void renderButtons();
    void renderResolution();
    void renderAudioVolume();
    void renderKeyBinds();
     
    void updateButtons();
    void updateResolution();
    void updateAudioVolume();
    void updateKeyBinds();
    void updateMenu();
    //Initialization
    void iniGUI();

    void iniVariables();
    void iniBackground();
    void iniButtons();
    void iniResolution();
    void iniAudioVolume();
    void iniInsertKeys();
    void iniMenu();
};

