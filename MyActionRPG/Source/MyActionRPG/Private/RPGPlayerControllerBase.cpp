// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerControllerBase.h"

void ARPGPlayerControllerBase::BeginPlay()
{
    // �������е���
    LoadInventory();

    Super::BeginPlay();
}

bool ARPGPlayerControllerBase::LoadInventory()
{
    return true;
}
