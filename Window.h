/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Window.h
 * Author: default
 *
 * Created on May 10, 2018, 10:14 AM
 */
#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isDone();
	bool isFullscreen();
	bool isFocused();

	void toggleFullscreen(EventDetails* details);
	void close(EventDetails* details = nullptr);

	sf::RenderWindow* getRenderWindow();
	EventManager* getEventManager();
	sf::Vector2u getWindowSize();
        
        sf::FloatRect getViewSpace();
private:
	void setup(const std::string& title, const sf::Vector2u& size);
	void create();

	sf::RenderWindow m_window;
	EventManager m_eventManager;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	bool m_isFocused;
};

#endif /* WINDOW_H */

