// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/AssetManager.h"
#include "RPGAssetManager.generated.h"

class URPGItem;

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API URPGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
    virtual void StartInitialLoading() override;

    static const FPrimaryAssetType PotionItemType;
    static const FPrimaryAssetType	SkillItemType;
    static const FPrimaryAssetType	TokenItemType;
    static const FPrimaryAssetType	WeaponItemType;

    /** ��ȡ��ǰAssetManager���� */
    static URPGAssetManager& Get();

    /** ���ص��ߣ����ص��߶���ָ�� */
    URPGItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);

};
