// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Skript_FPSCharachter.generated.h"
UCLASS()
class FOODWARS_API ASkript_FPSCharachter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkript_FPSCharachter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void getPlayerMovementInput(class UInputComponent* PlayerInputComponent);
	void getPlayerCameraInput(class UInputComponent* PlayerInputComponent); 

	UStaticMeshComponent* getButtetSphereComponent();
	void spawnBullet(UStaticMeshComponent* bullet); 

	//movement
	void moveForward(float value); 
	void moveRight(float value);
	void jump(); 
	void stopJumping(); 

	//mouse look
	void rotateRight(float value); 
	void rotateCameraUp(float value); 

	UFUNCTION(BlueprintCallable, Category = "Firering")
	void shoot(TSubclassOf<AActor> bulletClass, FVector barrel, bool debugBool, FRotator barrelRotation);
	//helper functions
	UFUNCTION(BlueprintCallable, Category = "Mouse Look")
	void setCamera(UCameraComponent* camera); 
	UFUNCTION(BlueprintCallable, Category = "Firering")
	void moveBullet(float timeSpan, float deltaTime);

	UFUNCTION(BlueprintCallable, Category = "Player Health")
	void takeDamage(); 
	UFUNCTION(BlueprintCallable, Category = "Player Health")
	float getHealth(); 
	UFUNCTION(BlueprintCallable, Category = "Firering")
	void doReload(); 
	UFUNCTION(BlueprintCallable, Category = "Firering")
	float getAmmo(); 
	

	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	void setCanDoStuff(bool newValue);
	UFUNCTION(BlueprintCallable, Category = "Player Controller")
	bool getCanDoStuff();

private:
	FVector moveVector;
	UPROPERTY(EditAnywhere)
	UCameraComponent* camera;

	AActor* bullet;

	float health = 100.0F; 

	UPROPERTY(EditAnywhere)
	float speed = 100; 

	float Ammo = 10;
	
	bool canDoStuff = true; 

	UPROPERTY(EditAnywhere)
	float jumpForce = 300.0F;
	bool isJumping = false; 
};
