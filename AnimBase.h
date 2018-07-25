/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AnimBase.h
 * Author: default
 *
 * Created on May 14, 2018, 4:49 PM
 */

#ifndef ANIMBASE_H
#define ANIMBASE_H

#include <string>


class SpriteSheet;

using Frame = unsigned int;

class AnimBase {
    friend class SpriteSheet;
public:
    AnimBase();
    virtual ~AnimBase();
    
    void setSpriteSheet(SpriteSheet* sheet);
    void setFrame(Frame frame);
    void setStartFrame(Frame frame);
    void setEndFrame(Frame frame);
    void setFrameRow(Frame frame);
    void setActionStart(Frame frame);
    void setActionEnd(Frame frame);
    void setFrameTime(float time);
    void setLooping(bool loop);
    void setName(const std::string& name);
    
    SpriteSheet* getSpriteSheet();
    Frame getFrame();
    Frame getStartFrame();
    Frame getEndFrame();
    Frame getRowFrame();
    
    int getActionStart();
    int getActionEnd();
    float getFrameTime();
    float getElapsedTime();
    bool isLooping();
    bool isPlaying();
    bool isInAction();
    std::string getName();
    
    void play();
    void pause();
    void stop();
    void reset();
    
    virtual void update(const float& dt);
    
    friend std::stringstream& operator >> (std::stringstream& stream, AnimBase& obj) {
        obj.readIn(stream);
        return stream;
    }
protected:
    virtual void frameStep() = 0;
    virtual void cropSprite() = 0;
    virtual void readIn(std::stringstream& stream) = 0;
    
    Frame m_frameCurrent;
    Frame m_frameStart;
    Frame m_frameEnd;
    Frame m_frameRow;
    int m_frameActionStart;
    int m_frameActionEnd;
    float m_frameTime;
    float m_elapsedTime;
    bool m_loop;
    bool m_playing;
    
    std::string m_name;
    SpriteSheet* m_spriteSheet;
};

#endif /* ANIMBASE_H */

