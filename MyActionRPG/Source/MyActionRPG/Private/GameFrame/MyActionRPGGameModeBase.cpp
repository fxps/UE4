// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionRPGGameModeBase.h"
#include "RPGPlayerControllerBase.h"
#include "RPGGameStateBase.h"

AMyActionRPGGameModeBase::AMyActionRPGGameModeBase()
{
    // ����GameState��PlayerController��ʹ�õ�UClass����
    //GameStateClass =
    GameStateClass = ARPGGameStateBase::StaticClass();
    PlayerControllerClass = ARPGPlayerControllerBase::StaticClass();
}
