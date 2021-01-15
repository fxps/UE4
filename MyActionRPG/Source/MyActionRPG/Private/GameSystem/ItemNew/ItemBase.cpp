// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

UItemBase::UItemBase():
ItemConfig(nullptr)
{
    
}

bool UItemBase::IsSupportedForNetworking() const
{
    return true;
}

void UItemBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UItemBase, ItemID);
    DOREPLIFETIME(UItemBase, ItemLevel);
}

void UItemBase::OnRep_ItemID()
{
    // �ͻ��˻�ȡFRPGItemDataTableRow��ָ�벢�����ţ������ѯ
    if (UTableAssetCommon::Get() == nullptr)
    {
        return;
    }

    ItemConfig = UTableAssetCommon::Get()->TableItem->FindRow<FRPGItemDataTableRow>(ItemID, TEXT(""));
}
