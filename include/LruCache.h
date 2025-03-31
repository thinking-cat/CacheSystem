//
// Created by adim on 3/30/2025.
//

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <memory>
#include <unordered_map>
#include <list>

template<typename Key, typename Value>
class LruNode
{
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
class LruCache
{
	using LruNodePtr = std::shared_ptr<LruNode<Key, Value>>;

public:
	LruCache()
		: capacity_(0)
		, hashMap_()
		, list_({dummyHead_, dummyTail_})
		, dummyHead_(std::make_unique<LruNode<Key, Value>>())
		, dummyTail_(std::make_unique<LruNode<Key, Value>>())
	{}

	LruCache(std::size_t capacity)
	    : capacity_(0)
	    , hashMap_()
	    , list_({dummyHead_, dummyTail_})
	    , dummyHead_(std::make_unique<LruNode<Key, Value>>())
	    , dummyTail_(std::make_unique<LruNode<Key, Value>>())
	{}

	void put(Key key, Value value)
	{

	}

private:
	std::size_t capacity_;
	std::unordered_map<Key, LruNodePtr> hashMap_;
	std::list<LruNode<Key, Value>> list_;
	std::unique_ptr<LruNode<Key, Value>> dummyHead_, dummyTail_;
};


#endif //LRUCACHE_H
