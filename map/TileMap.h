#pragma once

#include "Tile.h"
#include "../entity/player.h"
#include "../entity/projectile.h"
#include "../entity/entity.h"

class TileMap
{
private:
	//Map Variables
	int TileSize;
	int Width;
	int Height;

	std::vector< std::vector< std::vector< Tile* > > > board;
	//Render Variables
	int FromX;
	int FromY;
	int ToX;
	int ToY;

	sf::RectangleShape x;
	//Initialization
	//Update
	//Render
public:
	//Constructors and destructors
	TileMap(unsigned int TileSize, unsigned int Width, unsigned int Height);
	TileMap(std::string filePath, sf::Texture& Texture);
	~TileMap();
	//Main Functions
	void update();
	void render(sf::RenderTarget& target);
	void render(sf::RenderTarget& targetm, sf::Vector2f center, int renderLimit);
	void renderObverse(sf::RenderTarget& targetm, sf::Vector2f center, int renderLimit);
	//Accessors
	int getLayersQuantity(int x, int y);
	bool getCollision(int x, int y);
	bool getObverse(int x, int y);
	//Modifiers
	void addTile(int x,int y,sf::IntRect textureRect, sf::Texture& texture, sf::FloatRect OffSet, bool Collision, bool Obverse);
	void removeTile(int x, int y);
	//Other
	void saveToFile(std::string filePath);
	void loadFromFile(std::string filePath, sf::Texture& Texture);
	void checkCollision(player *entity, float dt);
	void checkEntityCollision(std::vector<entity *> *Entity, float dt);
	void checkShotsCollision(std::vector<projectile*> *Projectiles, float dt);
};