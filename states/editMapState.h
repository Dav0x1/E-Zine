#pragma once
#include "state.h"
#include "../map/TileMap.h"

class editMapState;
class TileMap;

class editMapState :
    public state
{
private:
    sf::View View;
    TileMap* tileMap;

    sf::RectangleShape BarBackground;
    std::vector <sf::RectangleShape*> BarTiles;

    sf::RectangleShape BackgroundTileInfo;
    sf::Text TileInfo;

    sf::Text SettingsInfo;

    sf::Vector2i GridMousePos;
    sf::RectangleShape ChoiceRect;
    sf::RectangleShape CollisionRect;

    sf::FloatRect CollisionOffSet;
    bool Obverse;
    bool Collision;
    //Default Variables
    int GridSize;
    int CurrentScrollAmount;
    int MaxScrollAmount;
    float BarTileSize;
    //Initialization
    void initTileMap();
    void initTexture();
    void initGui();
    void initTileInfo();
    void initTiles();
    void initView();
    //Update
    void updateGridMousePos();
    void updateInput();
    void updateRect();
    void updateGui();
    void updateTileInfo();
    void updateScroll();
    //Render
    void renderTileMap();
    void renderGui();
    void renderTiles();
    void renderTileInfo();
    void renderChoiceRect();
public:
    //Constructors and destructors
    editMapState(StateData* stateData);
    ~editMapState();
    //Main Functions
    void update();
    void render();
    //Accessors
    //Modifiers
};