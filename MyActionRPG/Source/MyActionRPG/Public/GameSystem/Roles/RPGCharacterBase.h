// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RPGType.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/RPGGameplayAbility.h"
#include "GameplayAbilitySpec.h"
#include "RPGInventoryInterface.h"
#include "RoleAssetBase.h"
#include "RPGCharacterBase.generated.h"

class URPGAbilitySystemComponent;
class URPGAttributeSet;

UCLASS()
class MYACTIONRPG_API ARPGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacterBase();
    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** Returns current health, will be 0 if dead */
    UFUNCTION(BlueprintCallable)
    virtual float GetHealth() const;

    /** Returns maximum health, health will never be greater than this */
    UFUNCTION(BlueprintCallable)
    virtual float GetMaxHealth() const;

    /** Returns current mana */
    UFUNCTION(BlueprintCallable)
    virtual float GetMana() const;

    /** Returns maximum mana, mana will never be greater than this */
    UFUNCTION(BlueprintCallable)
    virtual float GetMaxMana() const;

    /** Returns current movement speed */
    UFUNCTION(BlueprintCallable)
    virtual float GetMoveSpeed() const;

    /** ��ȡ��ɫ�ȼ�*/
    UFUNCTION(BlueprintCallable)
    virtual int32 GetCharacterLevel() const;

    UFUNCTION(BlueprintCallable)
    virtual bool SetCharacterLevel(int32 NewLevel);

    /** �ͷ�һ��װ���õļ���*/
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    bool ActivateAbilitiesWithItemSlot(FRPGItemSlot ItemSlot, bool bAllowRemoteActivation = true);

    /** ��ȡװ���õļ����б�*/
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void GetActiveAbilitiesWithItemSlot(FRPGItemSlot ItemSlot, TArray<URPGGameplayAbility*>& ActiveAbilities);

    /** ����tag�����*/
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    bool ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation = true);

    /** ����tag��ȡ��ǰ����ļ���*/
    UFUNCTION(BlueprintCallable, Category = "Abilities")
    void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<URPGGameplayAbility*>& ActiveAbilities);

    void SetRoleAsset(URoleAssetBase* ptr);

    template<typename T>
    T* GetRoleAsset()
    {
        if (!RoleAssetPtr.IsValid())
        {
            return nullptr;
        }

        return Cast<T>(RoleAssetPtr.Get());
    }
protected:
    // װ�����л����ߴ����Ļص�
    void OnItemSlotChanged(FRPGItemSlot ItemSlot, URPGItem* Item);
    void RefreshSlottedGameplayAbilities();

    // �����Ҽ����б�
    void AddStartupGameplayAbilities();

    // ���װ�����еļ���
    void AddSlottedGameplayAbilities();
    void FillSlottedAbilitySpecs(TMap<FRPGItemSlot, FGameplayAbilitySpec>& SlottedAbilitySpecs);

    UFUNCTION(BlueprintImplementableEvent)
    void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARPGCharacterBase* InstigatorCharacter, AActor* DamageCauser);

    UFUNCTION(BlueprintImplementableEvent)
    void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

    UFUNCTION(BlueprintImplementableEvent)
    void OnManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

    UFUNCTION(BlueprintImplementableEvent)
    void OnMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

    virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ARPGCharacterBase* InstigatorCharacter, AActor* DamageCauser);
    virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
    virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
    virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

    friend URPGAttributeSet;
    
protected:
    /** �������*/
    UPROPERTY()
    URPGAbilitySystemComponent* AbilitySystemComponent;

    // ��ɫ�ȼ�
    UPROPERTY(EditAnywhere, Replicated, Category = Abilities)
    int32 CharacterLevel;

    /** ����ϵͳʹ�õ����Լ�,���Ϊӵ�м���ϵͳ�����Actor�Ӷ������Զ�ע�������ϵͳ*/
    UPROPERTY()
    URPGAttributeSet* AttributeSet;

    /** ��Ҵ���ʱ������������ҵļ������ã�����ͨ��tag��event�ȼ���*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    TArray<TSubclassOf<URPGGameplayAbility>>    GameplayAbilities;

    /** ����װ������Ӧ�ļ������ã���װ������*/
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    TMap<FRPGItemSlot, TSubclassOf<URPGGameplayAbility>> DefaultSlottedAbilities;

    /** װ������װ���ļ��ܶ����б�*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
    TMap<FRPGItemSlot, FGameplayAbilitySpecHandle> SlottedAbilities;

    /** ��ɫ����ʱ��ӱ�������*/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
    TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

    // װ�����µĻص����������
    FDelegateHandle InventoryUpdateHandle;
    FDelegateHandle InventoryLoadedHandle;

    /**��ȡ��ɫ��ǰװ�������ݵĽӿ� */
    UPROPERTY()
    TScriptInterface<IRPGInventoryInterface> InventorySource;

    UPROPERTY()
    int32 bAbilitiesInitialized;

    // ��ǰactor��Ӧ������
    TWeakObjectPtr<URoleAssetBase> RoleAssetPtr;
};
