#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Container.generated.h"

class UContainerItemInfo;
class UContainerItemWidget;

class UStaticMeshComponent;
class UPickupComponent;
class UHighlightComponent;

/**
 *
 */
UCLASS()
class E2EE_API AContainer : public AItem
{
	GENERATED_BODY()

public:

	AContainer();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UPickupComponent* PickupComponent;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	UHighlightComponent* HightlightComponent;

public:



	virtual UItemInfo* GetItemInfo() override;

	virtual UUserWidget* GetItemWidget() override;

protected:

	UPROPERTY()
	UContainerItemInfo* ContainerItemInfo;

	UPROPERTY( BlueprintReadOnly )
	UContainerItemWidget* ContainerItemWidget;

};
