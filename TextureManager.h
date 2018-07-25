/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureManager.h
 * Author: default
 *
 * Created on May 14, 2018, 4:43 PM
 */

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"


class TextureManager : public ResourceManager<TextureManager, sf::Texture> {
public:
    TextureManager() : ResourceManager("resources/configs/textures.cfg") {
    }
    
    sf::Texture* load(const std::string& path) {
        sf::Texture* texture = new sf::Texture();
        if(!texture->loadFromFile(path)) {
            delete texture;
            texture = nullptr;
            std::cerr << "! Failed to load texture: " << path << std::endl;
        }
        return texture;
    }
};

#endif /* TEXTUREMANAGER_H */

