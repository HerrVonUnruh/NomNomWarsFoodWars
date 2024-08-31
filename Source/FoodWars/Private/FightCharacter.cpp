// Fill out your copyright notice in the Description page of Project Settings.


#include "FightCharacter.h"

// Sets default values
AFightCharacter::AFightCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFightCharacter::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AFightCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFightCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("InputAxis_Right", this, &AFightCharacter::getMovementInput);
	PlayerInputComponent->BindAction("InputAction_Jump", IE_Pressed, this, &AFightCharacter::jumpPlayer); 
	PlayerInputComponent->BindAction("InputAction_Jump", IE_Released, this, &AFightCharacter::resetJumpVal);
	//PlayerInputComponent->BindAction("InputAction_Punch", IE_Pressed, this, &AFightCharacter::doFalconPunch);
	//PlayerInputComponent->BindAction("InputAction_Punch", IE_Released, this, &AFightCharacter::resetFalconPunch);
}

void AFightCharacter::getMovementInput(float Value)
{
	if (FMath::Abs(Value) > 0.0f)
	{
		viewDir = Value; 
		moveVector = body->GetActorLocation();
		FVector DeltaMove = body->GetActorRightVector() * Value;
		moveVector += DeltaMove * speed; 
		FRotator  newRotation;
		if (Value < 0)
		{
			dir = -1; 
		}
		else if (Value > 0)
		{
			dir = 1; 
		}
		body->SetActorLocation(moveVector);
	}
}


void AFightCharacter::jumpPlayer()
{
	if(!isJumping)
	{

		moveVector = body->GetActorLocation();
		isJumping = true; 
		FVector jumpVec = body->GetActorUpVector() * jumpForce;
		moveVector += jumpVec;
		body->SetActorLocation(moveVector);
	}
}

void AFightCharacter::resetJumpVal()
{
	isJumping = false;
}
int AFightCharacter::getMoveDir()
{
	return dir; 
}


/*void AFightCharacter::doFalconPunch()
{
	if (!isPunching)
	{
		int i = 0; 
		isPunching = true; 
		moveVector = body->GetActorLocation();
		while(i < 3)
		{
			FVector DeltaMove; 
			if(viewDir > 0)
			{
				 DeltaMove = body->GetActorRightVector() * 10;
			} else 
			{
				 DeltaMove = body->GetActorRightVector() * -10;
			}
			moveVector += DeltaMove * 10;
			body->SetActorLocation(moveVector); 
			i++; 
		}
	}
}

void AFightCharacter::resetFalconPunch()
{
	isPunching = false; 
}*/
