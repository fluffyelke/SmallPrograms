/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityBase.h
 * Author: default
 *
 * Created on May 17, 2018, 10:29 AM
 */
#pragma once
#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum class EntityType {
    Base,
    Enemy,
    Player,
    Question
};

enum class EntityState {
    Idle,   //Not Moving
    Walking,    //Walk
    Running,    //Run
    Jumping,    //Jump
    Hurt,       //Hurt
    Dying
};

struct TileInfo;

struct CollisionElement {
    CollisionElement(float area, TileInfo* tileInfo, const sf::FloatRect& bounds) 
            : m_area{area},
              m_tile{tileInfo},
              m_tileBounds{bounds} {
        
    }
    float m_area;
    TileInfo* m_tile;
    sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;
bool sortCollisions(const CollisionElement& left, const CollisionElement& right);

//Forward Declaration
class EntityManager;

class EntityBase {
    friend class EntityManager;
public:
    EntityBase(EntityManager* entMgr);
    virtual ~EntityBase();
    
    //Getters and Setters
    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
    EntityState getState() const;
    std::string getName() const;
    unsigned int getId() const;
    EntityType getType() const;
    
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);
    void setSize(float x, float y);
    void setState(const EntityState& state);
    
    void move(float x, float y);
    void addVelocity(float x, float y);
    void accelerate(float x, float y);
    void setAcceleration(float x, float y);
    void applyFriction(float x, float y);
    
    virtual void update(float dt);
    virtual void draw(sf::RenderWindow* window) = 0;
    
protected:
    //Methods 
    void updateAABB();
    void checkCollisions();
    void resolveCollisions();
    
    //Method for what THIS entity do TO the collider entity;
    virtual void onEntityCollision(EntityBase* collider, bool attack) = 0;
    
    //Members
    std::string m_name;
    EntityType m_type;
    unsigned int m_id;
    sf::Vector2f m_position;    //Current position
    sf::Vector2f m_positionOld; //Position before entity move
    sf::Vector2f m_velocity;    //Current entity velocity
    sf::Vector2f m_maxVelocity; // maximum Velocity
    sf::Vector2f m_speed;       //value of acceleration
    sf::Vector2f m_acceleration;    
    sf::Vector2f m_friction;    //Default friction value.
    
    TileInfo* m_referenceTile;  //Tile underneath the entity;
    sf::Vector2f m_size;        //Size of the collision Box;
    sf::FloatRect m_AABB;       //Bounding box for the collisions.
    EntityState m_state;        //current entity state.
    //Flags for remembering axis collisions.
    bool m_collidingOnX;
    bool m_collidingOnY;
    
    Collisions m_collisions;
    EntityManager* m_entityManager;
};

#endif /* ENTITYBASE_H */

