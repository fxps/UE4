// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RPGType.h"
#include "GameFramework/Character.h"
#include "RPGAttributeSet.h"
#include "AbilitySystemInterface.h"
#include "RPGCharacterBase.generated.h"

UCLASS()
class MYACTIONRPG_API ARPGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacterBase();

    UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // ��ɫ�ȼ�

    // ����ϵͳʹ�õ����Լ�
    UPROPERTY()
    URPGAttributeSet* AttributeSet;

    // װ�����µĻص�
    FDelegateHandle InventoryUpdateHandle;
    FDelegateHandle InventoryLoadedHandle;
};
