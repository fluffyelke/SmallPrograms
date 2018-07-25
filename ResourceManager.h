/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceManager.h
 * Author: default
 *
 * Created on May 14, 2018, 4:17 PM
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <fstream>

template<typename Derived, typename T>
class ResourceManager {
public:
    //Constructor
    ResourceManager(const std::string& pathsFile) {
        loadPaths(pathsFile);
    }
    //Deconstructor
    virtual ~ResourceManager() {
        purgeResources();
    }
    
    T* getResource(const std::string& id) {
        auto res = findResource(id);
        return (res ? res->first : nullptr);
    }
    
    bool requireResource(const std::string& id) {
        auto res = findResource(id);
        if(res) {
            ++res->second;
            return true;
        }
        auto path = m_paths.find(id);
        if(path == m_paths.end()) {
            return false;
        }
        T* resource = load(path->second);
        if(!resource) {
            return false;
        }
        m_resources.emplace(id, std::make_pair(resource, 1));
        return true;
    }
    
    bool releaseResource(const std::string& id) {
        auto res = findResource(id);
        if(!res) {
            return false;
        }
        --res->second;
        if(!res->second) {
            unload(id);
        }
        return true;
    }
    
    void purgeResources() {
        while(m_resources.begin() != m_resources.end()) {
            std::cout << "Removing: " << m_resources.begin()->first << std::endl;
            delete m_resources.begin()->second.first;
            m_resources.erase(m_resources.begin());
        }
        std::cout << "Purging finished.\n";
    }
    
protected:
    
    T* load(const std::string& path) {
        return static_cast<Derived*>(this)->load(path);
    }
    
    
private:
    
    //Methods
    std::pair<T*, unsigned int>* findResource(const std::string& id) {
        auto it = m_resources.find(id);
        return ( it != m_resources.end() ? &it->second : nullptr);
    }
    
    bool unload(const std::string& id) {
        auto it = m_resources.find(id);
        if(it == m_resources.end()) {
            return false;
        }
        delete it->second.first;
        m_resources.erase(it);
        return true;
    }
    
    void loadPaths(const std::string& pathFile) {
        std::ifstream paths;
        paths.open(pathFile);
        
        if(paths.is_open()) {
            std::string line;
            while(std::getline(paths, line)) {
                std::stringstream keystream{line};
                std::string pathName;
                std::string path;
                keystream >> pathName;
                keystream >> path;
                m_paths.emplace(pathName, path);
            }
            paths.close();
            return;
        }
        std::cerr << "! Failed to load path file: " << pathFile << std::endl;
    }       
    
    //Members
    std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
    std::unordered_map<std::string, std::string> m_paths;
};



#endif /* RESOURCEMANAGER_H */

