// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTest.h"


// Sets default values
ACameraTest::ACameraTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraTest::BeginPlay()
{
	Super::BeginPlay();
    SetActorLocation(Center); 
}

// Called every frame
void ACameraTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    deltaTime = DeltaTime; 
}

// Called to bind functionality to input
void ACameraTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("InputAxis_Right", this,&ACameraTest::MoveCamera);
	PlayerInputComponent->BindAxis("InputAxis_CameraUp", this, &ACameraTest::MoveCameraUp);
}

void ACameraTest::MoveCamera(float Value)
{
    if (Value != 0)
    {
        FRotator playerRot = GetActorRotation();
        playerRot.Yaw += rotationSpeed * Value * deltaTime * -1;
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);
        SetActorRotation(newRot);
    }
}

void ACameraTest::MoveCameraUp(float Value)
{
    if (Value != 0)
    {
        FRotator playerRot = GetActorRotation();
        playerRot.Pitch += rotationSpeed * Value * deltaTime;
        playerRot.Pitch = FMath::ClampAngle(playerRot.Pitch, -45, 0);  // Hier den Clamp-Wert anwenden
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);

        SetActorRotation(newRot);
    }

}