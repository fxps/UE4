// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActionRPG.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
    URPGAttributeSet();

    /**��ɫHP����*/
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)

    // MaxHealth
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth)
protected:
    UFUNCTION()
    virtual void OnRep_Health();

    UFUNCTION()
    virtual void OnRep_MaxHealth();

};
