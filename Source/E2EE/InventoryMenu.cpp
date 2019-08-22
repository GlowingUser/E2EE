#include "InventoryMenu.h"

#include "ItemClicker.h"
#include "ItemMenu.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemWidget.h"
#include "DevUtilities.h"

#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/NamedSlot.h"

void UInventoryMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if ( !ItemClickerClass )
	{
		UDevUtilities::PrintError( "InventoryMenu's ItemClickerClass isn't assigned!" );
		return;
	}

	Button_HideInventoryMenu->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnButtonHideInventoryMenuClicked );
}

/**
 * Show a specified Inventory.
 * Only reload and reset if it's a different inventory.
 */
void UInventoryMenu::ShowInventory( UInventory* TargetInventory )
{
	if ( !TargetInventory ) { ensureAlways( false ); return; }

	if ( Inventory != TargetInventory )
	{
		if ( Inventory )
		{
			Inventory->OnItemAdded.RemoveAll( this );
			Inventory->OnItemRemoved.RemoveAll( this );
		}

		Inventory = TargetInventory;

		ReloadInventoryDisplay();

		Inventory->OnItemAdded.AddDynamic( this, &UInventoryMenu::HandleOnItemAdded );
		Inventory->OnItemRemoved.AddDynamic( this, &UInventoryMenu::HandleOnItemRemoved );
	}

	AddToViewport();

	for ( UItemClicker* ItemClicker : ClickersPendingForHighlightForAddition )
	{
		ItemClicker->HighlightForItemAddition();
	}
	ClickersPendingForHighlightForAddition.Empty();
}

void UInventoryMenu::HideInventory()
{
	bIsCombining = false;

	if ( ItemMenu->IsInViewport() )
	{
		ItemMenu->RemoveFromParent();
	}

	RemoveFromParent();
}

/**
 * Create a new ItemClicker with ItemWidget content, and add it to the WrapBox.
 */
UItemClicker* UInventoryMenu::AddNewItemClicker( UItemInfo* Item )
{
	UItemClicker* ItemClicker = CreateWidget<UItemClicker>( this, ItemClickerClass );

	ItemClicker->SetItemInfo( Item );

	ItemClicker->OnClicked.AddDynamic( this, &UInventoryMenu::HandleOnItemClickerClicked );

	WrapBox_ItemClickers->AddChildWrapBox( ItemClicker );

	ItemToItemClicker.Add( Item, ItemClicker );

	return ItemClicker;
}

/**
 * Remove all the ItemClickers.
 * Add new ItemClickers based on Inventory's Items.
 */
void UInventoryMenu::ReloadInventoryDisplay()
{
	WrapBox_ItemClickers->ClearChildren();

	if ( !Inventory ) { ensureAlways( false ); return; }

	TArray<UItemInfo*> Items = Inventory->GetItems();

	for ( int i = 0; i < Items.Num(); i++ )
	{
		if ( ensureAlways( Items[i] ) )
		{
			UItemClicker* ItemClicker = AddNewItemClicker( Items[i] );
		}
	}
}

void UInventoryMenu::HandleOnItemClickerClicked( UItemClicker* ClickedItemClicker )
{

}

void UInventoryMenu::HandleOnButtonHideInventoryMenuClicked()
{
	HideInventory();
}

void UInventoryMenu::HandleOnItemAdded( UItemInfo* ItemAdded )
{
	UItemClicker* NewItemClicker = AddNewItemClicker( ItemAdded );

	if ( IsInViewport() )
	{
		NewItemClicker->HighlightForItemAddition();
	}
	else
	{
		ClickersPendingForHighlightForAddition.Add( NewItemClicker );
	}
}

void UInventoryMenu::HandleOnItemRemoved( UItemInfo* ItemRemoved )
{
	UItemClicker** pItemClicker = ItemToItemClicker.Find( ItemRemoved );

	if ( pItemClicker )
	{
		(*pItemClicker)->RemoveFromParent();
	}
	else
	{
		UDevUtilities::PrintError( "UInventoryMenu hears an Item removal event, but no UItemClicker matches the removed item!" );
	}
}
