#include "BotInventoryMenu.h"

#include "ItemClicker.h"
#include "KeyItemInfo.h"
#include "ContainerItemInfo.h"
#include "DevUtilities.h"

void UBotInventoryMenu::PreDuplicationHighlight( TArray<UItemInfo*> ItemsToDuplicate )
{
	for ( int i = 0; i < ItemsToDuplicate.Num(); i++ )
	{
		if ( UItemClicker** pItemClicker = ItemToItemClicker.Find( ItemsToDuplicate[i] ) )
		{
			UItemClicker* ItemClicker = *pItemClicker;

			// Only subscribe to 1, instead of all, should be enough.
			if ( i == 0 )
			{
				ItemClicker->OnPreDuplicationHighlightFinished.AddDynamic( this, &UBotInventoryMenu::HandleOnPreDuplicationHighlightCompleted );
			}

			ItemClicker->HighlightForPreDuplication();
		}
		else { ensureAlways( false ); }
	}
}

void UBotInventoryMenu::ContainerOpenHighlight( UContainerItemInfo* Container )
{
	if ( UItemClicker** pItemClicker = ItemToItemClicker.Find( Container ) )
	{
		( *pItemClicker )->OnContainerOpenHighlightFinished.AddDynamic( this, &UBotInventoryMenu::HandleOnContainerOpenHighlightCompleted );

		( *pItemClicker )->HighlightForContainerOpen();
	}
	else { ensureAlways( false ); }
}

void UBotInventoryMenu::ContainerUnlockHighlight( UKeyItemInfo* KeyItem, UContainerItemInfo* Container )
{
	UItemClicker** pKeyItemClicker = ItemToItemClicker.Find( KeyItem );
	UItemClicker** pContainerItemClicker = ItemToItemClicker.Find( Container );

	if ( pKeyItemClicker && pContainerItemClicker )
	{
		// Only subscribe to one event.
		( *pKeyItemClicker )->OnContainerUnlockHighlightFinished.AddDynamic( this, &UBotInventoryMenu::HandleOnContainerUnlockHighlightCompleted );
	
		( *pKeyItemClicker )->HighlightForContainerUnlock();
		( *pContainerItemClicker )->HighlightForContainerUnlock();
	}
	else { ensureAlways( false ); }
}

void UBotInventoryMenu::HideInventory()
{
	Super::HideInventory();

	OnHidden.Broadcast();
}

void UBotInventoryMenu::HandleOnPreDuplicationHighlightCompleted( UItemClicker* HighlightedClicker )
{
	HighlightedClicker->OnAdditionHighlightFinished.RemoveDynamic( this, &UBotInventoryMenu::HandleOnPreDuplicationHighlightCompleted );

	OnPreDuplicationHighlightCompleted.Broadcast();
}

void UBotInventoryMenu::HandleOnContainerOpenHighlightCompleted( UItemClicker* HighlightedClicker )
{
	HighlightedClicker->OnContainerOpenHighlightFinished.RemoveDynamic( this, &UBotInventoryMenu::HandleOnContainerOpenHighlightCompleted );
	
	OnContainerOpenHighlightCompleted.Broadcast( Cast<UContainerItemInfo>( HighlightedClicker->GetItemInfo() ) );
}

void UBotInventoryMenu::HandleOnContainerUnlockHighlightCompleted( UItemClicker* HighlightedClicker )
{
	HighlightedClicker->OnContainerUnlockHighlightFinished.RemoveDynamic( this, &UBotInventoryMenu::HandleOnContainerUnlockHighlightCompleted );

	OnContainerUnlockHighlightCompleted.Broadcast();
}
