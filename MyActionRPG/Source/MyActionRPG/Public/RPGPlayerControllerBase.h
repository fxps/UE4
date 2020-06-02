// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RPGPlayerControllerBase.generated.h"


/**
 * 
 */
UCLASS()
class MYACTIONRPG_API ARPGPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;

    // 添加一个新的装备道具
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool AddInventoryItem(URPGItem* NewItem, int32 ItemCount = 1, int32 ItemLevel = 1, bool bAutoSlot = true);

    // 获取装备数据
    UFUNCTION(BlueprintPure, Category = Inventory)
    bool GetInventoryItemData(URPGItem* Item, FRPGItemData& ItemData) const;

    /** 玩家拥有的Item列表(数量和等级) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<URPGItem*, FRPGItemData> InventoryData;

    /** 插槽对应的道具Map*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<FRPGItemSlot, URPGItem*> SlottedItems;

    /** 从保存数据加载装备到数组中 */
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool LoadInventory();

    /** 手动保存装备数据*/
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool SaveInventory();

    /**使用装备中的道具填充空的插槽*/
    UFUNCTION(BlueprintCallable, Category = Inventory)
    void FillEmptySlots();

    /** Native version above, called before BP delegate */
    FOnSlottedItemChangedNative OnSlottedItemChangedNative;

    /** Delegate called when an inventory slot has changed */
    UPROPERTY(BlueprintAssignable, Category = Inventory)
    FOnSlottedItemChanged OnSlottedItemChanged;

    /** Delegate called when the inventory has been loaded/reloaded */
    UPROPERTY(BlueprintAssignable, Category = Inventory)
    FOnInventoryLoaded OnInventoryLoaded;

    /** Native version above, called before BP delegate */
    FOnInventoryLoadedNative OnInventoryLoadedNative;

    // 蓝图回调函数
    UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
    void SlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item);
protected:
    /** Called when a global save game as been loaded */
    void HandleSaveGameLoaded(URPGSaveGame* NewSaveGame);
   
    /** 自动找一个空的槽位插入Item */
    bool FillEmptySlotWithItem(URPGItem* NewItem);

    /** 执行装备相关更新后的委托回调*/
    void NotifyInventoryItemChanged(bool bAdded, URPGItem* Item);
    void NotifySlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item);
    void NotifyInventoryLoaded();
};
