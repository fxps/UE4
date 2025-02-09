// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGItemTypes.h"
#include "ItemEquipComponent.generated.h"

class UItemBase;

// 装备格子
USTRUCT(BlueprintType)
struct FEquipGird
{
    GENERATED_USTRUCT_BODY()

    FEquipGird() :Item(nullptr) {}

    UPROPERTY(EditAnywhere)
    EItemEquipType Type;                   // 当前位置装备类型

    UPROPERTY()
    class UItemBase* Item;                 // 当前道具

    bool IsEmpty()
    {
        return Item == nullptr;
    }

    void Reset()
    {
        Item = nullptr;
    }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYACTIONRPG_API UItemEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemEquipComponent();
// 客户端向服务器发送消息
public:
    /** 向服务器发送装备道具消息*/
    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerEquipItem(UItemBase* Item);
public:
    /** 装备道具 */
    UFUNCTION(BlueprintCallable, Category = Equip)
    bool EquipItem(UItemBase* Item);

    /** 卸载道具*/
    UFUNCTION(BlueprintCallable, Category = Equip)
    bool RemoveItem(int32 Index);

    UFUNCTION(BlueprintCallable, Category = Equip)
    bool CanEquipItem(UItemBase* Item);

    /** 获取某个类型的装备Item指针*/
    UItemBase* FindItemByType(EItemEquipType Type);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:
    /** 装备格子的类型在蓝图中配置*/
    UPROPERTY(BlueprintReadOnly, EditAnywhere, ReplicatedUsing = OnRep_EquipArrayChange, Category = Equip)
    TArray<FEquipGird> EquipArray;

private:
    UFUNCTION()
    void OnRep_EquipArrayChange();

private:
    bool LoadItemActor(UItemBase* Item);

    bool DestoryItemActor(UItemBase* Item);
private:
    /**获取某个类型所有的装备栏序号*/
    typedef TArray<uint8> OutGirdArray;
    bool GetEquipGird(EItemEquipType Type, OutGirdArray& OutArrary);
};
