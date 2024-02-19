#pragma once
class Tile
{
private:
	sf::RectangleShape Square;
	sf::FloatRect OffSet;
	bool Collision;
	bool Obverse;
	//Initialization
	//Update
	//Render
public:
	//Constructors and destructors
	Tile(float Size,float PosX, float PosY, sf::Texture& Texture, sf::IntRect TextureRect, sf::FloatRect OffSet,bool Collision = false , bool Obverse = false);
	~Tile();
	//Main Functions
	void update();
	void render(sf::RenderTarget &target);
	//Accessors
	bool getCollision();
	bool getObverse();
	sf::FloatRect getBounds();
	sf::FloatRect getCollisionBounds();
	sf::FloatRect getOffSet();
	sf::IntRect getTextureRect();
	sf::Vector2f getPosition();
	//Modifiers
};