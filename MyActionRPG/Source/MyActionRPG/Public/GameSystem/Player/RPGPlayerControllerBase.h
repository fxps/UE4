// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "RPGPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class MYACTIONRPG_API ARPGPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
    ARPGPlayerControllerBase();

    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;



// ��������ͻ��˷��͵�RPC
public:
    /** ��¼�ɹ�֪ͨ�ͻ���*/
    UFUNCTION(Client, Reliable)
    void LoginSucceed();

// �ͻ����������������Ϣ
public:
    UFUNCTION(Server, Reliable, BlueprintCallable)
    void SelectRole(const FName& RoleName);
};
