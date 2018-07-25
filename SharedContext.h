/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SharedContext.h
 * Author: default
 *
 * Created on May 14, 2018, 2:15 PM
 */
#pragma once
#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "Window.h"
#include "EventManager.h"
#include "graphics/TextureManager.h"
#include "EntityManager.h"

//Forward Declaration
class Map;

struct SharedContext {
    SharedContext() 
    : m_window{nullptr},
      m_eventManager{nullptr},
      m_textureManager{nullptr},
      m_entityManager{nullptr},
      m_gameMap{nullptr} {
        
    }
    Window* m_window;
    EventManager* m_eventManager;
    TextureManager* m_textureManager;
    EntityManager* m_entityManager;
    Map* m_gameMap;
};

#endif /* SHAREDCONTEXT_H */

