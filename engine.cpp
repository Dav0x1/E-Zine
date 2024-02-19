#include "stdafx.h"
#include "engine.h"
//Constructor and Destructor
engine::engine()
{
	this->Window = new sf::RenderWindow(sf::VideoMode(this->stateData.WindowSize.x, this->stateData.WindowSize.y,1), "RPG", sf::Style::None);
	this->iniFont();
	this->iniTexture();
	this->iniMusic();
	this->iniStateData();
	this->iniState();
	this->iniItemsDetails();
}
engine::~engine()
{
	delete this->Window;
}
//Functions
void engine::loop()
{
	while (!this->States.empty())
	{
		this->render();
		this->update();
	}
}
void engine::render()
{
	this->Window->clear();

	if (!this->States.empty())
		this->States.top()->render();

	this->Window->display();
}
void engine::update()
{
	this->poolEvent();

	if (!this->States.empty()	&& this->Window->hasFocus())
		this->States.top()->update();
}
void engine::poolEvent()
{
	while (this->Window->pollEvent(this->Event)) {
		switch (this->Event.type)
		{
		case sf::Event::Closed:
			this->Window->close();
			break;
		}
	}
}
//Initizalization
void engine::iniFont()
{
	if (!this->Font.loadFromFile("resources/font.ttf")) {
		std::cout << "ENGINE::FONT::LOAD::ERROR"<<std::endl;
	}
}
void engine::iniState()
{
	//Uncomment for game
	this->States.push(new menuState(&this->stateData));
	//Temporary for making tileMap
	//this->States.push(new editMapState(&this->stateData));
}
void engine::iniMusic()
{
	this->Music.openFromFile("resources/music/music.ogg");

	float volume{};
	std::string voidBuffert;

	this->Music.setVolume(this->stateData.Volume);
	this->Music.setLoop(true);
	this->Music.play();
}
void engine::iniTexture()
{
	this->stateData.Texture["BUTTON"].loadFromFile("resources/image/button.png");
	this->stateData.Texture["BACKGROUND"].loadFromFile("resources/image/background.png");
	this->stateData.Texture["MAP"].loadFromFile("resources/image/mapTexture.png");
	this->stateData.Texture["PLAYER"].loadFromFile("resources/image/playerTexture.png");
	this->stateData.Texture["ITEMS"].loadFromFile("resources/image/items.png");
	this->stateData.Texture["BG2"].loadFromFile("resources/image/bg2.png");
}
void engine::iniStateData()
{
	this->stateData.Window = this->Window;
	this->stateData.Event = &this->Event;
	this->stateData.Font = &this->Font;
	this->stateData.Music = &this->Music;
	this->stateData.States = &this->States;
}
void engine::iniItemsDetails()
{
	//Robes | TypeId | Id | name | maxdmg | mindmg | def | hp | mp | spd | att | attspd | cost | sell |  texturePos(x,y)
	{
		this->stateData.Items.push_back(new rpg::Item{ 0,0,"Wooden Robe",0,0,5,10,5,0,0,0,10,5,sf::Vector2f(0,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,1,"Ordinary Robe",0,0,15,56,15,0,1,1,90,34,sf::Vector2f(40,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,2,"Blue Dragon Robe",0,0,27,94,20,5,4,4,230,100,sf::Vector2f(80,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,3,"Tomb Robe",0,0,48,153,35,9,7,9,450,202,sf::Vector2f(120,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,4,"Clown Robe",0,0,68,180,45,14,8,14,720,453,sf::Vector2f(160,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,5,"Dark Robe",0,0,80,220,55,18,11,14,900,500,sf::Vector2f(200,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,6,"Night Robe",0,0,92,245,60,24,15,13,1150,550,sf::Vector2f(240,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,7,"Epic Robe",0,0,103,270,75,27,21,21,1570,650,sf::Vector2f(280,0) });
		this->stateData.Items.push_back(new rpg::Item{ 0,8,"Gold Robe",0,0,234,400,95,45,25,30,2100,1750,sf::Vector2f(320,0) });
	}
	//Staff | TypeId | Id | name | maxdmg | mindmg | def | hp | mp | spd | att | attspd | cost | sell | texturePos(x,y)
	{
		this->stateData.Items.push_back(new rpg::Item{ 1,9,"Staff 1",10,5,0,0,0,0,0,0,11,10,sf::Vector2f(0,40) });
		this->stateData.ShotsOffset[9] = sf::IntRect(0, 15, 40, 10);
		this->stateData.Items.push_back(new rpg::Item{ 1,10,"Staff 2",50,40,0,0,0,3,0,0,57,42,sf::Vector2f(40,40) });
		this->stateData.ShotsOffset[10] = sf::IntRect(5, 5, 30, 30);
		this->stateData.Items.push_back(new rpg::Item{ 1,11,"Staff 3",12,32,0,0,5,2,5,0,89,55,sf::Vector2f(80,40) });
		this->stateData.ShotsOffset[11] = sf::IntRect(10, 10, 20, 20);
		this->stateData.Items.push_back(new rpg::Item{ 1,12,"Staff 4",58,90,0,0,5,2,5,5,120,89,sf::Vector2f(120,40) });
		this->stateData.ShotsOffset[12] = sf::IntRect(0, 5, 40, 30);
		this->stateData.Items.push_back(new rpg::Item{ 1,13,"Staff 5",188,242,0,0,8,4,8,8,240,120,sf::Vector2f(160,40) });
		this->stateData.ShotsOffset[13] = sf::IntRect(0, 5, 40, 30);
		this->stateData.Items.push_back(new rpg::Item{ 1,14,"Staff 5",188,242,0,0,8,4,8,8,240,120,sf::Vector2f(200,40) });
		this->stateData.ShotsOffset[14] = sf::IntRect(0, 5, 40, 30);
		this->stateData.Items.push_back(new rpg::Item{ 1,15,"Staff 5",188,242,0,0,8,4,8,8,240,120,sf::Vector2f(240,40) });
		this->stateData.ShotsOffset[15] = sf::IntRect(0, 5, 40, 30);
		this->stateData.Items.push_back(new rpg::Item{ 1,16,"Staff 5",700,600,0,0,8,4,8,130,240,120,sf::Vector2f(280,40) });
		this->stateData.ShotsOffset[16] = sf::IntRect(0, 5, 40, 30);
	}
	//Hat | TypeId | Id | name | maxdmg | mindmg | def | hp | mp | spd | att | attspd | cost | sell | texturePos(x,y)
	{
		this->stateData.Items.push_back(new rpg::Item{ 2,17,"Hat 1",0,0,0,2,0,2,0,0,0,0,sf::Vector2f(0,120) });
		this->stateData.Items.push_back(new rpg::Item{ 2,18,"Hat 2",0,0,0,3,0,3,0,0,0,0,sf::Vector2f(40,120) });
	}
	//Boots | TypeId | Id | name | maxdmg | mindmg | def | hp | mp |spd | att |	attspd | cost | sell | texturePos(x,y)
	{
		this->stateData.Items.push_back(new rpg::Item{ 3,43,"Boots of Burning Vengeance",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(0,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,44,"Footguards of Fleeting Damnation",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(40,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,45,"Ivory Warboots of Imminent Whispers",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(80,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,46,"Mail Feet of Hellish Misery",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(120,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,47,"Fierce Chain Stompers",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(160,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,48,"Destiny's Golden Greaves",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(200,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,49,"Malignant Mail Footguards",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(240,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,50,"Wind-Forged Sabatons of Dark Powers",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(280,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,51,"Sabatons of Eternal Damnation",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(320,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,52,"Frost Sabatons of the Talon",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(360,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,53,"Fire Infused Embroided Sandals",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(400,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,54,"Heavy Hide Walkers of Holy Fortune",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(440,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,55,"Warlord's Footguards of Darkness",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(480,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,56,"Jade Infused Heels of Nature",0,0,4,0,4,4,0,0,0,0,sf::Vector2f(520,160) });
		this->stateData.Items.push_back(new rpg::Item{ 3,57,"Linen Boots of Eternal Justice",0,0,0,6,0,500,0,0,0,0,sf::Vector2f(560,160) });
	}
	//Rings | TypeId | Id | name | maxdmg | mindmg | def | hp | mp |spd | att |	attspd | cost | sell | texturePos(x,y)
	{
		this->stateData.Items.push_back(new rpg::Item{ 4,58,"Draupnir",0,0,	0,0,2,0,1,0,10,0,sf::Vector2f(0,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,59,"Tupsimati",0,0,0,5,5,1,3,0,40,20,sf::Vector2f(40,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,60,"Orloff",0,0,0,15,15,5,4,0,90,45,sf::Vector2f(80,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,61,"Kosmocholor",0,0,0,15,25,5,9,0,180,190,sf::Vector2f(120,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,62,"Magus Ring",0,0,0,25,53,7,0,0,290,150,sf::Vector2f(160,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,63,"Bandit King's",0,0,0,35,45,10,9,0,472,200,sf::Vector2f(200,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,64,"Lookout Ring",	0,0,5,55,54,14,15,0,652,300,sf::Vector2f(240,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,65,"Thunder Crystal",0,0,7,65,55,21,25,2,962,400,sf::Vector2f(280,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,66,"Unicorn Amulet",0,0,12,75,67,24,32,5,1402,700,sf::Vector2f(320,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,67,"Soul Amulet",	0,0,15,82,80,25,45,9,1700,900,sf::Vector2f(360,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,68,"Earth Crystal",0,0,18,90,90,25,50,15,1921,1000,sf::Vector2f(400,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,69,"Fire Crystal",	0,0,21,97,105,0,52,22,2152,1100,sf::Vector2f(440,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,70,"Confusion Amulet",0,0,25,104,125,26,52,27,2301,1250,sf::Vector2f(480,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,71,"Paralysis Amulet",0,0,28,130,132,27,65,35,2702,1500,sf::Vector2f(520,200) });
		this->stateData.Items.push_back(new rpg::Item{ 4,72,"Puri Amulet",0,0,40,180,175,32,93,37,5423,5423,sf::Vector2f(560,200) });
	}
}