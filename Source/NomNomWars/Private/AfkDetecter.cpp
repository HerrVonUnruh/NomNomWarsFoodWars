// Fill out your copyright notice in the Description page of Project Settings.


#include "AfkDetecter.h"

// Sets default values
AAfkDetecter::AAfkDetecter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAfkDetecter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAfkDetecter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(recievedInput==false)
	{
		timeSpendAfk+=DeltaTime; 
		if(timeSpendAfk >= 20.0F)
		{
 			UE_LOG(LogTemp, Warning, TEXT("Input detected!"));
		}
	} else 
	{
		timeSpendAfk=0; 
	}
}

void AAfkDetecter::IncreaseAFkTimer(float deltaTime)
{
	if(recievedInput==false)
	{
		timeSpendAfk += deltaTime; 
		if(timeSpendAfk >= 10)
		{
 			//UE_LOG(LogTemp, Warning, TEXT("No  input detected!"));
			timeSpendAfk=0; 
		}
	}else 
	{
		timeSpendAfk=0.0F; 

	}
}
void AAfkDetecter::setRevievedInput(bool val)
{
	recievedInput=val; 
}
// Called to bind functionality to input
void AAfkDetecter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 
}