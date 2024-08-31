// Fill out your copyright notice in the Description page of Project Settings.


#include "Skript_FPSCharachter.h"

// Sets default values
ASkript_FPSCharachter::ASkript_FPSCharachter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkript_FPSCharachter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkript_FPSCharachter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkript_FPSCharachter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	getPlayerMovementInput(PlayerInputComponent);
	getPlayerCameraInput(PlayerInputComponent); 
}

//input Handeling 
void ASkript_FPSCharachter::getPlayerMovementInput(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("InputAxis_Forward", this, &ASkript_FPSCharachter::moveForward);
	PlayerInputComponent->BindAxis("InputAxis_Right", this, &ASkript_FPSCharachter::moveRight);
	PlayerInputComponent->BindAction("InputAction_Jump", IE_Pressed, this, &ASkript_FPSCharachter::jump);
	PlayerInputComponent->BindAction("InputAction_Jump", IE_Released, this, &ASkript_FPSCharachter::stopJumping);
}

void ASkript_FPSCharachter::getPlayerCameraInput(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("InputAxis_MouseLookUp", this, &ASkript_FPSCharachter::rotateCameraUp);
	PlayerInputComponent->BindAxis("InputAxis_MouseLookRight", this, &ASkript_FPSCharachter::rotateRight);
}

//Player Movement
void ASkript_FPSCharachter::moveForward(float value)
{
	if (FMath::Abs(value) > 0.0f && canDoStuff)
	{
		moveVector = GetActorLocation();
		FVector deltaMove = GetActorForwardVector() * value;
		moveVector += deltaMove * speed;
		SetActorLocation(moveVector);
	}
}

void ASkript_FPSCharachter::moveRight(float value)
{
	if (FMath::Abs(value) > 0.0f && canDoStuff)
	{
		moveVector = GetActorLocation();
		FVector deltaMove = GetActorRightVector() * value;
		moveVector += deltaMove * speed;
		SetActorLocation(moveVector);
	}
}

void ASkript_FPSCharachter::jump()
{
	if (!isJumping && canDoStuff)
	{
		moveVector = GetActorLocation();
		isJumping = true;
		FVector jumpVec = GetActorUpVector() * jumpForce;
		moveVector += jumpVec;
		SetActorLocation(moveVector);
	}
}

void ASkript_FPSCharachter::stopJumping()
{
	isJumping = false;
}

//Mouse Look 
void ASkript_FPSCharachter::rotateCameraUp(float value)
{
	if (FMath::Abs(value) > 0.0f && canDoStuff)
	{
		FRotator cameraRotation = camera->GetRelativeRotation();
		if (cameraRotation.Pitch < 90 && value > 0 || cameraRotation.Pitch > -90 && value < 0)
		{
			cameraRotation.Pitch +=  value;
			camera->SetRelativeRotation(cameraRotation);
		}
	} 
}

void ASkript_FPSCharachter::rotateRight(float value)
{
	if (FMath::Abs(value) > 0.0f && canDoStuff)
	{
		FRotator playerRotation = GetActorRotation();
		playerRotation.Yaw += value;
		SetActorRotation(playerRotation);
	}
}



//Blueprint functions
void ASkript_FPSCharachter::setCamera(UCameraComponent* cam)
{
	camera = cam; 
}



void ASkript_FPSCharachter::shoot(TSubclassOf<AActor> bulletClass, FVector barrel, bool debugBool, FRotator barrelRotation)
{
	if(Ammo > 0 && canDoStuff)
	{
		Ammo--; 
		bullet = GetWorld()->SpawnActor<AActor>(bulletClass, barrel, barrelRotation);
		UStaticMeshComponent* BulletSphereComponent = getButtetSphereComponent();

		if (BulletSphereComponent)
		{
			spawnBullet(BulletSphereComponent);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NO SPHERE!!!!! WARNING ACHTUNG!!!!!NO SPHERE %s"));
		}
	}
}

UStaticMeshComponent* ASkript_FPSCharachter::getButtetSphereComponent()
{
	UStaticMeshComponent* BulletSphereComponent = nullptr;
	TArray<UStaticMeshComponent*> MeshComponents;
	bullet->GetComponents<UStaticMeshComponent>(MeshComponents);

	if (MeshComponents.Num() > 0)
	{
		BulletSphereComponent = MeshComponents[0];
		return BulletSphereComponent; 
	} else
	{
		return NULL; 
	}
}

void ASkript_FPSCharachter::spawnBullet(UStaticMeshComponent* BulletSphereComponent)
{
	FVector ImpulseDirection = BulletSphereComponent->GetUpVector();
	float ImpulseStrength = -50000.0f;
	UE_LOG(LogTemp, Warning, TEXT("Impulse Direction: %s"), *ImpulseDirection.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Impulse Strength: %f"), ImpulseStrength);
	BulletSphereComponent->AddImpulse(ImpulseDirection * ImpulseStrength);
}
void ASkript_FPSCharachter::moveBullet(float timeSpan,float deltaTime)
{
  while(timeSpan > 0)
  {

	  FVector bulletPos = bullet->GetActorLocation(); 
	  bulletPos += bullet->GetActorForwardVector() * 10.0F*deltaTime; 
	  bullet->SetActorLocation(bulletPos); 
	  timeSpan--; 
  } 
}

void ASkript_FPSCharachter::takeDamage()
{
	health -= 10.0F; 
}

float ASkript_FPSCharachter::getHealth()
{
	return health;
}

void ASkript_FPSCharachter::doReload()
{
	Ammo = 10; 
}

float ASkript_FPSCharachter::getAmmo()
{
	return Ammo;
}

void  ASkript_FPSCharachter::setCanDoStuff(bool newVal)
{
	canDoStuff = newVal; 
}

bool ASkript_FPSCharachter::getCanDoStuff()
{
	return canDoStuff;
}
