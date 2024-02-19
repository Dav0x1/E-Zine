#include "../stdafx.h"
#include "TileMap.h"
//Constructors and destructors
TileMap::TileMap(unsigned int TileSize, unsigned int Width, unsigned int Height)
{
	this->FromX = 0;
	this->FromY = 0;
	this->ToX = 0;
	this->ToY = 0;

	this->TileSize = TileSize;
	this->Width = Width;
	this->Height = Height;


	//Board initialization
	this->board.resize(this->Width, std::vector< std::vector< Tile* > >());
	for (size_t x = 0; x < this->Width ; x++) {
		for (size_t y = 0; y < this->Height; y++) {
			this->board[x].resize(this->Height, std::vector< Tile* >());
		}
	}
}
TileMap::TileMap(std::string filePath, sf::Texture& Texture)
{
	this->x.setOutlineThickness(2);
	this->x.setFillColor(sf::Color::Transparent);
	this->FromX = 0;
	this->FromY = 0;
	this->ToX = 0;
	this->ToY = 0;

	//Files Structure:
	//TileSize Width Height
	//Collision TexturePosX PosX PosY OffSetLeft OffSetTop OffSetDown OffSetRight Obverse[...]

	std::ifstream file(filePath);
	file >> this->TileSize >> this->Width >> this->Height;
	//Board initialization
	this->board.resize(this->Width, std::vector< std::vector< Tile* > >());
	for (size_t x = 0; x < this->Width; x++) {
		for (size_t y = 0; y < this->Height; y++) {
			this->board[x].resize(this->Height, std::vector< Tile* >());
		}
	}
	//Create tiles
	int TexturePosX{}, PosX{}, PosY{}, OffSetTop{}, OffSetLeft{}, OffSetDown{}, OffSetRight{};
	bool Obverse, Collision;

	while (file >> Collision >> TexturePosX >> PosX >> PosY>> OffSetLeft>> OffSetTop >> OffSetDown >> OffSetRight>>Obverse) {
		this->board[PosX][PosY].push_back(new Tile(this->TileSize, PosX * this->TileSize, PosY * this->TileSize, Texture,
													sf::IntRect(TexturePosX, 0, this->TileSize, this->TileSize), sf::FloatRect(OffSetLeft, OffSetTop, OffSetRight, OffSetDown), Collision, Obverse));
	}
	file.close();
}
TileMap::~TileMap()
{
	for (auto& x : this->board) {
		for (auto& y : x) {
			for (auto& z : y) {
				if (&z != NULL) {
					delete z;
				}
			}
		}
	}
}
//Main Functions
void TileMap::update()
{

}
void TileMap::render(sf::RenderTarget& target)
{
	sf::RectangleShape CollisionRect;
	CollisionRect.setFillColor(sf::Color(255,0,0,100));
	CollisionRect.setSize(sf::Vector2f(this->TileSize,this->TileSize));

	for (int x = 0; x < this->Width; x++) {
		for (int y = 0; y < this->Height; y++) {
			for (auto &z : this->board[x][y]) {
				if (z != NULL) {
					z->render(target);
					if (z->getCollision()) {
						CollisionRect.setPosition(z->getCollisionBounds().left, z->getCollisionBounds().top);
						CollisionRect.setSize(sf::Vector2f(z->getCollisionBounds().width, z->getCollisionBounds().height));
						target.draw(CollisionRect);
					}
				}
			}
		}
	}
}
void TileMap::render(sf::RenderTarget& target, sf::Vector2f centerFloat,int renderLimit)
{
	sf::Vector2i centerInt = sf::Vector2i(centerFloat.x/this->TileSize,centerFloat.y / this->TileSize);

	sf::Vector2i renderX;
		renderX.x = centerInt.x - renderLimit;
		if (renderX.x < 0)renderX.x = 0;
		renderX.y = centerInt.x + renderLimit+1;
		if (renderX.y > this->Width)renderX.y = this->Width;

	sf::Vector2i renderY;
		renderY.x = centerInt.y - renderLimit;
		if (renderY.x < 0)renderY.x = 0;
		renderY.y = centerInt.y + renderLimit+1;
		if (renderY.y > this->Height)renderY.y = this->Height;

	for (int x = renderX.x;x< renderX.y; x++) {
		for (int y = renderY.x; y < renderY.y; y++) {
			for (auto& z : this->board[x][y]) {
				if (z != NULL && !z->getObverse()) {
					z->render(target);
				}
			}
		}
	}
	target.draw(this->x);
}
void TileMap::renderObverse(sf::RenderTarget& target, sf::Vector2f centerFloat, int renderLimit)
{
	sf::Vector2i centerInt = sf::Vector2i(centerFloat.x / this->TileSize, centerFloat.y / this->TileSize);

	sf::Vector2i renderX;
	renderX.x = centerInt.x - renderLimit;
	if (renderX.x < 0)renderX.x = 0;
	renderX.y = centerInt.x + renderLimit + 1;
	if (renderX.y > this->Width)renderX.y = this->Width;

	sf::Vector2i renderY;
	renderY.x = centerInt.y - renderLimit;
	if (renderY.x < 0)renderY.x = 0;
	renderY.y = centerInt.y + renderLimit + 1;
	if (renderY.y > this->Height)renderY.y = this->Height;

	for (int x = renderX.x; x < renderX.y; x++) {
		for (int y = renderY.x; y < renderY.y; y++) {
			for (auto& z : this->board[x][y]) {
				if (z != NULL && z->getObverse()) {
					z->render(target);
				}
			}
		}
	}
}
//Accessors
int TileMap::getLayersQuantity(int x, int y)
{
	if (x >= 0 && x < this->Width && y >= 0 && y < this->Height) {
		return this->board[x][y].size();
	}
	return 0;
}
bool TileMap::getCollision(int x, int y)
{
	if (x >= 0 && x < this->Width && y >= 0 && y < this->Height) {
		for (auto& l : this->board[x][y]) {
			if (l->getCollision() == true)
				return true;
		}
	}
	return false;
}
bool TileMap::getObverse(int x, int y)
{
	if (x >= 0 && x < this->Width && y >= 0 && y < this->Height) {
		for (auto& l : this->board[x][y]) {
			if (l->getObverse() == true)
				return true;
		}
	}
	return false;
}
//Modifiers
void TileMap::addTile(int x, int y, sf::IntRect textureRect, sf::Texture& texture, sf::FloatRect OffSet, bool Collision, bool Obverse)
{
	if(x>=0 && x < this->Width && y>=0 && y<this->Height)
		this->board[x][y].push_back(new Tile(this->TileSize, x * this->TileSize, y * this->TileSize, texture , textureRect , OffSet , Collision, Obverse));
}
void TileMap::removeTile(int x , int y)
{
	if (x >= 0 && x < this->Width && y >= 0 && y < this->Height && !this->board[x][y].empty()) {
		int lastLayer = this->board[x][y].size()-1;
		delete this->board[x][y][lastLayer];
		this->board[x][y].erase(this->board[x][y].begin()+ lastLayer, this->board[x][y].begin()+lastLayer+1);
	}
}
//Other
void TileMap::saveToFile(std::string filePath)
{
	//Files Structure:
	//TileSize Width Height
	//Collision TexturePosX PosX PosY OffSetLeft OffSetTop OffSetDown OffSetRight Obverse [...]
	std::ofstream file(filePath);
	file << this->TileSize <<" "<<this->Width<<" "<< this->Height<<"\n";

	for (auto& x : this->board) {
		for (auto& y : x) {
			for (auto& z : y) {
				file << z->getCollision() << " " <<
					z->getTextureRect().left << " " <<
					z->getPosition().x / this->TileSize << " " << z->getPosition().y / this->TileSize << " " <<
					z->getOffSet().left << " " << z->getOffSet().top << " " <<
					z->getOffSet().height << " " << z->getOffSet().width << " " <<
					z->getObverse()<<" ";
			} 
		}
	}

	file.close();
}
void TileMap::loadFromFile(std::string filePath, sf::Texture& Texture)
{
	//Files Structure:
	//TileSize Width Height
	//Collision TexturePosX PosX PosY OffSetLeft OffSetTop OffSetDown OffSetRight Obverse  [...]
	std::ifstream file(filePath);
	file >> this->TileSize >> this->Width>> this->Height;
	
	//Clear Board
	for (auto& x : this->board) {
		for (auto& y : x) {
			for (auto& z : y) {
				if (&z != NULL) {
					delete z;
				}
			}
		}
	}
	this->board.erase(this->board.begin(),this->board.end());
	//Board initialization
	this->board.resize(this->Width, std::vector< std::vector< Tile* > >());
	for (size_t x = 0; x < this->Width; x++) {
		for (size_t y = 0; y < this->Height; y++) {
			this->board[x].resize(this->Height, std::vector< Tile* >());
		}
	}

	int TexturePosX{}, PosX{}, PosY{}, OffSetTop{}, OffSetLeft{}, OffSetDown{}, OffSetRight{};
	bool Obverse, Collision;

	while (file>>Collision>> TexturePosX >>PosX>>PosY>> OffSetLeft >>OffSetTop >> OffSetDown >> OffSetRight>> Obverse) {
		this->board[PosX][PosY].push_back(new Tile(this->TileSize, PosX * this->TileSize, PosY * this->TileSize , Texture , sf::IntRect(TexturePosX, 0 , this->TileSize,this->TileSize), sf::FloatRect(OffSetLeft,OffSetTop,OffSetRight,OffSetDown) , Collision, Obverse));
	}
	file.close();
}
void TileMap::checkCollision(player* entity,float dt)
{
	this->FromX = int(entity->getGlobalBounds().left/this->TileSize)-1;
	if (this->FromX < 0) this->FromX = 0;
	this->ToX = int(entity->getGlobalBounds().left/this->TileSize)+2;
	if (this->ToX > this->Width) this->ToX = this->Width;

	this->FromY = int(entity->getGlobalBounds().top / this->TileSize) - 1;
	if (this->FromY < 0) this->FromY = 0;
	this->ToY = int(entity->getGlobalBounds().top / this->TileSize) + 2;
	if (this->ToY > this->Height) this->ToY = this->Height;

	for (int x = this->FromX; x < this->ToX; x++) {
		for (int y = this->FromY ; y < this->ToY; y++) {
			for (auto& z : this->board[x][y]) {

				sf::FloatRect playerBounds = entity->getGlobalBounds();
				playerBounds.height /= 2;
				playerBounds.top += playerBounds.height;

				sf::FloatRect wallBounds = z->getCollisionBounds();

				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
				nextPositionBounds.height /= 2;
				nextPositionBounds.top += nextPositionBounds.height;

				if (z != NULL && z->getCollision() && z->getCollisionBounds().intersects(nextPositionBounds)) {
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, playerBounds.top-playerBounds.height);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height - playerBounds.height);
					}

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top - playerBounds.height);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top - playerBounds.height);
					}
				}
			}
		}
	}
}
void TileMap::checkEntityCollision(std::vector<entity*>* Entity, float dt)
{
	for (auto &entity : *Entity) {
		//Checking dystance +1 tile around Entity
		this->FromX = int(entity->getGlobalBounds().left / this->TileSize) - 1;
		if (this->FromX < 0) this->FromX = 0;
		this->ToX = int((entity->getGlobalBounds().left + entity->getGlobalBounds().width) / this->TileSize) + 2;
		if (this->ToX > this->Width) this->ToX = this->Width;

		this->FromY = int(entity->getGlobalBounds().top / this->TileSize) - 1;
		if (this->FromY < 0) this->FromY = 0;
		this->ToY = int((entity->getGlobalBounds().top + entity->getGlobalBounds().height) / this->TileSize) + 2;
		if (this->ToY > this->Height) this->ToY = this->Height;

		for (int x = this->FromX; x < this->ToX; x++) {
			for (int y = this->FromY; y < this->ToY; y++) {
				for (auto& z : this->board[x][y]) {

					sf::FloatRect playerBounds = entity->getGlobalBounds();
					sf::FloatRect wallBounds = z->getCollisionBounds();
					sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

					if (z != NULL && z->getCollision() && z->getCollisionBounds().intersects(nextPositionBounds)) {
						//Bottom collision
						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, playerBounds.top);
						}

						//Top collision
						else if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left
							)
						{
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						}

						//Right collision
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						}

						//Left collision
						else if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top
							)
						{
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						}
					}
				}
			}
		}
	}
}

