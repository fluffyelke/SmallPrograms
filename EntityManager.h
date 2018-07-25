/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityManager.h
 * Author: default
 *
 * Created on May 17, 2018, 12:39 PM
 */
#pragma once

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <functional>
#include "Player.h"
#include "Enemy.h"
#include "Question.h"

using EntityContainer = std::unordered_map<unsigned int, EntityBase*>;
using EntityFactory = std::unordered_map<EntityType, std::function<EntityBase*(void)>>;
using EnemyTypes = std::unordered_map<std::string, std::string>;
using TileTypes = std::unordered_map<std::string, std::string>;

struct SharedContext;

class EntityManager {
public:
    EntityManager(SharedContext* shared, unsigned int maxEntities);
    ~EntityManager();
    
    int add(const EntityType& type, const std::string& name = "");
    EntityBase* find(unsigned int id);
    EntityBase* find(const std::string& name);
    void remove(unsigned int id);
    
    void update(float dt);
    void draw();
    
    void purge();
    
    SharedContext* getContext();
private:
    
    template<class T>
    void registerEntity(const EntityType& type) {
        m_entityFactory[type] = [this]() -> EntityBase* {
            return new T(this);  
        };
    }
    
    void processRemovals();
    void loadEnemyTypes(const std::string& name);
    void loadTileTypes(const std::string& name);
    void entityCollisionCheck();
    
    EntityContainer m_entities;
    EnemyTypes m_enemyTypes;
    TileTypes m_tileTypes;
    EntityFactory m_entityFactory;
    SharedContext* m_context;
    unsigned int m_idCounter;
    unsigned int m_maxEntities;

    std::vector<unsigned int> m_entitiesToRemove;
    
};

#endif /* ENTITYMANAGER_H */

