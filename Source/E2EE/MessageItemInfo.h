#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.h"
#include "MessageItemInfo.generated.h"

/**
 * 
 */
UCLASS()
class E2EE_API UMessageItemInfo : public UItemInfo
{
	GENERATED_BODY()

public:

	virtual UMessageItemInfo* Duplicate() override;
	
};