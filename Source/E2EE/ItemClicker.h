#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemClicker.generated.h"

class UItemInfo;
class UItemWidget;
class UButton;
class UNamedSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnButtonClickerClicked, UItemClicker*, ClickedItemClicker );

/**
 * 
 */
UCLASS()
class E2EE_API UItemClicker : public UUserWidget
{
	GENERATED_BODY()

public:

	UItemClicker( const FObjectInitializer& ObjectInitializer );

protected:

	virtual void NativeOnInitialized() override;

public:

	UPROPERTY( BlueprintAssignable )
	FOnButtonClickerClicked OnClicked;

public:

	UFUNCTION( BlueprintCallable )
	UItemInfo* GetItemInfo();

	UFUNCTION( BlueprintCallable )
	void SetItemInfo( UItemInfo* ItemToSet );

protected:

	UPROPERTY( meta = ( BindWidget ) )
	UButton* Button_Clicker;

	UPROPERTY( meta = ( BindWidget ) )
	UNamedSlot* NamedSlot_ItemWidgetSlot;

	UPROPERTY( BlueprintReadWrite )
	UItemInfo* ItemInfo;

protected:

	UFUNCTION()
	void HandleOnButtonClicked();
	
};
