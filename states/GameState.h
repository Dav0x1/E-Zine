#pragma once
#include "state.h"

#include "../entity/player.h"
#include "../map/TileMap.h"
#include "../playerPanel/playerInfo.h"
#include "../shop/shop.h"
#include "../entity/entityHerd.h"

class TileMap;
class player;
class playerInfo;
class GameState;
class entity;

class GameState :
    public state
{
private:
    //View and things needed for render frames 
    sf::View View;
    sf::RenderTexture RenderTexture;
    sf::Sprite RenderSprite;
    //Tile Map Object
    TileMap* Map;
    //Player Object
    player* Player;
    //Player Bar Object
    playerInfo* PlayerInfo;
    //Array with all shops
    std::vector<shop*> Shops;
    bool ShopActive;
    //Variables
    short RenderLimit;
    //Testing Temporary <---- To remove ----->
    sf::Texture Texture;
    std::vector<entityHerd*> Entities;
public:
    //Constructor and Destructor
    GameState(StateData *stateData);
    ~GameState();
    //Main Functions
    void update();
    void render();
    //Initialization
    void initVariables();
    void initView();
    void initRender();
    void initTileMap();
    void initPlayer();
    void initPlayerInfo();
    void initShops();
    void initHerd();
    //Render
    void renderMap(sf::RenderTarget *Target);
    void renderPlayer(sf::RenderTarget* Target);
    void renderObverseMap(sf::RenderTarget* Target);
    void renderPlayerInfo(sf::RenderTarget* Target);
    void renderShops(sf::RenderTarget* Target);
    void renderEntities(sf::RenderTarget* Target);
    //Update
    void updateInput();
    void updatePlayer();
    void updateView();
    void updatePlayerCollision();
    void updateEntityCollision();
    void updatePlayerShotCollision();
    void updateShops();
    void updatePlayerInfo();
    void updateEntities();
    void updateEntitiesMove();
    //Other
};