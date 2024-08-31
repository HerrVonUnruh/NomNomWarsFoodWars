// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skript_WinManager.generated.h"

UCLASS()
class FOODWARS_API ASkript_WinManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkript_WinManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void setMaxWin(int value); 
	
	UFUNCTION(BlueprintCallable)
	int increaseWin(int PlayerID);
	
	UFUNCTION(BlueprintCallable)
	int getMaxWin(); 
	
	UFUNCTION(BlueprintCallable)
	int getPlayerWin(int playerId); 
	
	UFUNCTION(BlueprintCallable)
	void setPlayerCount(int playerCount);

public: 
	UPROPERTY(EditAnywhere)
	int32 maxWins = 2; 
	TArray<int> winCounter; 
	UPROPERTY(EditAnywhere)
	int playerCount = 3; 



};
