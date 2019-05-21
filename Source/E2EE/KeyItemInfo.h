#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "KeyItemInfo.generated.h"

/**
 *
 */
UCLASS()
class E2EE_API UKeyItemInfo : public UItemInfo
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	int GetKeyId();

	UFUNCTION( BlueprintCallable )
	void SetKeyId( int InKeyId );

protected:

	int KeyId;

};
