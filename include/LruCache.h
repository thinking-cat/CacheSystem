//
// Created by adim on 3/30/2025.
//

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <memory>
#include <unordered_map>
#include "LruNode.h"

template<typename KeyType, typename ValueType>
class LruCache
{
    using NodeType = LruNode<KeyType, ValueType>;

public:
    bool Get(const KeyType& targetKey, ValueType& returnValue) const;
    void Put(const KeyType& key, const ValueType& value);
private:
    void Insert(const std::shared_ptr<NodeType>& node);
    void Insert(const KeyType &key, const ValueType &value);
    void Remove(const std::shared_ptr<NodeType>& node);
public:
    explicit LruCache(const std::size_t capacity)
        : nodeMap_()
        , dummyHead_(std::make_shared<NodeType>())
        , dummyTail_(std::make_shared<NodeType>())
        , capacity_(capacity)
    {
        dummyHead_->next_ = dummyTail_;
        dummyTail_->prev_ = dummyHead_;
    }

    LruCache(const LruCache& other) = delete;
    LruCache& operator = (const LruCache& other) = delete;
    LruCache(LruCache&& other) = default;
    LruCache& operator = (LruCache&& other) = default;


    ~LruCache() = default;
private:
    std::unordered_map<KeyType, std::shared_ptr<NodeType>> nodeMap_;
    std::shared_ptr<NodeType> dummyHead_;
    std::shared_ptr<NodeType> dummyTail_;
    std::size_t capacity_;
};


#endif //LRUCACHE_H
