#pragma once

#include "MyActionRPG.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "SlateBrush.h"
#include "Define/RPGItemTypes.h"
#include "ItemActorBase.h"
#include "RPGItemDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FRPGItemDataTableRow : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    FRPGItemDataTableRow() {}

    /** ����ID*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    FName ItemID;

    /** ��������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    EItemType ItemType;

    /** װ����������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    EItemEquipType ItemEquipType;

    /** װ������Ҫ������ԣ���ɫ�ȼ�,���������ݣ�������*/


    /** ����Actor*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITEM)
    TSubclassOf<AItemActorBase> ItemActor;
};