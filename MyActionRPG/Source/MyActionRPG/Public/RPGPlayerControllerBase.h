// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RPGInventoryInterface.h"
#include "RPGPlayerControllerBase.generated.h"


/**
 * 
 */
UCLASS()
class MYACTIONRPG_API ARPGPlayerControllerBase : public APlayerController, public IRPGInventoryInterface
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;

    // ���һ���µ�װ������
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool AddInventoryItem(URPGItem* NewItem, int32 ItemCount = 1, int32 ItemLevel = 1, bool bAutoSlot = true);

    /**ɾ��һ��װ������ */
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool RemoveInventoryItem(URPGItem* RemovedItem, int32 RemoveCount = 1);

    /**���ݵ������ͣ���ȡ�����б� */
    UFUNCTION(BlueprintCallable, Category = Inventory)
    void GetInventoryItems(TArray<URPGItem*>& Items, FPrimaryAssetType ItemType);

    /**���� Inventory��Item������ */
    UFUNCTION(BlueprintPure, Category = Inventory)
    int32 GetInventoryItemCount(URPGItem* Item) const;

    // ��ȡװ������
    UFUNCTION(BlueprintPure, Category = Inventory)
    bool GetInventoryItemData(URPGItem* Item, FRPGItemData& ItemData) const;

    /** ����slot�е�ֵ�������ָ����ն�Ӧslot */
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool SetSlottedItem(FRPGItemSlot ItemSlot, URPGItem* Item);

    /** ��ȡslot�ж�Ӧ��Item */
    UFUNCTION(BlueprintPure, Category = Inventory)
    URPGItem* GetSlottedItem(FRPGItemSlot ItemSlot) const;

    /** ����slots��ָ��type������Item */
    UFUNCTION(BlueprintCallable, Category = Inventory)
    void GetSlottedItems(TArray<URPGItem*>& Items, FPrimaryAssetType ItemType, bool bOutputEmptyIndexes);

    /** ���ӵ�е�Item�б�(�����͵ȼ�) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<URPGItem*, FRPGItemData> InventoryData;

    /** ���װ�����еĵ���*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<FRPGItemSlot, URPGItem*> SlottedItems;

    /** �ӱ������ݼ���װ���������� */
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool LoadInventory();

    /** �ֶ�����װ������*/
    UFUNCTION(BlueprintCallable, Category = Inventory)
    bool SaveInventory();

    /**ʹ��װ���еĵ������յĲ��*/
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

    FOnInventoryItemChangedNative OnInventoryItemChangedNative;
    
    UPROPERTY(BlueprintAssignable, Category = Inventory)
    FOnInventoryItemChanged OnInventoryItemChanged;

	/** Called after the inventory was changed and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void InventoryItemChanged(bool bAdded, URPGItem* Item);

    // ��ͼ�ص�����
    UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
    void SlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item);

    /** ʵ��IRPGInventoryInterface�ӿڵĺ���*/
    virtual const TMap<URPGItem*, FRPGItemData>& GetInventoryDataMap() const override
    {
        return InventoryData;
    }
    virtual const TMap<FRPGItemSlot, URPGItem*>& GetSlottedItemMap() const override
    {
        return SlottedItems;
    }
    virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() override
    {
        return OnInventoryItemChangedNative;
    }
    virtual FOnSlottedItemChangedNative& GetSlottedItemChangedDelegate() override
    {
        return OnSlottedItemChangedNative;
    }
    virtual FOnInventoryLoadedNative& GetInventoryLoadedDelegate() override
    {
        return OnInventoryLoadedNative;
    }
protected:
    /** Called when a global save game as been loaded */
    void HandleSaveGameLoaded(URPGSaveGame* NewSaveGame);
   
    /** �Զ���һ���յĲ�λ����Item */
    bool FillEmptySlotWithItem(URPGItem* NewItem);

    /** ִ��װ����ظ��º��ί�лص�*/
    void NotifyInventoryItemChanged(bool bAdded, URPGItem* Item);
    void NotifySlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item);
    void NotifyInventoryLoaded();
};
