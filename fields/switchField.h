#pragma once
class switchField
{
private:
	sf::Color active,normal;

	sf::Text On,Off;
	sf::RectangleShape OnRect,OffRect;
	bool State{};

	bool MousePressed{};
public:
	switchField(sf::Font &Font,sf::Vector2f Position,bool State);
	~switchField();

	void render(sf::RenderTarget  &target);
	void update(sf::Vector2f MousePos);
};