// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstanceBase.h"

URPGGameInstanceBase::URPGGameInstanceBase()
{

}

URPGSaveGame* URPGGameInstanceBase::GetCurrentSaveGame()
{
    return CurrentSaveGame;
}
