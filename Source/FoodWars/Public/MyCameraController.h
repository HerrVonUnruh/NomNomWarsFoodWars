#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "AfkDetecter.h"
#include "MyCameraController.generated.h"

class MyCameraHelper;

UCLASS()
class FOODWARS_API AMyCameraController : public APawn
{
    GENERATED_BODY()

public:
    AMyCameraController();
    ~AMyCameraController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void moveCameraHorizontal(float Value);
    void moveCameraUp(float Value);
    void lookAt();
    UFUNCTION(BlueprintCallable)
    void switchPlayerTurn();
    UFUNCTION(BlueprintCallable)
    int getPlayerID();
    void setPositionRef();
    UFUNCTION(BlueprintCallable)
    void setMaxPlayerIndex(int value);
    UFUNCTION(BlueprintCallable)
    void resetPlayerPosition();
    UFUNCTION(BlueprintCallable)
    void setCamera(UCameraComponent* cam);
    void camAutoMovement();

private:
    UPROPERTY(EditAnywhere, Category = "Position Handler")
    int maxPlayer = 3;

    bool playerInput = false;
    int32 keyVal = 0;

    int maxPlayerIndex = 0;
    bool allowPlayerInput = true;
    bool isOnPoint = false;
    UPROPERTY(EditAnywhere, Category = "Turn Change Speed")
    float rotationSpeed = 1.0f;
    bool switchTurn = false;
    bool moveCameraToPos = true;
    bool settedCamPos = false; 

    UPROPERTY(EditAnywhere, Category = "Rotation Handler")
    FVector center = FVector(0, 0, 0);

    UPROPERTY(EditAnywhere, Category = "Position Handler")
    TArray<FVector> playerPositions;

    UPROPERTY(EditAnywhere, Category = "Rotation Handler")
    TArray<FRotator> viewRotations;

    UPROPERTY(EditAnywhere, Category = "Position Handler")
    TArray<AActor*> cameraViewPos;
    int32 rotIndex = 0;
    AAfkDetecter* afkDetection = nullptr;
    MyCameraHelper* camHelper = nullptr;
    float deltaTime;
    UCameraComponent* myCamera;

    // Add this line to declare the MyCameraHelper as a friend class
    friend class MyCameraHelper;
};

class MyCameraHelper
{
public:
    MyCameraHelper(UCameraComponent* camera, FVector Center);

    FVector setCameraPosition(float distance);
    FVector setPlayerPositions(FVector position, float distance);

private:
    UCameraComponent* m_Camera;
    FVector m_Center;
};