// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGType.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstanceBase.generated.h"

/**
 * ���ɻ��ڴ������ͼ������ͼ�������ص��߼�
 * ��Ҫ������Ϸ���ݵı��棬����Ϸ��Ӧ״̬���¼�����
 */
UCLASS()
class MYACTIONRPG_API URPGGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
    URPGGameInstanceBase();

    /**�����Ĭ�ϵ�װ�������б�*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<FPrimaryAssetId, FRPGItemData> DefaultInventory;

    /**ÿ�����͵Ĳ������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<FPrimaryAssetType, int32> ItemSlotsPerType;

    /**���ر������ݵ�ԭ��ί��*/
    FOnSaveGameLoadedNative OnSaveGameLoadedNative;

    /**���ر���������ɺ���õ�ί��*/
    UPROPERTY(BlueprintAssignable, Category = Inventory)
    FOnSaveGameLoaded OnSaveGameLoaded;

    /**���ر������ݵĶ���ָ��*/
    UFUNCTION(BlueprintCallable, Category = Save)
    URPGSaveGame* GetCurrentSaveGame();

    /**��������Ĭ�ϵ���*/
    void AddDefaultInventory(URPGSaveGame* SaveGame, bool bRemoveExtra);
protected:
    UPROPERTY()
    URPGSaveGame* CurrentSaveGame;
};
