/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityBase.cpp
 * Author: default
 * 
 * Created on May 17, 2018, 10:29 AM
 */

#include <cmath>

#include "EntityBase.h"
#include "SharedContext.h"
#include "Map.h"

EntityBase::EntityBase(EntityManager* entMgr) 
    : m_entityManager{entMgr},
      m_name{"BaseEntity"},
      m_type{EntityType::Base},
      m_referenceTile{nullptr},
      m_state{EntityState::Idle},
      m_id{0},
      m_collidingOnX{false},
      m_collidingOnY{false} {
    
}


EntityBase::~EntityBase() {
}

void EntityBase::setPosition(float x, float y) {
    m_position = sf::Vector2f{x, y};
    updateAABB();
}

void EntityBase::setPosition(const sf::Vector2f& pos) {
    m_position = pos;
    updateAABB();
}

void EntityBase::setSize(float x, float y) {
    m_size = sf::Vector2f{x, y};
    updateAABB();
}

void EntityBase::setState(const EntityState& state) {
    if(EntityState::Dying == m_state) {
        return;
    }
    m_state = state;
}

unsigned int EntityBase::getId() const {
    return m_id;
}

std::string EntityBase::getName() const {
    return m_name;
}

const sf::Vector2f& EntityBase::getPosition() const {
    return m_position;
}

const sf::Vector2f& EntityBase::getSize() const {
    return m_size;
}

EntityState EntityBase::getState() const {
    return m_state;
}

EntityType EntityBase::getType() const {
    return m_type;
}

void EntityBase::move(float x, float y) {
    m_positionOld = m_position;
    m_position += sf::Vector2f{x, y};
    
    sf::Vector2u mapSize = m_entityManager->getContext()->m_gameMap->getMapSize();
    if(m_position.x < 0) {
        m_position.x = 0;
    }
    else if(m_position.x > (mapSize.x + 1) * Sheet::TILE_SIZE) {
        m_position.x = (mapSize.x + 1) * Sheet::TILE_SIZE;
    }
    
    if(m_position.y < 0) {
        m_position.y = 0;
    }
    else if(m_position.y > (mapSize.y + 1) * Sheet::TILE_SIZE) {
        m_position.y = (mapSize.y + 1) * Sheet::TILE_SIZE;
        setState(EntityState::Dying);
    }
    updateAABB();
}

void EntityBase::addVelocity(float x, float y) {
    m_velocity += sf::Vector2f{x, y};
    if(abs(m_velocity.x) > m_maxVelocity.x) {
        if(m_velocity.x < 0) {
            m_velocity.x = -m_maxVelocity.x;
        }
        else {
            m_velocity.x = m_maxVelocity.x;
        }
    }
    if(abs(m_velocity.y) > m_maxVelocity.y) {
        if(m_velocity.y < 0) {
            m_velocity.y = -m_maxVelocity.y;
        }
        else {
            m_velocity.y = m_maxVelocity.y;
        }
    }
}

void EntityBase::accelerate(float x, float y) {
    m_acceleration += sf::Vector2f{x, y};
}

void EntityBase::applyFriction(float x, float y) {
    if(m_velocity.x != 0) {
        if(abs(m_velocity.x) - abs(x) < 0) {
            m_velocity.x = 0;
        }
        else {
            if(m_velocity.x < 0) {
                m_velocity.x += x;
            }
            else {
                m_velocity.x -= x;
            }
        }
    }
    if(m_velocity.y != 0) {
        if(abs(m_velocity.y) - abs(y) < 0) {
            m_velocity.y = 0;
        }
        else {
            if(m_velocity.y < 0) {
                m_velocity.y -= y;
            }
            else {
                m_velocity.y += y;
            }
        }
    }
}

