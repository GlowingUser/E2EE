// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Command.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UCommand;
class UItemWidget;

UCLASS( BlueprintType )
class E2EE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

protected:

	UTexture2D* Icon;

	TArray<UCommand*> Commands;

	UCommand* ActiveCommand;

public:

	UFUNCTION( BlueprintCallable )
	UTexture2D* GetIcon();

	UFUNCTION( BlueprintCallable )
	void SetIcon( UTexture2D* IconToSet );

};
