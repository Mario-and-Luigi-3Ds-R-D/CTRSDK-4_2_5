#pragma once

#include "nn/types.h"
#include "nn/util/util_NonCopyable.h"

namespace nn{
namespace fnd{
class IntrusiveQueue{
public:

    struct Item{
        nn::fnd::IntrusiveQueue::Item* mNextLink;
    };

    nn::fnd::IntrusiveQueue::Item* mHead;
    nn::fnd::IntrusiveQueue::Item* mTail;  
}; // IntrusiveQueue

class IntrusiveLinkedList{
public:

struct Item : nn::util::ADLFireWall::NonCopyable<Item> {
    Item* mPrevLink;
    Item* mNextLink;
};

nn::fnd::IntrusiveLinkedList::Item mHead;


}; // IntrusiveLinkedList

}
}