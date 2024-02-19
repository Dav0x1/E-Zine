#include "../stdafx.h"
#include "GameState.h"

//Constructor and Destructor
GameState::GameState(StateData* stateData)
	:state(stateData)
{
	this->initVariables();
	this->initView();
	this->initRender();
	this->initTileMap();
	this->initPlayer();
	this->initPlayerInfo();
	this->initShops();
	this->initHerd();

}
GameState::~GameState()
{
	delete this->Player;
	delete this->Map;
	delete this->PlayerInfo;
}
//Main Functions
void GameState::update()
{
	this->updateInput();
	this->updateDeltaTime();
	this->updateEntitiesMove();
	this->updateFps();
	this->updateMousePosition(&this->View);
	this->updateKeyTime();
	this->updateView();
	this->updatePlayerCollision();
	this->updateEntityCollision();
	this->updatePlayerShotCollision();
	this->updatePlayer();
	this->updateEntities();
	this->updateShops();
	this->updatePlayerInfo();
}
void GameState::render()
{
	this->RenderTexture.clear();

	this->RenderTexture.setView(this->View);
	//Render in View
	this->renderMap(&this->RenderTexture);
	this->renderPlayer(&this->RenderTexture);
	this->renderEntities(&this->RenderTexture);
	this->renderObverseMap(&this->RenderTexture);
	this->RenderTexture.setView(this->RenderTexture.getDefaultView());
	//Render in Window
	this->RenderTexture.draw(this->fps);
	this->renderShops(&this->RenderTexture);
	this->renderPlayerInfo(&this->RenderTexture);
	//FINAL RENDER
	this->RenderTexture.display();
	this->RenderSprite.setTexture(this->RenderTexture.getTexture());
	this->stateData->Window->draw(this->RenderSprite);
}
//Initialization
void GameState::initVariables()
{
	this->RenderLimit = 8;
}
void GameState::initView()
{
	this->View.setSize((float)this->stateData->Window->getSize().x, (float)this->stateData->Window->getSize().y);
	this->View.zoom(0.7f);
}
void GameState::initRender()
{
	this->RenderTexture.create(this->stateData->Window->getSize().x, this->stateData->Window->getSize().y);

	this->RenderSprite.setTexture(this->RenderTexture.getTexture());
	this->RenderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->Window->getSize().x, this->stateData->Window->getSize().y));
}
void GameState::initTileMap()
{
	this->Map = new TileMap("resources/map.txt", this->stateData->Texture["MAP"]);
}
void GameState::initPlayer()
{
	this->Player = new player(this->stateData->Texture["PLAYER"], sf::Vector2f(750.f, 550.f), this->stateData->Texture["ITEMS"]);
}
void GameState::initPlayerInfo()
{
	this->PlayerInfo = new playerInfo(this->stateData->Window->getSize(), *this->stateData->Font, this->Player->getStatsPointer(), this->stateData->Texture["ITEMS"], &this->ShopActive, sf::IntRect(0, 0, 500, 500));
}
void GameState::initShops()
{
	int* money = &this->Player->getStatsPointer()->money;
	this->Shops.push_back(new shop(*this->stateData->Font, "Armors", sf::FloatRect(20 * 50, 8 * 50, 50, 50), this->stateData->Window->getSize(), &this->stateData->Items, 0, this->PlayerInfo->getBackpackPointer(), money, this->PlayerInfo->getSize()));
	this->Shops.push_back(new shop(*this->stateData->Font, "Staffs", sf::FloatRect(29 * 50, 8 * 50, 50, 50), this->stateData->Window->getSize(), &this->stateData->Items, 1, this->PlayerInfo->getBackpackPointer(), money, this->PlayerInfo->getSize()));
	this->Shops.push_back(new shop(*this->stateData->Font, "Hats", sf::FloatRect(20 * 50, 6 * 50, 50, 50), this->stateData->Window->getSize(), &this->stateData->Items, 2, this->PlayerInfo->getBackpackPointer(), money, this->PlayerInfo->getSize()));
	this->Shops.push_back(new shop(*this->stateData->Font, "Boots", sf::FloatRect(29 * 50, 6 * 50, 50, 50), this->stateData->Window->getSize(), &this->stateData->Items, 3, this->PlayerInfo->getBackpackPointer(), money, this->PlayerInfo->getSize()));
	this->Shops.push_back(new shop(*this->stateData->Font, "Rings", sf::FloatRect(22 * 50, 4 * 50, 300, 40), this->stateData->Window->getSize(), &this->stateData->Items, 4, this->PlayerInfo->getBackpackPointer(), money, this->PlayerInfo->getSize()));

}
void GameState::initHerd()
{
	this->Texture.loadFromFile("resources/image/Entity.png");
	EntityParameters Parameters{ "Orc Micha³a",sf::IntRect(0,0,58,58),sf::Vector2i(15,15),sf::IntRect(7,2,40,54),500,50,50,50,25 };
	this->Entities.push_back(new entityHerd(Texture, *this->stateData->Font, 1, 10, Parameters, sf::IntRect(28, 14, 5, 6)));
}
//Render
void GameState::renderMap(sf::RenderTarget* Target)
{
	this->Map->render(*Target, this->Player->getPosition(), this->RenderLimit);
}
void GameState::renderObverseMap(sf::RenderTarget* Target)
{
	this->Map->renderObverse(*Target, this->Player->getPosition(), this->RenderLimit);
}
void GameState::renderPlayerInfo(sf::RenderTarget* Target)
{
	this->PlayerInfo->render(Target);
}
void GameState::renderShops(sf::RenderTarget* Target)
{
	for (auto& i : this->Shops) {
		i->render(Target);
	}
}
void GameState::renderEntities(sf::RenderTarget* Target)
{
	for (auto& i : this->Entities) {
		i->render(*Target);
	}
}
void GameState::renderPlayer(sf::RenderTarget* Target)
{
	this->Player->render(*Target);
}
//Update
void GameState::updateInput()
{
	//MOVE
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->Player->move(-1.f, 0.f, this->stateData->dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->Player->move(1.f, 0.f, this->stateData->dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->Player->move(0.f, -1.f, this->stateData->dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->Player->move(0.f, 1.f, this->stateData->dt);
}
void GameState::updatePlayer()
{
	this->Player->update(this->stateData->dt, this->MouseViewPos, this->PlayerInfo->getPointerToStaffSlot(), &this->stateData->ShotsOffset);
}
void GameState::updateView()
{
	this->View.setCenter(
		std::floor(this->Player->getPosition().x + this->Player->getSize().x / 2) + 125,
		std::floor(this->Player->getPosition().y + this->Player->getSize().y / 2)
	);
}
void GameState::updatePlayerCollision()
{
	this->Map->checkCollision(this->Player, this->stateData->dt);
}
void GameState::updateEntityCollision()
{
	for (auto& i : this->Entities) {
		this->Map->checkEntityCollision(i->GetPointerToEntities(), this->stateData->dt);
	}
}
void GameState::updatePlayerShotCollision()
{
	//Check Collision with Tiles
	this->Map->checkShotsCollision(this->Player->GetProjectilesPointer(), this->stateData->dt);
	//Check Collision with Entities
	for (auto& i : this->Entities) {
		if (i->checkShotsCollision(this->Player->GetProjectilesPointer(), &this->Player->getStatsPointer()->money)) { break; }
	}
}
void GameState::updateShops()
{
	bool isActive = false;
	for (auto& i : this->Shops) {
		i->update(this->Player->getGlobalBounds(), this->MouseWindowPos);
		if (i->isActive())isActive = true;
	}
	this->ShopActive = isActive;

}
void GameState::updateEntities()
{
	for (auto& i : this->Entities) {
		i->updateEntities(this->stateData->dt);
	}
}
void GameState::updateEntitiesMove()
{
	for (auto& i : this->Entities) {
		i->updateEntitiesMove(this->stateData->dt, this->Player->getGlobalBounds());
	}
}
void GameState::updatePlayerInfo()
{
	this->PlayerInfo->update(&this->MouseWindowPos);
}
//Other
