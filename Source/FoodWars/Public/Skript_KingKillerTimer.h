// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skript_KingKillerTimer.generated.h"

UCLASS()
class FOODWARS_API ASkript_KingKillerTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkript_KingKillerTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "timer")
	void timer(float deltaTime); 
	
	UFUNCTION(BlueprintCallable, Category = "timer")
	float getTimerValue();
private:
	float timeLeft = 20; 
	TArray<int32> winCounter[5]; 
};
