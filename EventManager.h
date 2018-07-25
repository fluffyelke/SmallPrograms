/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventManager.h
 * Author: default
 *
 * Created on May 10, 2018, 10:16 AM
 */

#pragma once
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

enum class EventType {
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo {

    EventInfo() {
        m_code = 0;
    }

    EventInfo(int event) {
        m_code = event;
    }

    union {
        int m_code;
    };
};

struct EventDetails {

    EventDetails(const std::string& bindName)
    : m_name(bindName) {
        clear();
    }
    std::string m_name;

    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode; // Single key code.

    void clear() {
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
    }
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding {

    Binding(const std::string& name) : m_name(name), m_details(name), c(0) {
    }

    void BindEvent(EventType type, EventInfo info = EventInfo()) {
        m_events.emplace_back(type, info);
    }

    Events m_events;
    std::string m_name;
    int c; // Count of events that are "happening".

    EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;
class EventManager {
public:
    EventManager();
    ~EventManager();

    bool addBinding(Binding *l_binding);
    bool removeBinding(std::string l_name);

    void setFocus(const bool& l_focus);

    // Needs to be defined in the header!

    template<class T>
    bool addCallback(StateType l_state, const std::string& l_name, void(T::*l_func)(EventDetails*), T* l_instance) {
        auto it = m_callbacks.emplace(l_state, CallbackContainer()).first;
        auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
        return it->second.emplace(l_name, temp).second;
    }

    bool removeCallback(StateType state, const std::string& name) {
        auto it = m_callbacks.find(state);
        
        if(it == m_callbacks.end()) {
            return false;
        }
        
        auto it2 = it->second.find(name);
        if(it2 == it->second.end()) {
            return false;
        }
        
        it->second.erase(name);
        return true;
    }

    void handleEvent(sf::Event& event);
    void update();

    sf::Vector2i getMousePos(sf::RenderWindow* wind = nullptr) {
        return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
    }

    void setCurrentState(const StateType& type);
private:
    void loadBindings();

    Bindings m_bindings;
    Callbacks m_callbacks;
    StateType m_currentState;
    bool m_hasFocus;
};

#endif /* EVENTMANAGER_H */

