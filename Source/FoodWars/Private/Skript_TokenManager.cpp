// Fill out your copyright notice in the Description page of Project Settings.


#include "Skript_TokenManager.h"

// Sets default values
ASkript_TokenManager::ASkript_TokenManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkript_TokenManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkript_TokenManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkript_TokenManager::addTokens(int tokenAmount, int playerCount) 
{
	playerTokens.Init(tokenAmount, playerCount); 
}

void ASkript_TokenManager::setTokens(int tokenValue, int playerID)
{
	playerTokens[playerID] = tokenValue; 
}

int ASkript_TokenManager::getTokens(int playerID) 
{
	return playerTokens[playerID];
}

