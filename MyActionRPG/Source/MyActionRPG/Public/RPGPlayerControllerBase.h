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

    /** ���ӵ�е�Item�б�(�����͵ȼ�) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<URPGItem*, FRPGItemData> InventoryData;

    /** ��۶�Ӧ�ĵ���Map*/
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

    /** Delegate called when the inventory has been loaded/reloaded */
    UPROPERTY(BlueprintAssignable, Category = Inventory)
    FOnInventoryLoaded OnInventoryLoaded;

    /** Native version above, called before BP delegate */
    FOnInventoryLoadedNative OnInventoryLoadedNative;
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
