/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LruCache.h
 * Author: cpu02331
 *
 * Created on May 20, 2019, 3:55 PM
 */

#ifndef LRUCACHE_H
#define LRUCACHE_H


#include <map>

using namespace std;

template <class Key, class Value>
class lruCache {
public:

    lruCache() : maxLength(100), next(0), upperBound(2000000000), length(0) {
    }

    lruCache(int n) : maxLength(n), next(0), upperBound(2000000000), length(0) {
        if (n < 2) {
            maxLength = 2;
        }
    }

    bool add(Key key, Value val) {
        try {
            table.at(key);
            lru.at(key) = genNext();
            return false;
        } catch (std::out_of_range e) {
            table.insert(std::pair<Key, Value>(key, val));
            lru.insert(std::pair<Key, int>(key,genNext()));
        }
        if (length == maxLength) {
            auto t = lru.begin();
            for(auto i = lru.begin(); i != lru.end();++i){
                if (i->second < t->second){
                    t = i;
                }
            }
            Key e = t->first;
            table.erase(e);
            lru.erase(e);
        }else {
            length++;
        }
        return true;
    }

    bool update(Key key, Value val) {
        remove(key);
        return add(key, val);
    };

    bool remove(Key key) {
        if (length == 0) return true;
        try {
            table.at(key);
            length--;
            table.erase(key);
            lru.erase(key);
            return true;
        } catch (std::out_of_range e){    
            return false;
        }
    };

    Value get(Key key) {
        Value val = table.at(key);
        lru.at(key) = genNext();
        return val;

    };
private:
    map<Key, Value> table;
    map<Key, int> lru;
    
    int maxLength ,length, upperBound , next;
    
    int genNext(){
        next = (next + 1) % upperBound;
        if (next == 0){
            next = reCache();
        }
        return next;
    }
    int reCache(){
        //todo::sort this
        int t = 0;
        for (auto i = lru.begin(); i != lru.end(); ++i) {
            lru.at(i->first) = t++;
        }
        return t;
    }
};

#endif