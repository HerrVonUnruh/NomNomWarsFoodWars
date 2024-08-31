#include "MyCameraController.h"

AMyCameraController::AMyCameraController()
{
    PrimaryActorTick.bCanEverTick = true;
    afkDetection = CreateDefaultSubobject<AAfkDetecter>(TEXT("AfkDetector"));
}

AMyCameraController::~AMyCameraController()
{
    //delete camHelper;
}

void AMyCameraController::BeginPlay()
{
    Super::BeginPlay();
    rotIndex = 0;
    deltaTime = 0;
    SetActorLocation(center);
    setMaxPlayerIndex(0); 
    resetPlayerPosition();
}

void AMyCameraController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (myCamera != nullptr && camHelper == nullptr)
    {
        camHelper = new MyCameraHelper(myCamera, center);
        myCamera->SetWorldLocation(camHelper->setCameraPosition(2750)); 
    }
    deltaTime = DeltaTime;
    afkDetection->IncreaseAFkTimer(DeltaTime);

    if (switchTurn || moveCameraToPos)
    {
        camAutoMovement();
    }
    else if (playerInput)
    {
        lookAt();
    }
}

void AMyCameraController::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("InputAxis_Right", this, &AMyCameraController::moveCameraHorizontal);
    PlayerInputComponent->BindAxis("InputAxis_CameraUp", this, &AMyCameraController::moveCameraUp);
}

void AMyCameraController::moveCameraHorizontal(float Value)
{
    if (Value != 0 && allowPlayerInput)
    {
        playerInput = true;
        afkDetection->setRevievedInput(playerInput);
        FRotator playerRot = GetActorRotation();
        playerRot.Yaw -= rotationSpeed * Value * deltaTime;
        FRotator newRot = FMath::RInterpTo(GetActorRotation(), playerRot, deltaTime, 4);
        SetActorRotation(newRot);
    }
    else
    {
        playerInput = false;
        afkDetection->setRevievedInput(playerInput);
    }
}

void AMyCameraController::lookAt()
{
    if (myCamera != nullptr)
    {
        FVector CameraLocation = myCamera->GetComponentLocation();
        FVector SceneRootLocation = GetActorLocation();
        FVector DirectionToSceneRoot = SceneRootLocation - CameraLocation;
        DirectionToSceneRoot.Normalize();
        FRotator TargetRotation = DirectionToSceneRoot.Rotation();
        FRotator NewRot = FMath::RInterpTo(GetActorRotation(), TargetRotation, deltaTime, 2);
        SetActorRotation(NewRot);
    }
}

void AMyCameraController::camAutoMovement()
{
    if (rotIndex >= 0 && rotIndex < viewRotations.Num())
    {
        FRotator desiredRotation = viewRotations[rotIndex]; // desiredRotation innerhalb des if-Blocks deklarieren
        float difference = GetActorRotation().Yaw - desiredRotation.Yaw; 
        UE_LOG(LogTemp, Warning, TEXT("target rotation: %f"), difference);
        if (FMath::Abs(difference) > 1)
        {
            FRotator newRot = FMath::Lerp(GetActorRotation(), desiredRotation, 1 * deltaTime);
            SetActorRotation(newRot); 
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Finieshed switching turn!"));
            switchTurn = false;
            moveCameraToPos = false;
            allowPlayerInput = true;
        }
    }
}



void AMyCameraController::moveCameraUp(float Value)
{
    if (Value != 0 && allowPlayerInput)
    {
        playerInput = true;
        afkDetection->setRevievedInput(playerInput);

        // Berechnen Sie die neue Pitch-Rotation
        float currentPitch = GetActorRotation().Pitch;
        float desiredPitchChange = rotationSpeed * Value * deltaTime;
        float newPitch = FMath::Clamp(currentPitch + desiredPitchChange, -55.0f, 20.0f);

        // Überprüfen Sie, ob die Kamera die Grenzen überschreitet, und setzen Sie die Bewegung auf Null, wenn sie es tut
        if ((currentPitch <= -55.0f && newPitch < currentPitch) || (currentPitch >= 20.0f && newPitch > currentPitch))
        {
            newPitch = currentPitch;
        }

        // Interpolieren Sie die Pitch-Rotation sanft
        FRotator targetRotation = GetActorRotation();
        targetRotation.Pitch = newPitch;
        FRotator newRotation = FMath::RInterpTo(GetActorRotation(), targetRotation, deltaTime, 15.0f);

        // Setzen Sie die neue Rotation des Actors
        SetActorRotation(newRotation);
    }
    else
    {
        playerInput = false;
        afkDetection->setRevievedInput(playerInput);
    }
}



void AMyCameraController::switchPlayerTurn()
{
    if (rotIndex < maxPlayer - 1)
    {
        rotIndex++;
    }
    else
    {
        rotIndex = 0;
    }
    UE_LOG(LogTemp, Warning, TEXT("rotation index: %d"), rotIndex);

    if (rotIndex >= 0 && rotIndex < viewRotations.Num())
    {
        switchTurn = true;
        allowPlayerInput = false;
    }
    else
    {
        allowPlayerInput = true;
    }
}

void AMyCameraController::setCamera(UCameraComponent *cam)
{
    myCamera = cam;
}

void AMyCameraController::setPositionRef()
{
    for (int x = 0; x < maxPlayer; x++)
    {
        if (x >= 0 && x < cameraViewPos.Num())
        {
            playerPositions.Add(cameraViewPos[x]->GetActorLocation());
            viewRotations.Add(cameraViewPos[x]->GetActorRotation());
        }
        else
        {
            FString Message = FString::Printf(TEXT("Initialize position failed at index %d"), x);
            break;
        }
    }
}

int AMyCameraController::getPlayerID()
{
    return rotIndex + 1;
}

void AMyCameraController::setMaxPlayerIndex(int value)
{
    maxPlayer = viewRotations.Num();
}

void AMyCameraController::resetPlayerPosition()
{
    if (!playerInput)
    {
        if (rotIndex >= 0 && rotIndex < viewRotations.Num())
        {
            moveCameraToPos = true;
        }
        else
        {
            moveCameraToPos = false;
            FString Message = FString::Printf(TEXT("couldnt find Actor in cameraViewPos at:  %d"), rotIndex);
            return;
        }
    }
}


MyCameraHelper::MyCameraHelper(UCameraComponent *camera, FVector center)
    : m_Center(center)
{
    m_Camera = camera;
}

FVector MyCameraHelper::setCameraPosition(float distance)
{
    if (m_Camera == nullptr)
    {
        return FVector(0, 0, 0); // Early out!
    }

    FVector directionToCenter = m_Center - m_Camera->GetComponentLocation();
    directionToCenter.Normalize();
    FVector newCameraPos = m_Center - directionToCenter * distance;
    m_Camera->SetWorldLocation(newCameraPos);

    return newCameraPos;
}

FVector MyCameraHelper::setPlayerPositions(FVector position, float distance)
{
    FVector directionToCenter = m_Center - position;
    directionToCenter.Normalize();
    FVector newPos = m_Center - directionToCenter * distance;

    return newPos;
}