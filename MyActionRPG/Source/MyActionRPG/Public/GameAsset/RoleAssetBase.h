#pragma once

#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "RPGAssetManager.h"
#include "RoleAssetBase.generated.h"

UCLASS(Abstract, BlueprintType)
class MYACTIONRPG_API URoleAssetBase : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    URoleAssetBase(){}

    /** ��ɫ���� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Role)
    FPrimaryAssetType	RoleType;

    /**  ��ɫ�� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Role)
    FText Name;

    /**  ������ʾ��icon */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Role)
    FSlateBrush Icon;

    /**  ���ö�Ӧ��actor */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Role)
    TSubclassOf<AActor> RoleActor;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};