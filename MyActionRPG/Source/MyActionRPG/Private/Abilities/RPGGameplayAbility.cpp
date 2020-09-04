// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility.h"
#include "RPGCharacterBase.h"
#include "Abilities/RPGAbilitySystemComponent.h"

URPGGameplayAbility::URPGGameplayAbility()
{

}

TArray<FActiveGameplayEffectHandle> URPGGameplayAbility::ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel /*= -1*/)
{
    FRPGGameplayEffectContainerSpec Spec = MakeEffectContainerSpec(ContainerTag, EventData, OverrideGameplayLevel);
    return ApplyEffectContainerSpec(Spec);
}

FRPGGameplayEffectContainerSpec URPGGameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel /*= -1*/)
{
    FRPGGameplayEffectContainer* FoundContainer = EffectContainerMap.Find(ContainerTag);
    if (FoundContainer)
    {
        return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData, OverrideGameplayLevel);
    }

    return FRPGGameplayEffectContainerSpec();
}

FRPGGameplayEffectContainerSpec URPGGameplayAbility::MakeEffectContainerSpecFromContainer(const FRPGGameplayEffectContainer& Contanier, const FGameplayEventData& EventData, int32 OverrideGameplayLevel /*= -1*/)
{
    FRPGGameplayEffectContainerSpec ReturnSpec;
    // ��ȡ����ϵͳ�������
    AActor* OwningActor = GetOwningActorFromActorInfo();
    ARPGCharacterBase* OwningCharacter = Cast<ARPGCharacterBase>(OwningActor);
    URPGAbilitySystemComponent* OwningASC = URPGAbilitySystemComponent::GetAbilitySystemComponentFromActor(OwningActor);
    if (OwningASC)
    {
        // ���������һ��Ŀ�����ͣ�ִ�������߼���ʵ��Ŀ������ں��������
        if (Contanier.TargetType.Get())
        {
            TArray<FHitResult> HitResults;          // �����ײ����ȡ����Ŀ��
            TArray<AActor*> TargetActors;           // ��Χ���ܻ�ȡ����Ŀ�꣬������

            // ͨ�����õ�TargetType�����͵�CDO��AddTargets������ȡHitResults��TargetActors
            // ͨ�������EventData����ȷ��Ŀ��Actor
            const URPGTargetType* TargetTypeCDO = Contanier.TargetType.GetDefaultObject();
            AActor* AvatarActor = GetAvatarActorFromActorInfo();
            TargetTypeCDO->GetTargets(OwningCharacter, AvatarActor, EventData, HitResults, TargetActors);
            ReturnSpec.AddTargets(HitResults, TargetActors);
        }
    }
    return ReturnSpec;
}

TArray<FActiveGameplayEffectHandle> URPGGameplayAbility::ApplyEffectContainerSpec(const FRPGGameplayEffectContainerSpec& ContainerSpec)
{
    TArray<FActiveGameplayEffectHandle> AllActiveEffects;
    for (const FGameplayEffectSpecHandle& SpecHandle: ContainerSpec.TargetGameplayEffectSpecs)
    {
        AllActiveEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TagetData));
    }

    return AllActiveEffects;
}
