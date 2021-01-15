// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyActionRPG.h"
#include "Engine/EngineTypes.h"
#include "RPGItemTypes.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    ItemType_Equip,
    ItemType_Task,
};

UENUM(BlueprintType)
enum class EItemEquipType : uint8
{
    ItemEquipType_None,
    ItemEquipType_Head,         // ͷ��װ��
    ItemEquipType_Body,         // �·�װ��
    ItemEquipType_Hand,         // �ֲ�װ��
    ItemEquipType_Weapon,       // ����װ��
    ItemEquipType_Leg,          // �Ȳ�װ��
    ItemEquipType_Foot,         // �Ų�װ��
};

USTRUCT(BlueprintType)
struct FItemGird
{
    GENERATED_USTRUCT_BODY()

    FItemGird() :Item(nullptr) {}

    UPROPERTY()
    uint32 Index;                   // ����

    UPROPERTY()
    class UItemBase* Item;          // ��ǰ����

    bool IsEmpty()
    {
        return Item == nullptr;
    }

    void Reset()
    {
        Item = nullptr;
    }
};

USTRUCT(BlueprintType)
struct FEquipGird
{
    GENERATED_USTRUCT_BODY()

    FEquipGird() :Item(nullptr) {}

    UPROPERTY(EditAnywhere)
    EItemEquipType Type;                   // ��ǰλ��װ������

    UPROPERTY()
    class UItemBase* Item;                 // ��ǰ����

    bool IsEmpty()
    {
        return Item == nullptr;
    }

    void Reset()
    {
        Item = nullptr;
    }
};