void TileMap::checkShotsCollision(std::vector<projectile*>* Projectiles, float dt)
{
	int j = 0;
	for (auto& i : (*Projectiles)){
		//Collision cheking distance
		this->FromX = int(i->getGlobalBounds().left / this->TileSize) - 1;
		if (this->FromX < 0) this->FromX = 0;
		this->ToX = int(i->getGlobalBounds().left / this->TileSize) + 2;
		if (this->ToX > this->Width) this->ToX = this->Width;

		this->FromY = int(i->getGlobalBounds().top / this->TileSize) - 1;
		if (this->FromY < 0) this->FromY = 0;
		this->ToY = int(i->getGlobalBounds().top / this->TileSize) + 2;
		if (this->ToY > this->Height) this->ToY = this->Height;
		//Checking all tiles around the projectile
		bool collision{ false };
		for (int x = this->FromX; x < this->ToX; x++) {
			for (int y = this->FromY; y < this->ToY; y++) {
				for (auto& z : this->board[x][y]) {
					//if collision
					if (z != NULL && z->getCollision() && z->getCollisionBounds().intersects(i->getGlobalBounds())) {
						delete i;
						Projectiles->erase((*Projectiles).begin()+j);
						collision = true;
					}
					if (collision)break;
				}
				if (collision)break;
			}
			if (collision)break;
		}
		j++;
		if (collision)break;
	}
}