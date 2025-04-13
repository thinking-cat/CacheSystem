//
// Created by 13662 on 4/13/2025.
//

#ifndef LRUNODE_H
#define LRUNODE_H
#include <utility>
#include <memory>

template<typename KeyType, typename ValueType>
class LruNode
{
public:
    KeyType getKey() const {return key_;}
    ValueType& getValue() {return value_;}
    void setValue(const ValueType& value) {value_ = value;}
    [[nodiscard]] std::size_t getSize() const {return accessCount_;}
    void incrementAccessCount() {++accessCount_;}
public:
    LruNode() = default;
    LruNode(const KeyType& key, const ValueType& value)
        : key_(key)
        , value_(value)
        , next_(nullptr)
        , prev_(nullptr)
    {}
    LruNode(const LruNode<KeyType, ValueType>& other) = delete;
    LruNode& operator = (const LruNode<KeyType, ValueType>& other) = delete;
    LruNode(LruNode<KeyType, ValueType>&& other) noexcept
        : LruNode<KeyType, ValueType>()
    {
        swap(*this, other);
    }
    LruNode& operator = (LruNode<KeyType, ValueType>&& other) noexcept
    {
        if (this == &other)
            return *this;
        LruNode<KeyType, ValueType> temp(std::move(other));
        swap(*this, temp);
        return *this;
    }
private:
    KeyType key_;
    ValueType value_;
    std::shared_ptr<LruNode<KeyType, ValueType>> next_;
    std::weak_ptr<LruNode<KeyType, ValueType>> prev_;
    std::size_t accessCount_{0};

    // swap-and-move idiom
    friend void swap(LruNode<KeyType, ValueType>& a, LruNode<KeyType, ValueType>& b) noexcept
    {
        std::swap(a.key_, b.key_);
        std::swap(a.value_, b.value_);
        std::swap(a.next_, b.next_);
        std::swap(a.prev_, b.prev_);
        std::swap(a.accessCount_, b.accessCount_);
    }

    friend class LRUCache;
};

#endif //LRUNODE_H
