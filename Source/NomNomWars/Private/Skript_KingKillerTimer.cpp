// Fill out your copyright notice in the Description page of Project Settings.


#include "Skript_KingKillerTimer.h"

// Sets default values
ASkript_KingKillerTimer::ASkript_KingKillerTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkript_KingKillerTimer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkript_KingKillerTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkript_KingKillerTimer::timer(float deltaTime)
{
	timeLeft -= deltaTime;
}

float ASkript_KingKillerTimer::getTimerValue()
{
	return timeLeft;
}