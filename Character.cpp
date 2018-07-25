/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.cpp
 * Author: default
 * 
 * Created on May 17, 2018, 1:51 PM
 */

#include "Character.h"
#include "EntityManager.h"
#include "StateManager.h"

Character::Character(EntityManager* entMgr) 
    : EntityBase(entMgr),
      m_spriteSheet{m_entityManager->getContext()->m_textureManager},
      m_jumpVelocity{250},
      m_hitPoints{1} {
    m_name  = "Character"; 
}


Character::~Character() {
}

void Character::move(const Direction& dir) {
    if(getState() == EntityState::Dying) {
        return;
    }
    m_spriteSheet.setDirection(dir);
    if(dir == Direction::Left) {
        accelerate(-m_speed.x, 0);
    }
    else {
        accelerate(m_speed.x, 0);
    }
    if(getState() == EntityState::Idle) {
        setState(EntityState::Walking);
    }
}

void Character::jump() {
    if(getState() == EntityState::Dying || getState() == EntityState::Jumping || getState() == EntityState::Hurt) {
        return;
    }
    setState(EntityState::Jumping);
    addVelocity(0, -m_jumpVelocity);
}

void Character::attack() {
    if(getState() == EntityState::Dying || getState() == EntityState::Jumping || 
        getState() == EntityState::Hurt || getState() == EntityState::Jumping) {
        return;
    }
//    setState(EntityState::)
}

void Character::getHurt(const int& damage) {
    if(getState() == EntityState::Dying || getState() == EntityState::Hurt) {
        return;
    }
    m_hitPoints = (m_hitPoints - damage > 0 ? m_hitPoints - damage : 0);
    if(m_hitPoints) {
        setState(EntityState::Hurt);
    }
    else {
        setState(EntityState::Dying);
    }
}

void Character::load(const std::string& path) {
    std::ifstream file;
    file.open(path);
    if(!file.is_open()) {
        std::cout << "! Error loading character file: " << path << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file, line)) {
        std::stringstream keystream{line};
        std::string type;
        keystream >> type;
        if(type == "Name") {
            keystream >> m_name;
        }
        else if(type == "Spritesheet") {
            std::string path;
            keystream >> path;
            m_spriteSheet.loadSheet("resources/media/SpriteSheet/" + path);
        }
        else if(type == "Hitpoints") {
            keystream >> m_hitPoints;
        }
        else if(type == "BoundingBox") {
            sf::Vector2f box;
            keystream >> box.x >> box.y;
            setSize(box.x , box.y);
        }
        else if(type == "DamageBox") {
            keystream >> m_attackAABBoffset.x >> m_attackAABBoffset.y >> m_attackAABB.width >> m_attackAABB.height;
        }
        else if(type == "Speed") {
            keystream >> m_speed.x >> m_speed.y;
        }
        else if(type == "JumpVelocity") {
            keystream >> m_jumpVelocity;
        }
        else if(type == "MaxVelocity") {
            keystream >> m_maxVelocity.x >> m_maxVelocity.y;
        }
        else {
            std::cout << "Unknow type in character file: " << type << std::endl;
        }
    }
    file.close();
}

void Character::updateAttackAABB() {
    m_attackAABB.left = (m_spriteSheet.getDirection() == Direction::Left ? 
            (m_AABB.left - m_attackAABB.width) - m_attackAABBoffset.x   :
            (m_AABB.left + m_AABB.width) + m_attackAABBoffset.x);
    
	m_attackAABB.top = m_AABB.top + m_attackAABBoffset.y;
}

void Character::animate() {
    EntityState state = getState();
    if(state == EntityState::Walking && m_spriteSheet.getCurrentAnim()->getName() != "Walk") {
        m_spriteSheet.setAnimation("Walk", true, true);
    }
    else if(state == EntityState::Jumping && m_spriteSheet.getCurrentAnim()->getName() != "Jump") {
        m_spriteSheet.setAnimation("Jump", true, false);
    }
    else if(state == EntityState::Idle && m_spriteSheet.getCurrentAnim()->getName() != "Idle") {
        m_spriteSheet.setAnimation("Idle", true, true);
    }
    else if(state == EntityState::Dying && m_spriteSheet.getCurrentAnim()->getName() != "Dying") {
        m_spriteSheet.setAnimation("Dying", true, false);
    }
}

void Character::update(float dt) {
    EntityBase::update(dt);

    if (m_attackAABB.width != 0 && m_attackAABB.height != 0) {
        updateAttackAABB();

        // Debug.
//        if (m_entityManager->GetContext()->m_debugOverlay.Debug()) {
//            sf::RectangleShape* arect = new sf::RectangleShape(sf::Vector2f(m_attackAABB.width, m_attackAABB.height));
//            arect->setPosition(m_attackAABB.left, m_attackAABB.top);
//            arect->setFillColor(sf::Color(255, 0, 0,
//                (m_state == EntityState::Attacking && m_spriteSheet.GetCurrentAnim()->IsInAction()
//                ? 200 : 100)));
//            m_entityManager->GetContext()->m_debugOverlay.Add(arect);
//        }
        // End debug.
    }
    if (getState() != EntityState::Dying && getState() != EntityState::Hurt) {
        if (abs(m_velocity.y) >= 0.001f) {
            setState(EntityState::Jumping);
        } else if (abs(m_velocity.x) >= 0.1f) {
            setState(EntityState::Walking);
        } else {
            setState(EntityState::Idle);
        }
    } else if (getState() == EntityState::Hurt) {
        if (!m_spriteSheet.getCurrentAnim()->isPlaying()) {
            setState(EntityState::Idle);
        }
    } else if (getState() == EntityState::Dying) {
        if (!m_spriteSheet.getCurrentAnim()->isPlaying()) {
            m_entityManager->remove(m_id);
        }
    }

    animate();

    m_spriteSheet.update(dt);
    m_spriteSheet.setSpritePos(m_position);
}

void Character::draw(sf::RenderWindow* window) {
    m_spriteSheet.draw(window);
}
