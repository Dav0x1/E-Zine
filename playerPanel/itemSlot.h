#pragma once
class itemSlot
{
private:
	sf::RectangleShape Slot;
	sf::RectangleShape *Item;

	bool Hover;
	bool Active;
	sf::RectangleShape InfoBox;
	sf::Text InfoText;

	rpg::Item ItemStat;

	sf::Texture* Texture;
	sf::Font* Font;

	int Type;
	//Initialization
	//Update
	//Render
public:
	//Constructors and destructors
	itemSlot(sf::IntRect Position, sf::Texture& Texture,sf::Font &Font, int Type=0);
	~itemSlot();
	//Main Functions
	void render(sf::RenderTarget& Target);
	void renderSlot(sf::RenderTarget& Target);
	void renderItem(sf::RenderTarget& Target);
	void renderInfo(sf::RenderTarget& Target);
	void update(sf::Vector2i &MousePos);
	//Accessors
	bool isEmpty();
	bool isActive();
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getItemGlobalBounds();
	rpg::Item getItemStat();
	int getSlotType();
	//Modifiers
	void addItem(rpg::Item ItemStat);
	void setActive();
	void disableActive(bool RefreshPos = true);
	void clearItem();
};