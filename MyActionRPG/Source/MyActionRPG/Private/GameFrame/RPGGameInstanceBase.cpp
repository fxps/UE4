// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstanceBase.h"
#include "RPGSaveGame.h"

URPGGameInstanceBase::URPGGameInstanceBase()
{

}

URPGSaveGame* URPGGameInstanceBase::GetCurrentSaveGame()
{
    return CurrentSaveGame;
}

void URPGGameInstanceBase::AddDefaultInventory(URPGSaveGame* SaveGame, bool bRemoveExtra)
{
    if (bRemoveExtra)
    {
        SaveGame->InventoryData.Reset();
    }

    // ��DefaultInventory���ݼ��ص�SaveGame.InventoryData��
    for (TPair<FPrimaryAssetId, FRPGItemData>& Pair : DefaultInventory)
    {
        if (!SaveGame->InventoryData.Contains(Pair.Key))
        {
            SaveGame->InventoryData.Add(Pair.Key, Pair.Value);
        }
    }
}
