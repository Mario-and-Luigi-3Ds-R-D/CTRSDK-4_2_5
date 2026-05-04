#pragma once

#include "nn/Assert.h"
#include "nn/fnd/fnd_Result.h"
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
};

// IntrusiveLinkedList

template <typename T, typename Tag = void>
class IntrusiveLinkedList : private nn::util::NonCopyable<IntrusiveLinkedList<T, Tag> >{
public:

    class Item;

    void Insert(T* position, T* inserted);
    static void InsertBefore(Item* p, Item* q);
    void PushBack(T* p);
    void PushFront(T* p);
    T* GetNext(T* p) const;
    T* GetBack() const;
    T* GetPrevious(T* p) const;
    T* GetFront() const;
    void Erase(T* p);
    static void ClearLinks(Item* p);
    bool IsEmpty() const {
        return !mHead; 
    }
protected:
    Item* mHead;
};

//

// IntrusiveLinkedList::Item

//

template <typename T, typename Tag>
class IntrusiveLinkedList<T, Tag>::Item : private nn::util::NonCopyable<IntrusiveLinkedList<T, Tag>::Item> {
public:

    Item* mPrevLink;
    Item* mNextLink;
protected:
};

//

// Inlines

//


template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::Erase(T* p){
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(pNode->m_PreviousLink, MakeResultInvalidNode());
    if (pNode == pNode->mPrevLink){
        this->mHead = 0;
    }
    else{
        if (mHead == pNode){
            this->mHead = mHead->mNextLink;
        }
        pNode->mNextLink->mPrevLink = pNode->mPrevLink;
        pNode->mPrevLink->mNextLink = pNode->mNextLink;
    }
    ClearLinks(pNode);
}



template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetNext(T* p) const{
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(pNode->m_PreviousLink, MakeResultInvalidNode());
    if (p == this->GetBack()){
        return 0;
    }
    return static_cast<T*>(pNode->mNextLink);
}



template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::ClearLinks(Item* p){
    p->mPrevLink = p->mNextLink = 0;
}



template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::PushBack(T* p){
    Item* pNode = static_cast<Item*>(p);
    if (IsEmpty()){
        p->mPrevLink = p->mNextLink = p;
        this->mHead = p;
    }
    else{
        InsertBefore(mHead, pNode);
    }
}



template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetBack() const{
    if (IsEmpty()){
        return 0;
    }
    else{
        return static_cast<T*>(mHead->mPrevLink);
    }
}



template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::PushFront(T* p){
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(!pNode->mPrevLink, MakeResultAlreadyListed());
    if (IsEmpty()){
        p->mPrevLink = p->mNextLink = p;
    }
    else{
        InsertBefore(mHead, pNode);
    }
    this->mHead = p;
}



template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetFront() const{
    return static_cast<T*>(mHead);
}



template <typename T, typename Tag>
inline T* IntrusiveLinkedList<T, Tag>::GetPrevious(T* p) const{
    NN_ASSERT_WITH_RESULT(p, MakeResultInvalidAddress());
    Item* pNode = static_cast<Item*>(p);
    NN_ASSERT_WITH_RESULT(pNode->m_PreviousLink, MakeResultInvalidNode());
    if (p == this->GetFront()){
        return 0;
    }
    return static_cast<T*>(pNode->mPrevLink);
}



template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::InsertBefore(Item* p, Item* q){
    q->mNextLink = p;
    p->mPrevLink->mNextLink = q;
    q->mPrevLink = p->mPrevLink;
    p->mPrevLink = q;
}



template <typename T, typename Tag>
inline void IntrusiveLinkedList<T, Tag>::Insert(T* position, T* inserted){
    NN_ASSERT_WITH_RESULT(inserted, MakeResultInvalidAddress());
    Item* pNodeInserted = static_cast<Item*>(inserted);
    Item* pNodePosition = static_cast<Item*>(position);
    NN_ASSERT_WITH_RESULT(!pNodeInserted->m_PreviousLink, MakeResultAlreadyListed());
    if (pNodePosition == mHead){
        PushFront(inserted);
    }
    else if (pNodePosition){
        NN_ASSERT_WITH_RESULT(pNodePosition->m_PreviousLink, MakeResultInvalidNode());
        InsertBefore(pNodePosition, pNodeInserted);
    }
    else{
        PushBack(inserted);
    }
}


}
}
