// Fill out your copyright notice in the Description page of Project Settings.
#include "Skript_CameraController.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASkript_CameraController::ASkript_CameraController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASkript_CameraController::BeginPlay()
{
    Super::BeginPlay();
    SetActorLocation(center); 
    setPositionRef(); 
}

// Called every frame
void ASkript_CameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    deltaTime = DeltaTime; 
    lookAt(); 
 }

// Called to bind functionality to input
void ASkript_CameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("InputAxis_Right", this, &ASkript_CameraController::moveCameraHorizontal);
    PlayerInputComponent->BindAxis("InputAxis_CameraUp", this, &ASkript_CameraController::moveCameraUp);
}

void ASkript_CameraController::moveCameraHorizontal(float Value)
{
    if (Value != 0)
    {
        playerInput = true; 
        FRotator playerRot = GetActorRotation();
        playerRot.Yaw += rotationSpeed * Value * deltaTime * -1;
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);
        SetActorRotation(newRot);
    } else 
    {
        playerInput = false; 
    }
}

void ASkript_CameraController::lookAt()
{
	FRotator targetRotation = (center - GetActorLocation()).Rotation();
	FRotator NewRot = FMath::RInterpTo(GetActorRotation(), targetRotation, deltaTime, 1.3);
	SetActorRotation(NewRot);
}


void ASkript_CameraController::moveCameraUp(float Value)
{
    if (Value != 0)
    {
        playerInput = true; 
        FRotator playerRot = GetActorRotation();
        playerRot.Pitch += rotationSpeed * Value * deltaTime;
        playerRot.Pitch = FMath::ClampAngle(playerRot.Pitch, -45, 0);  // Hier den Clamp-Wert anwenden
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 1.3);
        SetActorRotation(newRot);
    }else 
    {
        playerInput = false; 
    }
}

void ASkript_CameraController::switchPlayerTurn()
{
    if(rotIndex < maxPlayer-1)
    {
        rotIndex++; 
    } else 
    {
        rotIndex = 0;
    }
        FVector camPos = MyCamera->GetComponentLocation(); 
        FVector targetPos = playerPositions[rotIndex]; 
        if(camPos != targetPos)
        {
            allowPlayerInput = false; 
            FVector dir = targetPos - camPos; 
            dir.Normalize(); 
            camPos += dir * rotationSpeed; 
            FVector newPos = FMath::VInterpTo(MyCamera->GetComponentLocation(), camPos,deltaTime, 1.3F); 
            MyCamera->SetWorldLocation(newPos); 

        } else 
        {
            allowPlayerInput = true; 
        }
}

void ASkript_CameraController::setCamera(UCameraComponent* cam)
{
    MyCamera = cam; 
}

void ASkript_CameraController::setPositionRef()
{
}
int ASkript_CameraController::getPlayerID()
{
    return rotIndex+1; 
}

void ASkript_CameraController::setMaxPlayerIndex(int value)
{
    maxPlayerIndex = value; 
}

void ASkript_CameraController::resetPlayerPosition()
{
    isOnPoint = false; 
 while(isOnPoint == false && playerInput == false)
 {
     FVector camPos = MyCamera->GetComponentLocation();
     FVector targetPos = playerPositions[rotIndex];
     if(FVector::Distance(camPos, targetPos) > 10)
     {           
         FVector dir = targetPos - camPos; 
         dir.Normalize(); 
         camPos += dir * rotationSpeed;
         FVector newPos = FMath::VInterpTo(MyCamera->GetComponentLocation(), camPos, deltaTime, 0.1F);
         MyCamera->SetWorldLocation(newPos);
     } else 
     {
         isOnPoint = true; 
     }
 }
}