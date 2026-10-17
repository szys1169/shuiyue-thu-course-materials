#pragma once
#include <list>
#include <unordered_map>
#include <utility>

template<typename Key>
class PopStrategy {
public:
    virtual void visit(const Key& key) = 0;
    virtual Key pop() = 0;
    virtual ~PopStrategy() = default;
};

template<typename Key>
class FIFOStrategy : public PopStrategy<Key> {
private:
    std::list<Key> shuju;       
    std::unordered_map<Key, typename std::list<Key>::iterator> jilu; 

public:
    void visit(const Key& key) override {
        if (jilu.find(key) == jilu.end()) {
            shuju.push_back(key);
            jilu[key] = std::prev(shuju.end());
        }
    }

    Key pop() override {
        Key toRemove = shuju.front();
        jilu.erase(toRemove);
        shuju.pop_front();
        return toRemove;
    }
};

template<typename Key>
class LRUStrategy : public PopStrategy<Key> {
private:
    std::list<Key> shuju;      
    std::unordered_map<Key, typename std::list<Key>::iterator> jilu;

public:
    void visit(const Key& key) override {
        if (jilu.find(key) != jilu.end()) {
            shuju.erase(jilu[key]);
        }
        shuju.push_back(key);
        jilu[key] = std::prev(shuju.end());
    }

    Key pop() override {
        Key toRemove = shuju.front();
        jilu.erase(toRemove);
        shuju.pop_front();
        return toRemove;
    }
};