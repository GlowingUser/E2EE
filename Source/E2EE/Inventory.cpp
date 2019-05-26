#include "Inventory.h"

#include "Item.h"
#include "ItemCombiner.h"
#include "DropItemComponent.h"
#include "BasicCharacter.h"
#include "DevUtilities.h"

#include "Net/UnrealNetwork.h"

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	ItemCombiner = NewObject<UItemCombiner>();
}

TArray<UItemInfo*> UInventory::GetItems()
{
	return Items;
}

int UInventory::CountItems()
{
	return Items.Num();
}

void UInventory::AddItem( UItemInfo* ItemToAdd )
{
	if ( !ItemToAdd )
	{
		UDevUtilities::PrintError( "UInventory::AddItem gets a null UItemInfo!" );
		return;
	}

	Items.Add( ItemToAdd );

	OnItemAdded.Broadcast( ItemToAdd );
}

void UInventory::RemoveItem( UItemInfo* ItemToRemove )
{
	Items.Remove( ItemToRemove );

	OnItemRemoved.Broadcast( ItemToRemove );
}

void UInventory::DropItem( UItemInfo* ItemToDrop )
{
	UDropItemComponent* DropItemComponent = GetOwner()->FindComponentByClass<UDropItemComponent>();

	if ( DropItemComponent )
	{
		DropItemComponent->ServerDropItem( ItemToDrop );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "The owner of this UInventory doesn't have a UDropItemComponent! Aborted." ) );
		return;
	}

	RemoveItem( ItemToDrop );
}

void UInventory::CombineItems( TArray<UItemInfo*> SourceItems )
{
	TArray<UItemInfo*> ResultItems = ItemCombiner->CombineItems( SourceItems );

	for ( UItemInfo* Item : SourceItems )
	{
		RemoveItem( Item );
	}

	for ( UItemInfo* Item : ResultItems )
	{
		AddItem( Item );
	}
}
