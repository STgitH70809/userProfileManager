/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "LruCache.h"

template<class Key,class Value>
bool lruCache<Key,Value>::add(Key key, Value val) {
    try {
        table.at(key);
        lru.at(key) = genNext();
        return false;
    } catch (std::out_of_range e) {
        table.insert(std::pair<Key, Value>(key, val));
        lru.insert(std::pair<Key, int>(key, genNext()));
    }
    if (length == maxLength) {
        auto t = lru.begin();
        for (auto i = lru.begin(); i != lru.end(); ++i) {
            if (smaller(i->second, t->second)) {
                t = i;
            }
        }
        Key e = t->first;
        table.erase(e);
        lru.erase(e);
    } else {
        length++;
    }
    return true;
}

template<class Key,class Value>
bool lruCache<Key,Value>::update(Key key, Value val) {
    remove(key);
    return add(key, val);
};

template<class Key,class Value>
bool lruCache<Key,Value>::remove(Key key) {
    if (length == 0) return true;
    try {
        table.at(key);
        length--;
        table.erase(key);
        lru.erase(key);
        return true;
    } catch (std::out_of_range e) {
        return false;
    }
};

template<class Key,class Value>
Value lruCache<Key,Value>::get(Key key) {
    Value val = table.at(key);
    lru.at(key) = genNext();
    return val;

};