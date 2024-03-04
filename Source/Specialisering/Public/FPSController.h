// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputToStringHandler.h"
#include "FPSController.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class AGunBase;
struct FInputActionValue;

UCLASS()
class SPECIALISERING_API AFPSController : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ToggleInputStringAction;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPHUD> CrossHairClass;
	UPROPERTY()
	class UPHUD* myCrossHair;

public:
	// Sets default values for this character's properties
	AFPSController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void ToggleInputString(const FInputActionValue& Value);

	AGunBase* myGun;
	InputToStringHandler myInputHandler;

	UPROPERTY();
	bool myIsInputtingString;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
