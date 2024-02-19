#pragma once

class state;
class StateData;

class StateData
{
public:
	//Variables
	sf::RenderWindow* Window = NULL;
	sf::Event* Event = NULL;
	sf::Font* Font = NULL;
	sf::Music* Music = NULL;
	std::stack<state*>* States = NULL;
	std::map <std::string, sf::Texture> Texture;
	float dt = 1;
	sf::Vector2u WindowSize;
	unsigned int Volume;

	std::vector<rpg::Item *> Items;
	std::map<int, sf::IntRect> ShotsOffset;
	//Constructor and Descructor
	StateData(){
		std::fstream file("config/config.ini");
			short width, height;
			file >> this->WindowSize.x >> this->WindowSize.y;
			file >> this->Volume;
		file.close();
	};
	~StateData() {
	};
};

class state
{
protected:
	StateData* stateData;

	sf::Vector2i MouseWindowPos;
	sf::Vector2f MouseViewPos;

	float keyTime;
	float keyTimeMax;

	sf::Clock dtClock;
	sf::Text fps;
	float fpsUpdateDelay;
public:
	//Constructor and Destructor
	state(StateData* stateData);
	~state();
	//Functions
	void updateMousePosition(sf::View* View = NULL);
	void updateDeltaTime();
	void updateKeyTime();
	void updateFps();

	bool getKeyTime();
	virtual void render() = NULL;
	virtual void update() = NULL;
};

