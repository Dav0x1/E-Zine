#include "../stdafx.h"
#include "editMapState.h"

//Constructors and destructors
editMapState::editMapState(StateData* stateData):
	state(stateData)
{
	//Default Values
	this->MaxScrollAmount = 0;
	this->BarTileSize = 50;
	this->GridSize = 50;
	this->Collision = false;
	this->Obverse = false;
	this->CollisionOffSet = sf::FloatRect(0,0,0,0);
	//Initialization
	this->initTexture();
	this->initView();

	this->initTileInfo();

	this->initTileMap();
	this->initGui();
	this->initTiles();
}
editMapState::~editMapState()
{
	delete this->tileMap;

	for (auto& i : this->BarTiles) {
		delete i;
	}
}
//Main Functions
void editMapState::update()
{
	this->updateDeltaTime();
	this->updateKeyTime();
	this->updateMousePosition(&this->View);
	this->updateGridMousePos();
	this->updateInput();
	this->updateGui();
	this->updateTileInfo();
	this->updateScroll();
	this->updateRect();
}
void editMapState::render()
{
	this->stateData->Window->setView(this->View);
	this->renderTileMap();
	this->renderChoiceRect();
	this->stateData->Window->setView(this->stateData->Window->getDefaultView());
	this->renderTileInfo();
	this->renderGui();
	this->renderTiles();
}
//Initialization
void editMapState::initTileMap()
{
	this->tileMap = new TileMap(this->GridSize,50,40);
}
void editMapState::initTexture()
{
	this->stateData->Texture["TILE_TEXTURE"].loadFromFile("resources/image/mapTexture.png");
}
void editMapState::initGui()
{
	//Tiles Background
	this->BarBackground.setPosition(0, this->stateData->Window->getSize().y - this->BarTileSize - 10);
	this->BarBackground.setSize(sf::Vector2f(this->stateData->Window->getSize().x, this->BarTileSize +10));
	this->BarBackground.setFillColor(sf::Color::Black);
	this->BarBackground.setOutlineThickness(2);
	this->BarBackground.setOutlineColor(sf::Color(90,90,90));
	//Rect
	this->ChoiceRect.setOutlineColor(sf::Color::Green);
	this->ChoiceRect.setOutlineThickness(1);
	this->ChoiceRect.setSize(sf::Vector2f(this->GridSize,this->GridSize));
	this->ChoiceRect.setTexture(&this->stateData->Texture["TILE_TEXTURE"]);
	this->ChoiceRect.setTextureRect(sf::IntRect(0,0,50,50));

	this->CollisionRect.setFillColor(sf::Color(255,0,0,100));

	//CurrentTileInfo
	this->SettingsInfo.setFont(*this->stateData->Font);
	this->SettingsInfo.setCharacterSize(14);
	this->SettingsInfo.setPosition(this->stateData->Window->getSize().x-this->SettingsInfo.getGlobalBounds().width,0);
}
void editMapState::initTileInfo()
{
	this->BackgroundTileInfo.setPosition(100,100);
	this->BackgroundTileInfo.setSize(sf::Vector2f(80,30));
	this->BackgroundTileInfo.setFillColor(sf::Color(125, 125, 125, 100));

	this->TileInfo.setFont(*this->stateData->Font);
	this->TileInfo.setFillColor(sf::Color(200,200,200));
	this->TileInfo.setCharacterSize(10);
}
void editMapState::initTiles()
{
	int amount{ 95 };
	for (int i = 0; i < amount; i++) {
		this->BarTiles.push_back(new sf::RectangleShape);
		this->BarTiles[i]->setTexture(&this->stateData->Texture["TILE_TEXTURE"]);
		this->BarTiles[i]->setTextureRect(sf::IntRect( i*51 ,0, 50 ,50));
		this->BarTiles[i]->setSize(sf::Vector2f(this->BarTileSize, this->BarTileSize));
		this->BarTiles[i]->setPosition(i* this->BarTileSize +(5*(i+1)),
			this->BarBackground.getPosition().y + this->BarBackground.getSize().y/2 - this->BarTileSize /2);
	}
	if ((this->BarTiles[this->BarTiles.size() - 1]->getPosition().x + this->BarTiles[this->BarTiles.size() - 1]->getSize().x) - this->stateData->Window->getSize().x > 0) {
		this->MaxScrollAmount = ((this->BarTiles[this->BarTiles.size() - 1]->getPosition().x + this->BarTiles[this->BarTiles.size() - 1]->getSize().x) - this->stateData->Window->getSize().x)/10;
	}
}
void editMapState::initView()
{
	this->View.setSize(this->stateData->Window->getSize().x, this->stateData->Window->getSize().y);
	this->View.setCenter(this->stateData->Window->getSize().x/2, this->stateData->Window->getSize().y / 2);
}
//Render
void editMapState::renderTileMap()
{
	this->tileMap->render(*this->stateData->Window);
}
void editMapState::renderGui()
{
	this->stateData->Window->draw(this->BarBackground);

	//GUI CurrentTileInfo
	this->stateData->Window->draw(this->SettingsInfo);
}
void editMapState::renderTiles()
{
	for (auto &i : this->BarTiles) {
		this->stateData->Window->draw(*i);
	}
}
void editMapState::renderTileInfo()
{
	this->stateData->Window->draw(this->BackgroundTileInfo);
	this->stateData->Window->draw(this->TileInfo);
}
void editMapState::renderChoiceRect()
{
	this->stateData->Window->draw(this->ChoiceRect);
	if (this->Collision) {
		this->stateData->Window->draw(this->CollisionRect);
	}
}
//Update
void editMapState::updateGridMousePos()
{
	this->GridMousePos.x = int(this->MouseViewPos.x /this->GridSize);
	this->GridMousePos.y = int(this->MouseViewPos.y/this->GridSize);}
