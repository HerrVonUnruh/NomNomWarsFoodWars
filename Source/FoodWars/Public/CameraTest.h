// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraTest.generated.h"

UCLASS()
class FOODWARS_API ACameraTest : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveCamera(float Value);
	void MoveCameraUp(float Value);

private: 
	UPROPERTY(EditAnywhere, Category = "Camera Movement")
	float rotationSpeed = 150.0F; 
	UPROPERTY(EditAnywhere, Category = "CameraMovement")
	FVector Center;  
	float deltaTime = 0; 
};
