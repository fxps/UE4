// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "RPGAssetManager.h"
#include "RPGItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class MYACTIONRPG_API URPGItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	URPGItem()
	{}

    /** �������� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType	ItemType;

    /** ������ */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemName;

    /** �������� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemDescription;

    /** ������ʾ��icon  */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FSlateBrush ItemIcon;
};