void EntityBase::update(float dt) {
    Map* map = m_entityManager->getContext()->m_gameMap;
    float gravity = map->getGravity();
    
    accelerate(0, gravity);
    addVelocity(m_acceleration.x * dt, m_acceleration.y * dt);
    setAcceleration(0.0f, 0.0f);
    
    sf::Vector2f frictionValue;
    if(m_referenceTile) {
        frictionValue = m_referenceTile->m_friction;
        if(m_referenceTile->m_deadly) {
            setState(EntityState::Dying);
        }
    }
    else if(map->getDefaultTile()) {
        frictionValue = map->getDefaultTile()->m_friction;
    }
    else {
        frictionValue = m_friction;
    }
    
    float frictionX = (m_speed.x * frictionValue.x) * dt;
    float frictionY = (m_speed.y * frictionValue.y) * dt;
    
    applyFriction(frictionX, frictionY);
    sf::Vector2f deltaPos = m_velocity * dt;
    move(deltaPos.x, deltaPos.y);
    m_collidingOnX = false;
    m_collidingOnY = false;

    checkCollisions();
    resolveCollisions();
}

void EntityBase::updateAABB() {
    m_AABB = sf::FloatRect{m_position.x - (m_size.x / 2), m_position.y - (m_size.y / 2), m_size.x, m_size.y};
}



//Helper
bool sortCollisions(const CollisionElement& left, const CollisionElement& right) {
    return left.m_area < right.m_area;
}

void EntityBase::checkCollisions() {
    Map* gameMap = m_entityManager->getContext()->m_gameMap;
    unsigned int tileSize = gameMap->getTileSize();
    
    int fromX = floor(m_AABB.left / tileSize);
    int toX = floor((m_AABB.left + m_AABB.width) / tileSize);
    int fromY = floor(m_AABB.top / tileSize);
    int toY = floor((m_AABB.top + m_AABB.height) / tileSize);
    for(int x = fromX; x <= toX; ++x) {
        for(int y = fromY; y <= toY; ++y) {
            Tile* tile = gameMap->getTile(x, y);
            if(!tile || tile->m_properties->m_isBackgroundText){
                continue;
            }

            sf::FloatRect tileBounds(x * tileSize, y * tileSize, tileSize, tileSize);
            sf::FloatRect intersection;
            m_AABB.intersects(tileBounds, intersection);
            float area = intersection.width * intersection.height;
            
            CollisionElement e{area, tile->m_properties, tileBounds};
            m_collisions.emplace_back(e);
            if(tile->m_warp && m_type == EntityType::Player) {
                gameMap->loadNext();
            }
        }
    }
}

void EntityBase::resolveCollisions() {
    if(!m_collisions.empty()) {
        std::sort(m_collisions.begin(), m_collisions.end(), sortCollisions);
        Map* gameMap = m_entityManager->getContext()->m_gameMap;
        unsigned int tileSize = gameMap->getTileSize();

        for(auto& it : m_collisions) {
            if(!m_AABB.intersects(it.m_tileBounds)) {
                continue;
            }

            float xDiff = (m_AABB.left + (m_AABB.width / 2)) - (it.m_tileBounds.left + (it.m_tileBounds.width / 2));
            float yDiff = (m_AABB.top + (m_AABB.height / 2)) - (it.m_tileBounds.top + (it.m_tileBounds.height / 2));

            float resolve = 0;
            if(abs(xDiff) > abs(yDiff)) {
                if(xDiff > 0) {
                    resolve = (it.m_tileBounds.left + tileSize) - m_AABB.left;
                }
                else {
                    resolve = -((m_AABB.left + m_AABB.width) - it.m_tileBounds.left);
                }
                move(resolve, 0);
                m_velocity.x = 0;
                m_collidingOnX = true;
            }
            else {
                if(yDiff > 0) {
                    resolve = (it.m_tileBounds.top + tileSize) - m_AABB.top;
                }
                else {
                    resolve = -((m_AABB.top + m_AABB.height) - it.m_tileBounds.top);
                }
                move(0, resolve);
                m_velocity.y = 0;
                if(m_collidingOnY) {
                    continue;
                }
                m_referenceTile = it.m_tile;
                m_collidingOnY = true;
            }
        }
        m_collisions.clear();
    }
    if(!m_collidingOnY) {
        m_referenceTile = nullptr;
    }
}

void EntityBase::setAcceleration(float x, float y) {
    m_acceleration = sf::Vector2f{x, y};
}
