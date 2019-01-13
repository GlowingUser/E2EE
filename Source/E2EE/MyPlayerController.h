// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AE2EECharacter;

UCLASS()
class E2EE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetActiveCharacter( AE2EECharacter* Character );

protected:

	AE2EECharacter* ActiveCharacter;

	TSubclassOf<AE2EECharacter> CharacterClass;
	
};