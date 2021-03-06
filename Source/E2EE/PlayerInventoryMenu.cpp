#include "PlayerInventoryMenu.h"

#include "Inventory.h"
#include "ItemClicker.h"
#include "ItemMenu.h"
#include "BasicPlayerController.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPlayerInventoryMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind UItemMenu events.
	ItemMenu->OnButtonDestroyClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonDestroyClicked );
	ItemMenu->OnButtonDropClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonDropClicked );
	ItemMenu->OnButtonDuplicateClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonDuplicateClicked );
	ItemMenu->OnButtonOpenClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonOpenClicked );
	ItemMenu->OnButtonReadClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonReadClicked );
	ItemMenu->OnButtonForCombinationClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnItemMenuButtonForCombinationClicked );

	Button_Close->OnClicked.AddDynamic( this, &UPlayerInventoryMenu::HandleOnButtonCloseClicked );

	PlayerController = Cast<ABasicPlayerController>( GetWorld()->GetFirstPlayerController() );
}

void UPlayerInventoryMenu::HideInventory()
{
	bIsCombining = false;

	ClearDescription();

	ItemMenu->Reset();

	PlayerController->HideNotification( true );

	RemoveFromParent();
}

void UPlayerInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{
	Super::HandleOnItemClickerClicked( ClickedItemClicker );

	UItemInfo* TargetItem = ClickedItemClicker->GetItemInfo();

	if ( bIsCombining )
	{
		PlayerController->HideNotification( true );

		TArray<UItemInfo*> CombiningItems;
		CombiningItems.Add( FirstItemForCombination );
		CombiningItems.Add( TargetItem );
		Inventory->CombineItems( CombiningItems );

		bIsCombining = false;

		if ( LastClickedClicker ) LastClickedClicker->Unhighlight();
		if ( ClickedItemClicker ) ClickedItemClicker->Unhighlight();

		ClearDescription();
	}
	else
	{
		ItemMenu->Display( TargetItem );

		FirstItemForCombination = TargetItem;

		if ( LastClickedClicker ) LastClickedClicker->Unhighlight();
		ClickedItemClicker->HighlightForClicking();
	}

	LastClickedClicker = ClickedItemClicker;
}

#pragma region Item Menu event handlers
void UPlayerInventoryMenu::HandleOnItemMenuButtonDestroyClicked( UItemInfo* TargetItem )
{
	Inventory->RemoveItem( TargetItem );

	ClearDescription();
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonDropClicked( UItemInfo* TargetItem )
{
	Inventory->DropItem( TargetItem );

	ClearDescription();
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonDuplicateClicked( UItemInfo* TargetItem )
{
	Inventory->ServerDuplicateItem( TargetItem );
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonOpenClicked( UItemInfo* TargetItem )
{
	Inventory->OpenItem( TargetItem );

	ClearDescription();
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonReadClicked( UItemInfo* TargetItem )
{
	Inventory->ReadItem( TargetItem );
}

void UPlayerInventoryMenu::HandleOnItemMenuButtonForCombinationClicked( UItemInfo* TargetItem )
{
	bIsCombining = true;

	PlayerController->DisplayNotification( NSLOCTEXT( "PlayerInventoryMenu", "CombiningItem", "Select a secondary item." ), true );
}
#pragma endregion

void UPlayerInventoryMenu::HandleOnButtonCloseClicked()
{
	HideInventory();
}

void UPlayerInventoryMenu::ToggleInput( bool Enabled )
{
	Super::ToggleInput( Enabled );

	Button_Close->SetIsEnabled( Enabled );
}
