// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "RPGTask_PlayMontageWaitEvent.generated.h"

class URPGAbilitySystemComponent;

/** ����һ����̫��ص�ʹ�õĶಥ���� */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRPGPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);
/**
 * 
 */
UCLASS()
class MYACTIONRPG_API URPGTask_PlayMontageWaitEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
   URPGTask_PlayMontageWaitEvent(const FObjectInitializer& ObjectInitializer);
   virtual void Activate() override;
   virtual void ExternalCancel() override;
   virtual FString GetDebugString() const override;
   virtual void OnDestroy(bool bAbilityEnded) override;

    /** ��̫�沥�Ž����Ļص�����*/
    UPROPERTY(BlueprintAssignable)
    FRPGPlayMontageAndWaitForEventDelegate OnCompleted;

    /** ��̫�濪ʼ�ڳ��Ļص�����*/
    UPROPERTY(BlueprintAssignable)
    FRPGPlayMontageAndWaitForEventDelegate OnBlendOut;

    /** ��̫�汻��ϵĻص�����*/
    UPROPERTY(BlueprintAssignable)
    FRPGPlayMontageAndWaitForEventDelegate OnInterrupted;

    /** ����������������ȡ���Ļص�����*/
    UPROPERTY(BlueprintAssignable)
    FRPGPlayMontageAndWaitForEventDelegate OnCancelled;

    /** ����Gameplay�¼��Ļص�����*/
    UPROPERTY(BlueprintAssignable)
    FRPGPlayMontageAndWaitForEventDelegate EventReceived;

    /** �������񹤳�����*/
    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
    static URPGTask_PlayMontageWaitEvent* PlayMontageAndWaitForEvent(
        UGameplayAbility* OwningAbility,
        FName TaskInstanceName,
        UAnimMontage* MontageToPlay,
        FGameplayTagContainer EventTags,
        float Rate = 1.f,
        FName StartSection = NAME_None,
        bool bStopWhenAbilityEnds = true,
        float AnimRootMotionTranslationScale = 1.f);

private:
    /** ��ǰ���ŵ���̫��*/
    UPROPERTY()
    UAnimMontage* MontageToPlay;
   
    /** ��Ӧgameplay�¼���tags�б�*/
    UPROPERTY()
    FGameplayTagContainer EventTags;

    /** Playback rate*/
    UPROPERTY()
    float Rate;

    /** ��̫�濪ʼ���ŵķֶ�*/
    UPROPERTY()
    FName StartSection;

    UPROPERTY()
    float AnimRootMotionTranslationScale;

    /** ���ܽ����Ƿ��ж���̫��*/
    UPROPERTY()
    bool bStopWhenAbilityEnds;

    /** ��ȡ�������*/
    URPGAbilitySystemComponent* GetTargetASC();

    /** ֹͣ��̫�涯������*/
    bool StopPlayingMontage();

    /** ��ȡAnimInstance*/
    UAnimInstance* GetAnimInstance();

    void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
    void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);
    void OnAbilityCancelled();
    /** ������*/
    FOnMontageBlendingOutStarted BlendingOutDelegate;
    FOnMontageEnded MontageEndedDelegate;
    FDelegateHandle CancelledHandle;
    FDelegateHandle EventHandle;
};
