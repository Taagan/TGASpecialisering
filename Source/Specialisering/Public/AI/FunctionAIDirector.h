// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FunctionAIDirector.generated.h"
/**
 * 
 */
UCLASS()
class SPECIALISERING_API UFunctionAIDirector : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable, Category = "AIDirector") void SpawnEnemy();
	UPROPERTY(EditAnywhere, Category = "AIDirector")float myDirectorValue;
};
