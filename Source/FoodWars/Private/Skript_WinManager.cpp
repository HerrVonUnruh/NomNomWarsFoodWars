// Fill out your copyright notice in the Description page of Project Settings.


#include "Skript_WinManager.h"

// Sets default values
ASkript_WinManager::ASkript_WinManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkript_WinManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkript_WinManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkript_WinManager::setPlayerCount(int count)
{
	playerCount = count; 
	winCounter.Init(0, playerCount); 
}
int ASkript_WinManager::getPlayerWin(int playerID)
{
	return winCounter[playerID]; 
}
int ASkript_WinManager::getMaxWin()
{
	return maxWins; 
}

int ASkript_WinManager::increaseWin(int PlayerID)
{
	winCounter[PlayerID]+=1;
	return winCounter[PlayerID];
}
void  ASkript_WinManager::setMaxWin(int value)
{
	maxWins = value; 
}


