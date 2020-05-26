// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerControllerBase.h"
#include "RPGGameInstanceBase.h"
#include "RPGAssetManager.h"
#include "RPGSaveGame.h"

void ARPGPlayerControllerBase::BeginPlay()
{
    // �������е���
    LoadInventory();

    Super::BeginPlay();
}

bool ARPGPlayerControllerBase::LoadInventory()
{
    InventoryData.Reset();
    SlottedItems.Reset();

    // ͨ��world��ȡGameInstance
    UWorld* World = GetWorld();
    URPGGameInstanceBase* GameInstance = World ? World->GetGameInstance<URPGGameInstanceBase>() : nullptr;

    if (!GameInstance)
    {
        return false;
    }

    // ��ί�лص�
    if (!GameInstance->OnSaveGameLoadedNative.IsBoundToObject(this))
    {
        GameInstance->OnSaveGameLoadedNative.AddUObject(this, &ARPGPlayerControllerBase::HandleSaveGameLoaded);
    }

    // ItemSlotsPerType�д�ŵĲ�����ͼ����������б�ÿ�������ж����ۣ��������еĲ�۷ŵ�SlottedItems��
    for (const TPair<FPrimaryAssetType, int32>& Pair: GameInstance->ItemSlotsPerType)
    {
        for (int32 SlotNumber = 0; SlotNumber < Pair.Value; SlotNumber++)
        {
            // �������еĲ�ۣ���ǰ��Ϊ�ղ��
            SlottedItems.Add(FRPGItemSlot(Pair.Key, SlotNumber), nullptr);
        }
    }

    URPGSaveGame* CurrentSaveGame = GameInstance->GetCurrentSaveGame();
    URPGAssetManager& AssetManager = URPGAssetManager::Get();
    if (CurrentSaveGame)
    {
        // ����SaveGame.InventoryData�������InventoryData��SlottedItems
        bool bFoundAnySlots = false;
        for (const TPair<FPrimaryAssetId, FRPGItemData>& ItemPair : CurrentSaveGame->InventoryData)
        {
            // ������ԴID������һ���������ö���
            URPGItem* LoadedItem = AssetManager.ForceLoadItem(ItemPair.Key);

            if (LoadedItem != nullptr)
            {
                InventoryData.Add(LoadedItem, ItemPair.Value);
            }
        }

        // ����SaveGame.SlottedItems�������SlottedItems
        for (const TPair<FRPGItemSlot, FPrimaryAssetId>& ItemPair : CurrentSaveGame->SlottedItems)
        {
            // ������ԴID������һ���������ö���
            URPGItem* LoadedItem = AssetManager.ForceLoadItem(ItemPair.Value);
            if (LoadedItem != nullptr)
            {
                SlottedItems.Add(ItemPair.Key, LoadedItem);
                bFoundAnySlots = true;
            }
        }

        if (!bFoundAnySlots)
        {
            FillEmptySlots();
        }

        NotifyInventoryLoaded();
    }
    
   

    return true;
}

bool ARPGPlayerControllerBase::SaveInventory()
{
    return true;
}

void ARPGPlayerControllerBase::FillEmptySlots()
{
    bool bShouldSave = false;
    for (const TPair<URPGItem*, FRPGItemData>& Pair : InventoryData)
    {
        bShouldSave |= FillEmptySlotWithItem(Pair.Key);
    }

    if (bShouldSave)
    {
        SaveInventory();
    }
}

void ARPGPlayerControllerBase::HandleSaveGameLoaded(URPGSaveGame* NewSaveGame)
{
    LoadInventory();
}

bool ARPGPlayerControllerBase::FillEmptySlotWithItem(URPGItem* NewItem)
{
    return true;
}

void ARPGPlayerControllerBase::NotifyInventoryItemChanged(bool bAdded, URPGItem* Item)
{

}

void ARPGPlayerControllerBase::NotifySlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item)
{

}

void ARPGPlayerControllerBase::NotifyInventoryLoaded()
{

}
