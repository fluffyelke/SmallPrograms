/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: default
 *
 * Created on May 16, 2018, 11:26 AM
 */
#pragma once
#ifndef MAP_H
#define MAP_H

#include "SharedContext.h"
#include "IBaseState.h"

enum Sheet {
    TILE_SIZE = 16,
    SHEET_WIDTH = 528,
    SHEET_HEIGHT = 448
};

using TileID = unsigned int;

/**
 * Class to take the Tile from the sheet.
 */
struct TileInfo {
    //TileInfo Constructor
    TileInfo(SharedContext* shared, const std::string& texture = "", TileID id = 0) 
            : m_context{shared},
              m_id{0},
              m_deadly{false},
              m_isBackgroundText{false} {
                  
        TextureManager* textMgr = shared->m_textureManager;
        if(texture == "") {
            m_id = id;
            return;
        }
        if(!textMgr->requireResource(texture)) {
            return;
        }
        m_texture = texture;
        m_id = id;
        m_sprite.setTexture(*textMgr->getResource(m_texture));
        
        //Cut Tile from sheet.Extraordinary
        sf::IntRect tileBoundaries(m_id % (Sheet::SHEET_WIDTH / Sheet::TILE_SIZE) * Sheet::TILE_SIZE,
                                   m_id / (Sheet::SHEET_HEIGHT / Sheet::TILE_SIZE) * Sheet::TILE_SIZE,
                                   Sheet::TILE_SIZE,Sheet::TILE_SIZE);
        m_sprite.setTextureRect(tileBoundaries);
        
    }   //End of Constructor
    ~TileInfo() {
        if(m_texture == "") {
            return;
        }
        m_context->m_textureManager->releaseResource(m_texture);
    }
              
    sf::Sprite m_sprite;
    
    
    TileID m_id;
    std::string m_name;
    sf::Vector2f m_friction;
    bool m_deadly;
    bool m_isBackgroundText;
    
    SharedContext* m_context;
    std::string m_texture;
    
private:

};



struct Tile {
    TileInfo* m_properties; //The tile information
    bool m_warp;            //is the tile warp to next level.
    //Other unique flags.
};


//Conatiners to hold the tile information
using TileMap = std::unordered_map<TileID, Tile*>;
using TileSet = std::unordered_map<TileID, TileInfo*>;


class Map {
public:
    Map(SharedContext* context, IBaseState* currState);
    ~Map();
    
    Tile* getTile(unsigned int x, unsigned int y);
    TileInfo* getDefaultTile();
    float getGravity();
    unsigned int getTileSize() const;
    const sf::Vector2u& getMapSize() const;
    const sf::Vector2f& getPlayerStart() const;
    
    void loadMap(const std::string& path);
    void loadNext();
    void update(float dt);
    void draw();
    
private:
    //Method to convert 2 Dimmension Coords to 1 Dimmension ints
    unsigned int convertCoords(unsigned int x, unsigned int y);
    void loadTiles(const std::string& path);
    void purgeMap();
    void purgeTileSet();
    
    TileSet m_tileSet;
    TileMap m_tileMap;
    sf::Sprite m_background;
    TileInfo m_defaultTile;
    sf::Vector2u m_mapMaxSize;
    sf::Vector2f m_playerStart;
    unsigned int m_tileCount;
    unsigned int m_tileSetCount;
    float m_mapGravity;
    std::string m_nextMap;
    bool m_loadNextMap;
    std::string m_backgroundTexture;
    IBaseState* m_currentState;
    SharedContext* m_context;
};

#endif /* MAP_H */

