// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionRPGGameModeBase.h"
#include "RPGPlayerControllerBase.h"
#include "RPGGameStateBase.h"

AMyActionRPGGameModeBase::AMyActionRPGGameModeBase()
{
    // 设置GameState、PlayerController所使用的UClass对象
    //GameStateClass =
    GameStateClass = ARPGGameStateBase::StaticClass();
    PlayerControllerClass = ARPGPlayerControllerBase::StaticClass();
}
