#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Lock.generated.h"

class ULockItemInfo;
class ULockItemWidget;

class UStaticMeshComponent;
class UPickupComponent;
class UHighlightComponent;

/**
 * 
 */
UCLASS()
class E2EE_API ALock : public AItem
{
	GENERATED_BODY()

public:

	ALock();

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

	UFUNCTION( BlueprintCallable )
	void SetLockId( int InLockId );

	virtual UItemInfo* GetItemInfo() override;

	virtual UUserWidget* GetItemWidget() override;

protected:

	UPROPERTY()
	ULockItemInfo* LockItemInfo;

	UPROPERTY( BlueprintReadOnly )
	ULockItemWidget* LockItemWidget;
	
};
