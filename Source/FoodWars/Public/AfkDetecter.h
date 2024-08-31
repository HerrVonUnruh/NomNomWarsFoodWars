// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AfkDetecter.generated.h"

UCLASS()
class FOODWARS_API AAfkDetecter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAfkDetecter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void IncreaseAFkTimer(float deltaTime); 

	void setRevievedInput(bool val);
	bool getRecievedInput(){return recievedInput; }; 

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
bool recievedInput=false; 
float timeSpendAfk=0; 
};
