#pragma once

#include <nn/types.h>
#include <nn/Result.h>
#include <nn/assert.h>
#include <nn/util/util_Int64.h>
#include <nn/dbm/dbm_RomPathTool.h>
#include <nn/dbm/dbm_Parameters.h>

namespace nn{
namespace dbm{

template <class BucketStorage_,class EntryStorage_,class Key_,class Value_,int MAX_EXTRA_SIZE_>
class KeyValueRomStorageTemplate{
public:
    typedef BucketStorage_ BucketStorage;
    typedef EntryStorage_ EntryStorage;
    typedef Key_ Key;
    typedef Value_ Value;
    typedef u32 Position;
    typedef u32 IndexBucket;

    static const Position STORAGE_FREEENTRY = 0xFFFFFFFF;

    struct StorageElement{
        Key key;
        Value value;
        Position next;
        u32 size;
    };

private:
    util::Int64<s64> mOffsetBucket;
    u32 mCountBucket;
    BucketStorage* mpBufBucket;
    s64 mOffsetKeyValue;
    u32 mSizeKeyValue;
    EntryStorage* mpBufKeyValue;
    u32 mTotalEntrySize;
    u32 mEntryCount;
public:

   KeyValueRomStorageTemplate(): 
        mOffsetBucket(0),
        mCountBucket(0),
        mpBufBucket(NULL),
        mOffsetKeyValue(0),
        mSizeKeyValue(0),
        mpBufKeyValue(NULL),
        mTotalEntrySize(0),
        mEntryCount(0)
    {}

    static u32 QueryBucketCount(u32 size){
        return size / sizeof(Position);
    }

    Result Initialize(BucketStorage* pBucket, s64 offsetBucket, u32 countBucket, EntryStorage* pKeyValue, s64 offsetKeyValue, u32 sizeKeyValue){
        NN_NULL_TASSERT_(pBucket);
        NN_NULL_TASSERT_(pKeyValue);
        NN_TASSERT_(countBucket > 0);

        mpBufBucket = pBucket;
        mOffsetBucket = offsetBucket;
        mCountBucket = countBucket;

        mpBufKeyValue = pKeyValue;
        mOffsetKeyValue = offsetKeyValue;
        mSizeKeyValue = sizeKeyValue;

        return ResultSuccess();
    }

    Result GetInternal(Position* pPosition,Value* pValue,const Key& key,u32 hashKey,const void* pExtraKey,size_t extraSize) const{
        Position pos;
        Position posPrevious;
        StorageElement storeElement;

        NN_NULL_TASSERT_(pPosition);
        NN_NULL_TASSERT_(pValue);

        Result res;
        res = FindInternal(&pos,&posPrevious,&storeElement,key,hashKey,pExtraKey,extraSize);
        if (res.IsFailure()){
            return res;
        }

        *pPosition = pos;
        *pValue = storeElement.value;

        return ResultSuccess();
    }

    Result GetByPosition(Key* pKey,Value* pValue,void* pExtraKey,size_t* pExtraSize,Position pos) const{
        NN_NULL_TASSERT_(pKey);
        NN_NULL_TASSERT_(pValue);

        StorageElement storeElement;
        Result result = ReadKeyValue(&storeElement, pExtraKey, pExtraSize, pos);

        if (result.IsFailure()){
            return result;
        }

        *pKey = storeElement.key;
        *pValue = storeElement.value;

        return ResultSuccess();
    }
private:
    IndexBucket HashToBucket(u32 hashKey) const{
        return hashKey % mCountBucket;
    }

    Result FindInternal(Position* pPosition,Position* pPreviousPosition,StorageElement* pStoreElement,const Key& key,u32 hashKey,const void* pExtraKey,size_t extraSize) const{
        Result res;

        NN_NULL_TASSERT_(pPosition);
        NN_NULL_TASSERT_(pPreviousPosition);
        NN_NULL_TASSERT_(pStoreElement);
        NN_TASSERT_(this->mCountBucket > 0);
        NN_TASSERT_(this->mSizeKeyValue >= 0);

        *pPosition = 0;
        *pPreviousPosition = 0;

        IndexBucket indexBucket = HashToBucket(hashKey);

        Position posTop;
        res = ReadBucket(&posTop, indexBucket);
        if (res.IsFailure()){
            return res;
        }
        NN_TASSERT_((posTop == STORAGE_FREEENTRY) || (posTop < mSizeKeyValue));

        if (posTop == STORAGE_FREEENTRY){
            return ResultKeyNotFound();
        }

        u8 buf[MAX_EXTRA_SIZE_];

        Position pos = posTop;
        while (true){
            size_t currExtraSize = 0;
            res = ReadKeyValue(pStoreElement, buf, &currExtraSize, pos);
            if (res.IsFailure()){
                return res;
            }

            if (key.IsEqual(pStoreElement->key, pExtraKey, extraSize, buf, currExtraSize)){
                *pPosition = pos;
                return ResultSuccess();
            }

            *pPreviousPosition = pos;
            pos = pStoreElement->next;
            if (STORAGE_FREEENTRY == pos){
                return Result(0xc880446f);
            }
        }
    }

    inline Result ReadBucket(Position* pKvStorePosition, IndexBucket index) const{
        NN_NULL_TASSERT_(pKvStorePosition);
        NN_NULL_TASSERT_(mpBufBucket);
        NN_TASSERT_(index < mCountBucket);

        s64 offset = mOffsetBucket + index * sizeof(Position);
        return mpBufBucket->ReadBytes(offset, pKvStorePosition, sizeof(Position));
    }

    inline Result ReadKeyValue(StorageElement* pElement,void* pExtraKey,size_t* pExtraSize,Position pos) const{
        NN_NULL_TASSERT_(pElement);
        NN_NULL_TASSERT_(this->mpBufKeyValue);
        NN_TASSERT_(pos < this->mSizeKeyValue);

        Result res;

        s64 offset = mOffsetKeyValue + pos;
        res = mpBufKeyValue->ReadBytes(offset, pElement, sizeof(StorageElement));
        if (res.IsFailure()){
            return res;
        }

        if ((pExtraKey != NULL) && (pExtraSize != NULL)){
            *pExtraSize = pElement->size;
            if (pElement->size > 0){
                res = mpBufKeyValue->ReadBytes(offset + sizeof(StorageElement), pExtraKey, pElement->size);
                if (res.IsFailure()){
                    return res;
                }
            }
        }

        return ResultSuccess();
    }
};

}
}