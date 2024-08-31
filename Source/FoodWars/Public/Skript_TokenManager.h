// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skript_TokenManager.generated.h"

UCLASS()
class FOODWARS_API ASkript_TokenManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkript_TokenManager();
	UFUNCTION(BlueprintCallable)
	void addTokens(int tokenAmount, int playerCount); 
	UFUNCTION(BlueprintCallable)
	void setTokens(int tokenValue, int playerID);
	UFUNCTION(BlueprintCallable)
	int getTokens(int playerID); 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private: 
	TArray<int> playerTokens; 
};
