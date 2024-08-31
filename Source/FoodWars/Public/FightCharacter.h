// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FightCharacter.generated.h"

UCLASS()
class FOODWARS_API AFightCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFightCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void getMovementInput(float Value); 
	void jumpPlayer();
	void resetJumpVal(); 
	//void doFalconPunch(); 
	//void resetFalconPunch(); 
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = "Damage")
	int getMoveDir(); 
private:
	float speed = 5.0F;

	float viewDir; 
	float jumpForce = 100.0F; 
	bool isJumping = false; 
	bool isPunching = false; 
	UPROPERTY(EditAnywhere)
	AActor* body;
	UPROPERTY(EditAnywhere)
	bool lookRight = true; 
    FVector moveVector; 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
	float dir = 1; 
};
