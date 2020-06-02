// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerControllerBase.h"
#include "RPGGameInstanceBase.h"
#include "RPGAssetManager.h"
#include "RPGSaveGame.h"
#include "RPGItem.h"

void ARPGPlayerControllerBase::BeginPlay()
{
    // �������е���
    LoadInventory();

    Super::BeginPlay();
}

bool ARPGPlayerControllerBase::AddInventoryItem(URPGItem* NewItem, int32 ItemCount /*= 1*/, int32 ItemLevel /*= 1*/, bool bAutoSlot /*= true*/)
{
    bool bChanged = false;
    if (!NewItem)
    {
        UE_LOG(LogActionRPG, Warning, TEXT("AddInventoryItem: Failed trying to add null item!"));
        return false;
    }

    if (ItemCount <= 0 || ItemLevel <= 0)
    {
        UE_LOG(LogActionRPG, Warning, TEXT("AddInventoryItem: Failed trying to add item %s with negative count or level!"), *NewItem->GetName());
        return false;
    }

    //��ȡ��ǰItem����
    FRPGItemData OldData;
    GetInventoryItemData(NewItem, OldData);

    // ���������ݲ��������ݽ��бȽϲ���������
    FRPGItemData NewData = OldData;
    NewData.UpdateItemData(FRPGItemData(ItemCount, ItemLevel), NewItem->MaxCount, NewItem->MaxLevel);
    if (NewData != OldData)
    {
        InventoryData.Add(NewItem, NewData);
        NotifyInventoryItemChanged(true, NewItem);
        bChanged = true;
    }

    // �����Զ��Ž����
    if(bAutoSlot)
    {
        bChanged |= FillEmptySlotWithItem(NewItem);
    }

    // �����б䶯��Ҫ���б���
    if (bChanged)
    {
        SaveInventory();
        return true;
    }

    return false;
}

bool ARPGPlayerControllerBase::GetInventoryItemData(URPGItem* Item, FRPGItemData& ItemData) const
{
    const FRPGItemData* FoundItem = InventoryData.Find(Item);

    if (FoundItem)
    {
        ItemData = *FoundItem;
        return true;
    }
    ItemData = FRPGItemData(0, 0);
    return false;
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

    // ����SaveGame.InventoryData�������InventoryData��SlottedItems
    URPGSaveGame* CurrentSaveGame = GameInstance->GetCurrentSaveGame();
    URPGAssetManager& AssetManager = URPGAssetManager::Get();
    if (CurrentSaveGame)
    {
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

        // ����װ���������֪ͨ
        NotifyInventoryLoaded();
        return true;
    }
    
    // ��Ȼ����ʧ�ܣ�������Ϊ���õ�װ�����Ի���Ҫ����֪ͨ
    NotifyInventoryLoaded();
    return false;
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
    // ��һ����Ӧ��Դ�����͵ĿյĲ۲������Item
    FPrimaryAssetType NewItemType = NewItem->GetPrimaryAssetId().PrimaryAssetType;

    // �ҵ��ղ۵�KEY
    FRPGItemSlot EmptySlot;
    for (TPair<FRPGItemSlot, URPGItem*>& Pair : SlottedItems)
    {
        // ������ͬ
        if (Pair.Key.ItemType == NewItemType)
        {
            // Item�Ѿ����ڣ�������
            if (Pair.Value == NewItem)
            {
                return false;
            }
            else if (Pair.Value == nullptr && (!EmptySlot.IsValid()) || EmptySlot.SlotNumber > Pair.Key.SlotNumber)
            {
                EmptySlot = Pair.Key;
            }
        }
    }

    if (EmptySlot.IsValid())
    {
        SlottedItems[EmptySlot] = NewItem;
        NotifySlottedItemChanged(EmptySlot, NewItem);
        return true;
    }

    return false;
}

void ARPGPlayerControllerBase::NotifyInventoryItemChanged(bool bAdded, URPGItem* Item)
{
    
}

void ARPGPlayerControllerBase::NotifySlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* Item)
{
    OnSlottedItemChangedNative.Broadcast(ItemSlot, Item);
    OnSlottedItemChanged.Broadcast(ItemSlot, Item);

    // ִ����ͼ�ص�����
    SlottedItemChanged(ItemSlot, Item);
}

void ARPGPlayerControllerBase::NotifyInventoryLoaded()
{

}
