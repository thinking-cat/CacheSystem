//
// Created by 13662 on 4/13/2025.
//
#pragma once

#include "LruCache.h"

/**
 *
 * @param targetKey The identifier of the cache node.
 * @param returnValue The value in the cache node, returned by reference.
 * @return true if key exists in the cache.
 */
template<typename KeyType, typename ValueType>
bool LruCache<KeyType, ValueType>::Get(const KeyType &targetKey, ValueType& returnValue) const {
    auto nodeIt = nodeMap_.find(targetKey);
    if (nodeIt != nodeMap_.end()) {
        returnValue = nodeIt->second->getValue();
        return true;
    }
    return false;
}

/**
 *
 * @param key The identifier of the cache node.
 * @param value The value to store in the cache node.
 */
template<typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::Put(const KeyType &key, const ValueType &value) {
    // write the value if the key exists
    if (auto nodeIt = nodeMap_.find(key); nodeIt != nodeMap_.end()) {
        const std::shared_ptr<NodeType> &nodePtr = nodeIt->second;
        nodePtr->setValue(value);
        Remove(nodePtr);
        Insert(nodePtr);
    } else {
        // Trying to insert a new node
        if (nodeMap_.size() == capacity_) {
            auto lruNode = dummyTail_->prev_.lock();
            if (lruNode) {
                Remove(lruNode);
                nodeMap_.erase(lruNode->getKey());
            }
        }
        InsertNode(key, value);
    }
}
template<typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::Insert(const std::shared_ptr<NodeType> &node) {
    node->next_ = dummyHead_->next_;
    node->prev = dummyHead_;
    node->next_->prev_ = node;
    dummyHead_->next_ = node;
}

template<typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::Insert(const KeyType &key, const ValueType &value) {
    std::shared_ptr<NodeType> newNode = std::make_shared<NodeType>(key, value);
    nodeMap_[key] = newNode;
    Insert(newNode);
}
template<typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::Remove(const std::shared_ptr<NodeType> &node) {
    node->prev->next_ = node->next_;
    node->next->prev_ = node->prev_;
}