void editMapState::updateInput()
{
	//Mouse click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//ADD TILE
		if(!this->BarBackground.getGlobalBounds().contains(sf::Vector2f(this->MouseWindowPos.x, this->MouseWindowPos.y)) && this->getKeyTime())
			this->tileMap->addTile(this->GridMousePos.x,this->GridMousePos.y,this->ChoiceRect.getTextureRect(),this->stateData->Texture["TILE_TEXTURE"],this->CollisionOffSet, this->Collision, this->Obverse);
		//PICK ONE OF TILES
		else {
			for (auto& i : this->BarTiles) {
				if (i->getGlobalBounds().contains(sf::Vector2f(this->MouseWindowPos.x, this->MouseWindowPos.y))) {
					this->ChoiceRect.setTextureRect(i->getTextureRect());
				}
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {
		this->tileMap->removeTile(this->GridMousePos.x, this->GridMousePos.y);
	}
	//KEY PRESS CHECK
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && this->getKeyTime()) {
		if (this->Collision)this->Collision = false;
		else this->Collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->getKeyTime()) {
		this->tileMap->saveToFile("resources/map.txt");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && this->getKeyTime()) {
		this->tileMap->loadFromFile("resources/map.txt",this->stateData->Texture["TILE_TEXTURE"]);
	}
	//CAMERA MOVEMENT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->View.move(-2.f,0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->View.move(2.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->View.move(0.f, -2.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) {
		this->View.move(0.f, 2.f);
	}

//OffSet Control
	//OffSet Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && this->getKeyTime()) {
		this->CollisionOffSet.left++;
	}
	//OffSet Top
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && this->getKeyTime()) {
		this->CollisionOffSet.top++;
	}
	//OffSet Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && this->getKeyTime()) {
		this->CollisionOffSet.width++;
	}
	//OffSet Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && this->getKeyTime()) {
		this->CollisionOffSet.height++;
	}
	//Clear OffSet
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5) && this->getKeyTime()) {
		this->CollisionOffSet = sf::FloatRect(0, 0, 0, 0);
	}

	//Obverse
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && this->getKeyTime()) {
		if (this->Obverse)this->Obverse = false;
		else this->Obverse = true;
	}
}
void editMapState::updateRect()
{
	this->ChoiceRect.setPosition(this->GridMousePos.x*this->GridSize, this->GridMousePos.y * this->GridSize);
	this->CollisionRect.setPosition(this->ChoiceRect.getPosition().x+this->CollisionOffSet.left, this->ChoiceRect.getPosition().y + this->CollisionOffSet.top);
	this->CollisionRect.setSize(sf::Vector2f(this->ChoiceRect.getSize().x - this->CollisionOffSet.width - this->CollisionOffSet.left, this->ChoiceRect.getSize().y - this->CollisionOffSet.height - this->CollisionOffSet.top));
}
void editMapState::updateGui()
{
	if(this->Collision)
		this->ChoiceRect.setOutlineColor(sf::Color::Red);
	else
		this->ChoiceRect.setOutlineColor(sf::Color::Green);
	//GUI CurrentTileInfo
	std::stringstream temp;
	temp << "Collision (Press C): " << this->Collision << "\n"
		<< "Save to File (Press S) " << "\n"
		<< "Load From File (Press L) "<< "\n"
		<< "Obverse (Press O): " << this->Obverse;
	this->SettingsInfo.setString(temp.str());
	this->SettingsInfo.setPosition(this->stateData->Window->getSize().x - this->SettingsInfo.getGlobalBounds().width, 0);

}
void editMapState::updateTileInfo()
{
	std::stringstream temp;
	temp << "x:" << this->GridMousePos.x << " y:" << this->GridMousePos.y << "\n"
		<< "layers:" << this->tileMap->getLayersQuantity(this->GridMousePos.x, this->GridMousePos.y) << "\n";
	this->TileInfo.setString(temp.str());

	float x, y;
	x = this->MouseWindowPos.x+50;
	y = this->MouseWindowPos.y;
	if (x < 0)
		x = 0;
	else if (x + this->BackgroundTileInfo.getSize().x > this->stateData->Window->getSize().x)
		x = this->stateData->Window->getSize().x - this->BackgroundTileInfo.getSize().x;
	if (y < 0)
		y = 0;
	else if (y + this->BackgroundTileInfo.getSize().y > this->stateData->Window->getSize().y-this->BarBackground.getSize().y)
		y = this->stateData->Window->getSize().y - this->BackgroundTileInfo.getSize().y - this->BarBackground.getSize().y;
	this->BackgroundTileInfo.setPosition(x,y);

	this->TileInfo.setPosition(this->BackgroundTileInfo.getPosition().x+5, this->BackgroundTileInfo.getPosition().y+3);
}
void editMapState::updateScroll()
{
	if (this->stateData->Event->type == sf::Event::MouseWheelScrolled)
	{
		if (this->stateData->Event->mouseWheelScroll.delta > 0)
		{
			//UP
			if (this->CurrentScrollAmount > 0) {
				this->CurrentScrollAmount--;
				for (auto& i : this->BarTiles) {
					i->setPosition(i->getPosition().x + 100, i->getPosition().y);
				}
				//-
			}
			this->stateData->Event->mouseWheelScroll.delta = 0;
		}
		else if (this->stateData->Event->mouseWheelScroll.delta < 0)
		{
			//DOWN
			if (this->CurrentScrollAmount <= this->MaxScrollAmount) {
				this->CurrentScrollAmount++;
				for (auto& i : this->BarTiles) {
					i->setPosition(i->getPosition().x - 100, i->getPosition().y);
				}
				//-
			}
			this->stateData->Event->mouseWheelScroll.delta = 0;
		}
	}
}