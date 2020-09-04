// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyActionRPG.h"
#include "RPGTargetType.h"
#include "GameplayAbilityTargetTypes.h"
#include "Engine/EngineTypes.h"
#include "RPGAbilityTypes.generated.h"

/** 
*   gameplay effect class�б�a tag, and targeting info
*  �����������ͼ��assets�б���̬����(ָ�����ͺ�Ĭ��ֵ)Ȼ��������ʱ��ת����Specs��ִ��
*/
USTRUCT(BlueprintType)
struct FRPGGameplayEffectContainer
{
    GENERATED_BODY()

public:
    FRPGGameplayEffectContainer() {}

    /**�趨����Ŀ������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
    TSubclassOf<URPGTargetType> TargetType;

    /** Ӧ���ڵ�ǰĿ��ļ���Ч������ */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
    TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
   
};

/** ��ӦFRPGGameplayEffectContainer��������ִ�м���İ汾 */
USTRUCT(BlueprintType)
struct FRPGGameplayEffectContainerSpec
{
    GENERATED_BODY()
public:
    FRPGGameplayEffectContainerSpec() {}

    /** ����ϵͳ�ڲ�Ŀ������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
    FGameplayAbilityTargetDataHandle TagetData;

    /** Ӧ���ڵ�ǰĿ��ļ���Ч�������б� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
    TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

    /** �Ƿ�����Ч��effect specs*/
    bool HasValidEffects() const;

    /** �Ƿ�����Ч��targets */
    bool HasValidTargets() const;

    /** ����Ŀ������*/
    void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};