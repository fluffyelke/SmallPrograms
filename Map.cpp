/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.cpp
 * Author: default
 * 
 * Created on May 16, 2018, 11:26 AM
 */

#include <cmath>

#include "Map.h"
#include "StateManager.h"

Map::Map(SharedContext* context, IBaseState* currState)
    : m_context{context},
      m_defaultTile{context},
      m_mapMaxSize{212, 14},
      m_tileCount{0},
      m_tileSetCount{0},
      m_mapGravity{512.f},
      m_loadNextMap{false},    
      m_currentState{currState}  {
          m_context->m_gameMap = this;
          loadTiles("resources/configs/tiles.cfg");
}


Map::~Map() {
    purgeMap();
    purgeTileSet();
    
    m_context->m_gameMap = nullptr;
}

Tile* Map::getTile(unsigned int x, unsigned int y) {
    auto it = m_tileMap.find(convertCoords(x, y));
    return (it != m_tileMap.end() ? it->second : nullptr);
}

//Convert 2 dimm to 1 dimm int
unsigned int Map::convertCoords(unsigned int x, unsigned int y) {
    return (x * m_mapMaxSize.x) + y;    //Row Major
}

void Map::update(float dt) {
    if(m_loadNextMap) {
        purgeMap();
        m_loadNextMap = false;
        if(m_nextMap != "") {
            loadMap("resources/media/Maps/" + m_nextMap);
        }
        else {
            m_currentState->getStateManager()->switchTo(StateType::GAMEOVER);
        }
        m_nextMap = "";
    }
    sf::FloatRect viewSpace = m_context->m_window->getViewSpace();
    m_background.setPosition(viewSpace.left, viewSpace.top);
}

void Map::draw() {
    sf::RenderWindow* window = m_context->m_window->getRenderWindow();
    window->draw(m_background);
    
    sf::FloatRect viewSpace = m_context->m_window->getViewSpace();
    
    //draw tiles
    sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::TILE_SIZE), floor(viewSpace.top / Sheet::TILE_SIZE));
    sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::TILE_SIZE), ceil((viewSpace.top + viewSpace.height) / Sheet::TILE_SIZE));
    
    unsigned int count = 0;
    for(int x = tileBegin.x; x <= tileEnd.x; ++x) {
        for(int y = tileBegin.y; y <= tileEnd.y; ++y) {
            if(x < 0 || y < 0) {
                continue;
            }
            Tile* tile = getTile(x, y);
            if(!tile) {
                continue;
            }
            sf::Sprite& sprite = tile->m_properties->m_sprite;
            sprite.setPosition(x * Sheet::TILE_SIZE, y * Sheet::TILE_SIZE); //Multiply *3 to get bigger tile 
            sprite.setScale(1.0, 1.0);  //Multiply Scale by 3 to get correct tile pos and size.
            window->draw(sprite);
            ++count;
        }
    }
}

void Map::purgeMap() {
    m_tileCount = 0;
    for(auto& it : m_tileMap) {
        delete it.second;
    }
    m_tileMap.clear();
    m_context->m_entityManager->purge();
    if(m_backgroundTexture == "") {
        return;
    }
    m_context->m_textureManager->releaseResource(m_backgroundTexture);
    m_backgroundTexture = "";
}

void Map::purgeTileSet() {
    for(auto& it : m_tileSet) {
        delete it.second;
    }
    m_tileSet.clear();
    m_tileSetCount = 0;
}

void Map::loadTiles(const std::string& path) {
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) {
        std::cerr << "! Failed loading tile set file: " << path << std::endl;
        return;
    }
    
    std::string line;
    while(std::getline(file, line)) {
        if(line[0] == '|') {
            continue;
        }
        std::stringstream keystream{line};
        int tileId;
        keystream >> tileId;
        if(tileId < 0) {
            continue;
        }
        TileInfo* tile = new TileInfo(m_context, "TileSheet", tileId);
        keystream >> tile->m_name >> tile->m_friction.x >> tile->m_friction.y >> tile->m_deadly >> tile->m_isBackgroundText;
        
        if(!m_tileSet.emplace(tileId, tile).second) {
            //Duplicate tile detected.
            std::cout << "! Duplicate tile type: " << tile->m_name << std::endl;
            delete tile;
        }
    }
    file.close();
}

