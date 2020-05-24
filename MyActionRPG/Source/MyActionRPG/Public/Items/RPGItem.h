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

    /** ����һ�α�װ�����������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
    int32 MaxCount;

    /** ��ǰ�����Ƿ�������Ʒ*/
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = Max)
    bool IsConsumble() const;

    /** ���ߵ���ߵȼ��� <=0��ζ��������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
    int32 MaxLevel;

    /** ��ǰ���߰󶨵ļ���*/
    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    //TSubclassOf<U>
    /** ���ܵȼ���<=0��ζ�Ž�ɫ�ȼ�*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    int32 AbilityLevel;

    /** ��ȡ������ID*/
    UFUNCTION(BlueprintCallable, Category = Item)
    FString GetIdentifierString() const;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
