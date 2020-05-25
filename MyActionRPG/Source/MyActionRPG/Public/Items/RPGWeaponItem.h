// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/RPGItem.h"
#include "RPGWeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API URPGWeaponItem : public URPGItem
{
	GENERATED_BODY()
public:
    URPGWeaponItem()
    {
        ItemType = URPGAssetManager::WeaponItemType;
    }

    /** ����actor UCLASS����*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
    TSubclassOf<AActor> WeaponActor;

};
