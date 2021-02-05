// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyActionRPG.h"
#include "Engine/EngineTypes.h"
#include "RPGItemTypes.generated.h"

// ��������
UENUM(BlueprintType)
enum class EItemType : uint8
{
    ItemType_Equip,
    ItemType_Task,
};

// װ������
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

// ���������
UENUM(BlueprintType)
enum class EShortcutType: uint8
{
    ShortcutGirdType_None,
    ShortcutGirdType_Item,
    ShortcutGirdType_Skill,
    ShortcutGirdType_WeaponSkill
};

