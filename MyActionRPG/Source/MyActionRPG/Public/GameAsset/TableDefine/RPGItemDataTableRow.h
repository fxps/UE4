#pragma once
#include "MyActionRPG.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "SlateBrush.h"
#include "Define/RPGItemTypes.h"
#include "ItemActorBase.h"
#include "GameSystem/ItemNew/ItemBase.h"
#include "RPGItemDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FRPGItemDataTableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    FRPGItemDataTableRow() 
    {
        ItemObjClass = UItemBase::StaticClass();
        CanStacked = true;
    }

    /** ����ID*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    FName ItemID;

    /** ��������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    EItemType ItemType;

    /** װ����������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    EItemEquipType ItemEquipType;

    /** �Ƿ�ɶѵ�*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    bool CanStacked;

    /** ����UObject*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    TSubclassOf<UItemBase> ItemObjClass;

    /** ����Actor*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    TSubclassOf<AItemActorBase> ItemActorClass;

    /** ����Actor�İ��*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    FName BindSocketName;

    /** ���߸����ļ���*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    TSubclassOf<URPGGameplayAbility> AbilityClass;
};