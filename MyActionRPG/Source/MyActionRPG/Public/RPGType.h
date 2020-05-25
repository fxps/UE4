#pragma once
#include "UObject/PrimaryAssetId.h"
#include "RPGType.generated.h"
/**
*
*/
class URPGItem;

USTRUCT(BlueprintType)
struct MYACTIONRPG_API FRPGItemSlot
{
    GENERATED_BODY()

    /** ���ԷŽ���ǰ���ӵĵ�������*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    FPrimaryAssetType ItemType;

    /** �������*/ 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    int32 SlotNumber;

    /** Equality operators */
    bool operator==(const FRPGItemSlot& Other) const
    {
        return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
    }

    bool operator!=(const FRPGItemSlot& Other) const
    {
        return !(*this == Other);
    }

    /** ʵ������TMap Keyֵ��GetTypeHash���� */
    friend inline uint32 GetTypeHash(const FRPGItemSlot& Key)
    {
        uint32 Hash = 0;

        Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
        Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
        return Hash;
    }

    /** Returns true if slot is valid */
    bool IsValid() const
    {
        return ItemType.IsValid() && SlotNumber >= 0;
    }
};

USTRUCT(BlueprintType)
struct MYACTIONRPG_API FRPGItemData
{
    GENERATED_BODY()

        FRPGItemData() :
        ItemCount(1),
        ItemLevel(1) {}

    FRPGItemData(int32 InItemCount, int32 InItemLevel)
        : ItemCount(InItemCount)
        , ItemLevel(InItemLevel)
    {}

    /** ����ʵ������������Զ����С��1 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    int32 ItemCount;

    /** ���ߵȼ�����Զ����С��1*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
    int32 ItemLevel;

    bool operator==(const FRPGItemData& Other) const
    {
        return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
    }

    bool operator!=(const FRPGItemData& Other) const
    {
        return !(*this == Other);
    }

    bool IsValid() const
    {
        return ItemCount > 0;
    }

    /** ����ItemData*/
    void UpdateItemData(const FRPGItemData& Other, int32 MaxCount, int32 MaxLevel)
    {
        if (MaxCount <= 0)
        {
            MaxCount = MAX_int32;
        }

        if (MaxLevel <= 0)
        {
            MaxLevel = MAX_int32;
        }

        ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
        ItemLevel = FMath::Clamp(Other.ItemLevel, 1, MaxLevel);
    }
};