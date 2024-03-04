// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSController.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GunBase.h"
#include "InputStringTypes.h"
#include "Blueprint/UserWidget.h"
#include "PHUD.h"

// Sets default values
AFPSController::AFPSController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPSController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	TArray<AActor*> kids;
	GetAttachedActors(kids);
	for (auto& kid : kids)
	{
		if (AGunBase* gun = Cast<AGunBase>(kid))
		{
			myGun = gun;
			myGun->Attach(this);
		}
	}

	APlayerController* fPC = GetController<APlayerController>();
	myCrossHair = CreateWidget<UPHUD>(fPC, CrossHairClass);
	myCrossHair->AddToPlayerScreen();

	myIsInputtingString = false;
}

void AFPSController::Look(const FInputActionValue& aValue)
{
	FVector2D LookAxis = aValue.Get<FVector2D>();
	LookAxis.Y = -LookAxis.Y;

	if (Controller != nullptr)
	{
		if (myIsInputtingString == false)
		{
			AddControllerYawInput(LookAxis.X);
			AddControllerPitchInput(LookAxis.Y);
		}
		else
		{
			myInputHandler.SendInput(LookAxis);
			if (myInputHandler.HasInputPathChanged())
			{
				FVector2D endPoint(myInputHandler.GetInputPath().back());
				FVector2D startPoint = FVector2D::ZeroVector;
				myCrossHair->AddComboLine(startPoint, endPoint);
				myCrossHair->SetComboPoints(endPoint);
			}
		}
	}
}

void AFPSController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSController::Shoot(const FInputActionValue& Value)
{
	//myGun->ParseInputStringToGun(std::to_string(eInputStringTypes::SHOOT));
	myIsInputtingString = false;
	myGun->ParseInputStringToGun(myInputHandler.RetrieveString());
	myGun->ForwardShootAction();
}

void AFPSController::ToggleInputString(const FInputActionValue& Value)
{
	myIsInputtingString = !myIsInputtingString;
	if (myIsInputtingString == false)
	{
		myGun->ParseInputStringToGun(myInputHandler.RetrieveString());
	}
}

// Called every frame
void AFPSController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	myCrossHair->SetCrosshairPos(myInputHandler.GetCursorPos());
}

// Called to bind functionality to input
void AFPSController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSController::Look);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSController::Move);
	Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AFPSController::Shoot);
	Input->BindAction(ToggleInputStringAction, ETriggerEvent::Started, this, &AFPSController::ToggleInputString);
}

