//
// Created by adim on 3/30/2025.
//

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <memory>
#include <unordered_map>

template<typename Key, typename Value>
class LruNode{
public:
    LruNode(Key key, Value value)
        : key_(key)
        , value_(value)
        , next_(nullptr)
        , prev_(nullptr)
    {}

private:
    Key key_;
    Value value_;
    std::shared_ptr<LruNode<Key, Value>> next_;
    std::shared_ptr<LruNode<Key, Value>> prev_;
};

template<typename Key, typename Value>
class LruCache{
public:
    LruCache(int capacity)
        : capacity_(capacity)
        // Empty Node
        , L_(std::make_unique<LruNode<Key, Value>>(Key(), Value()))
        , R_(std::make_unique<LruNode<Key, Value>>(Key(), Value()))
    {}

    bool get(const Key& key, Value& value){
        if (hashmap_.find(key) != hashmap_.end()){
            LruNode<Key, Value>* node = hashmap_[key];
            remove(node);
            insert(node->key_, node->value_);
            value = node->value_;
            return true;
        }
        return false;
    }

    void put(Key key, Value value){
        if (hashmap_.find(key) != hashmap_.end()){
            LruNode<Key, Value>* node = hashmap_[key];
            remove(node);
            insert(node->key_, node->value_);
        }
        else{
            if (hashmap_.size() == capacity_){
                remove(L_->next);
                insert(key, value);
            }
            else{
                insert(key, value);
            }
        }
    }
private:
    std::size_t capacity_;
    std::unordered_map<Key, std::shared_ptr<LruNode<Key, Value>>> hashmap_;
    std::unique_ptr<LruNode<Key, Value>> L_, R_;
};


#endif //LRUCACHE_H
