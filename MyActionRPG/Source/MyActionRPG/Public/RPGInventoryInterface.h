// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYACTIONRPG_API IRPGInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    /** ��ȡӵ�е�Item���е�Data*/
    virtual const TMap<URPGItem*, FRPGItemData>& GetInventoryDataMap() const = 0;

    /** ��ȡ��ǰװ�����еĵ���*/
    virtual const TMap<FRPGItemSlot, URPGItem*>& GetSlottedItemMap() const = 0;

    /** ��ȡ���߱仯�Ļص�ί��*/
    virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() = 0;

    /** ��ȡװ���������仯ʱ�Ļص�ί��*/
    virtual FOnSlottedItemChangedNative& GetSlottedItemChangedDelegate() = 0;

    /** ��ȡװ������ʱ�Ļص�ί��*/
    virtual FOnInventoryLoadedNative& GetInventoryLoadedDelegate() = 0;
};
