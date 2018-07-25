/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityManager.cpp
 * Author: default
 * 
 * Created on May 17, 2018, 12:39 PM
 */

#include "EntityManager.h"
#include "SharedContext.h"


EntityManager::EntityManager(SharedContext* shared, unsigned int maxEntities)
    : m_context{shared}, 
      m_maxEntities{maxEntities},
      m_idCounter{0} {
          loadEnemyTypes("resources/media/Characters/EnemiesList.list");
          loadTileTypes("resources/media/Characters/Tiles.list");
          registerEntity<Player>(EntityType::Player);
          registerEntity<Enemy>(EntityType::Enemy);
          registerEntity<Question>(EntityType::Question);
}


EntityManager::~EntityManager() {
    purge();
}

int EntityManager::add(const EntityType& type, const std::string& name) {
    auto it = m_entityFactory.find(type);
    if(it == m_entityFactory.end()) {
        return -1;
    }
    EntityBase* entity = it->second();
    entity->m_id = m_idCounter;
    if(name != "") {
        entity->m_name = name;
    }
    m_entities.emplace(m_idCounter, entity);
    if(type == EntityType::Enemy) {
        auto it = m_enemyTypes.find(name);
        if(it != m_enemyTypes.end()) {
            Enemy* enemy = (Enemy*) entity;
            enemy->load("resources/media/Characters/" + it->second);
        }
    }
    else if(type == EntityType::Question) {
        auto it = m_tileTypes.find(name);
        if(it != m_tileTypes.end()) {
            Question* question = (Question*) entity;
            question->load("resources/media/AnimatedTiles/" + it->second);
        }
    }
    ++m_idCounter;
    return m_idCounter - 1;
}

EntityBase* EntityManager::find(const std::string& name) {
    for(auto& it : m_entities) {
        if(it.second->getName() == name) {
            return it.second;
        }
    }
    return nullptr;
}

EntityBase* EntityManager::find(unsigned int id) {
    auto it = m_entities.find(id);
    if(it == m_entities.end()) {
        return nullptr;
    }
    return it->second;
}

void EntityManager::remove(unsigned int id) {
    m_entitiesToRemove.emplace_back(id);
}

void EntityManager::update(float dt) {
    for(auto& it : m_entities) {
        it.second->update(dt);
    }
    entityCollisionCheck();
    processRemovals();
}

void EntityManager::draw() {
    sf::RenderWindow* window = m_context->m_window->getRenderWindow();
    sf::FloatRect viewSpace = m_context->m_window->getViewSpace();

    for(auto& it : m_entities) {
        if(!viewSpace.intersects(it.second->m_AABB)) {
            continue;
        }
        
        it.second->draw(window);
    }
}

SharedContext* EntityManager::getContext() {
    return m_context;
}

void EntityManager::purge() {
    for(auto& it : m_entities) {
        delete it.second;
    }
    m_entities.clear();
    m_idCounter = 0;
}

void EntityManager::processRemovals() {
    while(m_entitiesToRemove.begin() != m_entitiesToRemove.end()) {
        unsigned int id = m_entitiesToRemove.back();
        auto it = m_entities.find(id);
        if(it != m_entities.end()) {
            std::cout << "Discarding Entity: " << it->second->getId() << std::endl;
            delete it->second;
            m_entities.erase(it);
        }
        m_entitiesToRemove.pop_back();
    }
}

void EntityManager::entityCollisionCheck() {
    if(m_entities.empty()) {
        return;
    }
    for(auto it = m_entities.begin(); std::next(it) != m_entities.end(); ++it) {
        for(auto it2 = std::next(it); it2 != m_entities.end(); ++it2) {
            if(it->first == it2->first) {
                continue;
            }
            
            //Regular AABB bounding box collision.
            if(it->second->m_AABB.intersects(it2->second->m_AABB)) {
                it->second->onEntityCollision(it2->second, false);
                it2->second->onEntityCollision(it->second, false);
            }
            
//            EntityType t1 = it->second->getType();
//            EntityType t2 = it2->second->getType();
//            if(t1 == EntityType::Enemy || t2 == EntityType::Player){
//                Character* c1 = (Character*)it->second;
//                if(c1->m_attackAABB.intersects(it2->second->m_AABB)) {
//                    c1->onEntityCollision(it2->second, true);
//                }
//            }
//            if(t2 == EntityType::Enemy || t2 == EntityType::Player){
//                Character* c2 = (Character*)it2->second;
//                if(c2->m_attackAABB.intersects(it->second->m_AABB)) {
//                    c2->onEntityCollision(it->second, true);
//                }
//            }
        }
    }
}

void EntityManager::loadEnemyTypes(const std::string& name) {
    std::ifstream file;
    file.open(name);
    if(!file.is_open()) {
        std::cout << "! Error open enemy type file: " << name << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file, line)) {
        if(line[0] == '|') {
            continue;
        }
        std::stringstream keystream{line};
        std::string name;
        std::string nameFile;
        keystream >> name >> nameFile;
        m_enemyTypes.emplace(name, nameFile);
    }
    file.close();
}

void EntityManager::loadTileTypes(const std::string& name) {
    std::ifstream file;
    file.open(name);
    if(!file.is_open()) {
        std::cout << "! Error open tile type file: " << name << std::endl;
        return;
    }
    std::string line;
    
    while(std::getline(file, line)) {
        if(line[0] == '|') {
            continue;
        }
        std::stringstream keystream{line};
        std::string name;
        std::string nameFile;
        keystream >> name >> nameFile;
        m_tileTypes.emplace(name, nameFile);
    }
    file.close();
}
