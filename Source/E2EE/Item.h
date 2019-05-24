#pragma once

#include "ItemUsage.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemInfo;
class UItemWidget;

UCLASS( BlueprintType )
class E2EE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();

public:

	UFUNCTION( BlueprintCallable )
	virtual UItemInfo* GetItemInfo() PURE_VIRTUAL( , return ItemInfo; );

	UFUNCTION( BlueprintCallable )
	virtual void SetItemInfo( UItemInfo* InItemInfo ) PURE_VIRTUAL( , );

protected:

	UPROPERTY()
	UItemInfo* ItemInfo;

};
