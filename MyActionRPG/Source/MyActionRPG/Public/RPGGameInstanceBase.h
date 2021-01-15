// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGType.h"
#include "Engine/GameInstance.h"
#include "RPGCharacterBase.h"
#include "ControlRole.h"
#include "RPGGameInstanceBase.generated.h"

/**
 * ���ɻ��ڴ������ͼ������ͼ�������ص��߼�
 * ��Ҫ������Ϸ���ݵı��棬����Ϸ��Ӧ״̬���¼�����
 */

USTRUCT(BlueprintType)
struct FGameDefaultData
{
    GENERATED_USTRUCT_BODY()

    /**�����Ĭ�ϵ�װ�������б�*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<FPrimaryAssetId, FRPGItemData> DefaultInventory;

    /**ÿ�����͵Ĳ������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<FPrimaryAssetType, int32> ItemSlotsPerType;
};

//USTRUCT(BlueprintType)
//struct FSaveGame
//{
//    GENERATED_USTRUCT_BODY()
//};

UCLASS()
class MYACTIONRPG_API URPGGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
    URPGGameInstanceBase();

    virtual void Init() override;
    
    // �ؿ�������ɵĻص�
    virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

    /**��������Ĭ�ϵ���*/
    UFUNCTION(BlueprintCallable, Category = Inventory)
    void AddDefaultInventory(URPGSaveGame* SaveGame, bool bRemoveExtra);

    /**���ر������ݵ�ԭ��ί��*/
    FOnSaveGameLoadedNative OnSaveGameLoadedNative;

    /**���ر���������ɺ���õ�ί��*/
    UPROPERTY(BlueprintAssignable, Category = Inventory)
    FOnSaveGameLoaded OnSaveGameLoaded;

    /**���ر������ݵĶ���ָ��*/
    UFUNCTION(BlueprintCallable, Category = Save)
    URPGSaveGame* GetCurrentSaveGame();

   /**�Ƿ����浵����*/
    UFUNCTION(BlueprintCallable, Category = Save)
    void SetSavingEnabled(bool bEnabled);

    /**������浵���ݺ�Ļص� */
    UFUNCTION(BlueprintCallable, Category = Save)
    bool HandleSaveGameLoaded(USaveGame* SaveGameObject);

    /**��ȡ�������ݵ�slot��index */
    UFUNCTION(BlueprintCallable, Category = Save)
    void GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const;

    /**ִ�����ݱ��� */
    UFUNCTION(BlueprintCallable, Category = Save)
    bool WriteSaveGame();

    /** The slot name used for saving */
    UPROPERTY(BlueprintReadWrite, Category = Save)
    FString SaveSlot;

    /** The platform-specific user index */
    UPROPERTY(BlueprintReadWrite, Category = Save)
    int32 SaveUserIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    FGameDefaultData DefaultData;

#pragma region rolelist
public:
    UControlRole* GetAssetRole(const FName& AssetName);
    
    UPROPERTY()
    class  ARPGPlayerSeats* PlayerSeats;


protected:
    // ��ɫ�б�����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Characters)
    TMap<FName, UControlRole*> DefaultRoles;

    /**��ʼ����ɫ�б�*/
    void StartLoadRoleList();

    FStreamableDelegate ControlRoleLoadDelegate;
    void ControlRoleLoadComplated();

   
#pragma endregion rolelist

protected:
    UPROPERTY()
    URPGSaveGame* CurrentSaveGame;

    UPROPERTY()
    bool bSavingEnabled;

    /** ��ǰ�Ƿ��ڱ������ݵĹ�����*/
    UPROPERTY()
    bool bCurrentlySaving;

    /**�ڱ������ݵĹ����������������ݱ�������*/
    UPROPERTY()
    bool bPendingSaveRequested;

    /**�첽���淢��ʱ��ִ��*/
    virtual void HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess);

    void LoadCommonDataTableFinish();
};