void Map::loadMap(const std::string& path) {
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) {
        std::cerr << "! Map File was not found: " << path << std::endl;
        return;
    }
    EntityManager* entityMgr = m_context->m_entityManager;
    std::string line;
    std::cout << "######################## Loading Map... #####################\n";
    int playerId = -1;
    int animTileId = -1;
    while(std::getline(file, line)) {
        if(line[0] == '|') {
            continue;
        }
        std::stringstream keystream{line};
        std::string type;
        keystream >> type;
        if(type == "TILE") {
            int tileId = 0;
            keystream >> tileId;
            if(tileId < 0) {
                std::cout << "Bad Tile Id: " << tileId << std::endl;
                continue;
            }
            auto it = m_tileSet.find(tileId);
            if(it == m_tileSet.end()) {
                std::cout << "! Tile id: (" << tileId << ") was not found in the tileSet. \n";
                continue;
            }
            sf::Vector2i tileCoords;
            keystream >> tileCoords.x >> tileCoords.y;
            if(tileCoords.x > m_mapMaxSize.x || tileCoords.y > m_mapMaxSize.y) {
                std::cout << "! Tile is out of range: x - " << tileCoords.x << ", y - " << tileCoords.y << std::endl;
                continue;
            }
            Tile* tile = new Tile();
            //Bind properties of a tile from the set.
            tile->m_properties = it->second;
            if(!m_tileMap.emplace(convertCoords(tileCoords.x, tileCoords.y), tile).second) {
                //Duplicate tile detected.
                std::cout << "! Duplicate tile type: x - " << tileCoords.x << ", y - " << tileCoords.y << std::endl;
                delete tile;
                tile = nullptr;
                continue;
            }
            std::string warp;
            keystream >> warp;
            tile->m_warp = false;
            if(warp == "WARP") {
                tile->m_warp = true;
            }
        }
        else if(type == "BACKGROUND") {
            if(m_backgroundTexture != "") {
                continue;
            }
            keystream >> m_backgroundTexture;
            if(!m_context->m_textureManager->requireResource(m_backgroundTexture)) {
                m_backgroundTexture = "";
                continue;
            }
            sf::Texture* texture = m_context->m_textureManager->getResource(m_backgroundTexture);
            m_background.setTexture(*texture);
            sf::Vector2f viewSize = m_currentState->getView().getSize();
            sf::Vector2u textureSize = texture->getSize();
            sf::Vector2f scaleFactors;
            
            scaleFactors.x = viewSize.x / textureSize.x;
            scaleFactors.y = viewSize.y / textureSize.y;
            m_background.scale(scaleFactors.x, scaleFactors.y);
        }
        else if(type == "SIZE") {
            keystream >> m_mapMaxSize.x >> m_mapMaxSize.y;
        }
        else if(type == "GRAVITY") {
            keystream >> m_mapGravity;
        }
        else if(type == "DEFAULT_FRICTION") {
            keystream >> m_defaultTile.m_friction.x >> m_defaultTile.m_friction.y;
        }
        else if(type == "NEXTMAP") {
            keystream >> m_nextMap;
        }
        else if(type == "PLAYER"){
			if (playerId != -1){ continue; }
			// Set up the player position here.
			playerId = entityMgr->add(EntityType::Player);
			if (playerId < 0){ continue; }
			float playerX = 0; float playerY = 0;
			keystream >> playerX >> playerY;
			entityMgr->find(playerId)->setPosition(playerX,playerY);
			m_playerStart = sf::Vector2f(playerX, playerY);
		}
        else if(type == "ENEMY") {
            std::string enemyName;
            keystream >> enemyName;
            int enemyId = entityMgr->add(EntityType::Enemy, enemyName);
            if(enemyId < 0) {
                continue;
            }
            float enemyX, enemyY;
            keystream >> enemyX >> enemyY;
            entityMgr->find(enemyId)->setPosition(enemyX, enemyY);
        }
        else if(type == "TILE_QUESTION") {
            std::string tileName;
            keystream >> tileName;
            int entityId = entityMgr->add(EntityType::Question, tileName);
            if(entityId < 0) {
                std::cout << "Should not enter here! Map.cpp line 259. " << std::endl; 
                continue;
            }
            float entityX, entityY;
            keystream >> entityX >> entityY;
            entityMgr->find(entityId)->setPosition(entityX, entityY);
        }
        else {
            std::cout << "! Unknown type: " << type << std::endl;
        }
    }
    file.close();
    std::cout << "####################### Map Loaded ########################\n";
}

void Map::loadNext() {
    m_loadNextMap = true;
}

TileInfo* Map::getDefaultTile() {
    return &m_defaultTile;
}

float Map::getGravity() {
    return m_mapGravity;
}

const sf::Vector2u& Map::getMapSize() const {
    return m_mapMaxSize;
}

const sf::Vector2f& Map::getPlayerStart() const {
    return m_playerStart;
}

unsigned int Map::getTileSize() const {
    return Sheet::TILE_SIZE;
}

