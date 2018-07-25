/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimBase.cpp
 * Author: default
 * 
 * Created on May 14, 2018, 4:49 PM
 */

#include "AnimBase.h"
#include "SpriteSheet.h"
#include <iostream>
AnimBase::AnimBase() 
    : m_frameCurrent{0},
      m_frameStart{0},
      m_frameEnd{0},
      m_frameRow{0},
      m_frameTime{0.f},
      m_elapsedTime{0.f},
      m_frameActionStart{-1},
      m_frameActionEnd{-1},
      m_loop{false},
      m_playing{false} {

}


AnimBase::~AnimBase() {
}

void AnimBase::setFrame(Frame frame) {
    if(frame >= m_frameStart && frame <= m_frameEnd || frame >= m_frameEnd && frame <= m_frameEnd) {
        m_frameCurrent = frame;
    }
}

bool AnimBase::isInAction() {
    if(m_frameActionStart == -1 || m_frameActionEnd == -1) {
        return false;
    }
    return (m_frameCurrent >= m_frameActionStart && m_frameCurrent <= m_frameActionEnd);
}

void AnimBase::reset() {
    m_frameCurrent = m_frameStart;
    m_elapsedTime = 0.f;
    cropSprite();
}

void AnimBase::update(const float& dt) {
    if(!m_playing) {
        return;
    }
    m_elapsedTime += dt;
    if(m_elapsedTime < m_frameTime) {
        return;
    }

    frameStep();
    cropSprite();
    m_elapsedTime = 0;
}

void AnimBase::setActionEnd(Frame frame) {
    m_frameActionEnd = frame;
}

void AnimBase::setActionStart(Frame frame) {
    m_frameActionStart = frame;
}

void AnimBase::setEndFrame(Frame frame) {
    m_frameEnd = frame;
}

void AnimBase::setFrameRow(Frame frame) {
    m_frameRow = frame;
}

void AnimBase::setFrameTime(float time) {
    m_frameTime = time;
}

void AnimBase::setLooping(bool loop) {
    m_loop = loop;
}

void AnimBase::setName(const std::string& name) {
    m_name = name;
}

void AnimBase::setSpriteSheet(SpriteSheet* sheet) {
    m_spriteSheet = sheet;
}

void AnimBase::setStartFrame(Frame frame) {
    m_frameStart = frame;
}

int AnimBase::getActionEnd() {
    return m_frameActionEnd;
}

int AnimBase::getActionStart() {
    return m_frameActionStart;
}

float AnimBase::getElapsedTime() {
    return m_elapsedTime;
}

Frame AnimBase::getEndFrame() {
    return m_frameEnd;
}

Frame AnimBase::getFrame() {
    return m_frameCurrent;
}

float AnimBase::getFrameTime() {
    return m_frameTime;
}

std::string AnimBase::getName() {
    return m_name;
}

Frame AnimBase::getRowFrame() {
    return m_frameRow;
}

SpriteSheet* AnimBase::getSpriteSheet() {
    return m_spriteSheet;
}

Frame AnimBase::getStartFrame() {
    return m_frameStart;
}

bool AnimBase::isLooping() {
    return m_loop;
}

bool AnimBase::isPlaying() {
    return m_playing;
}

void AnimBase::pause() {
    m_playing = false;
}

void AnimBase::play() {
    m_playing = true;
}

void AnimBase::stop() {
    m_playing = false;
    reset();
}






