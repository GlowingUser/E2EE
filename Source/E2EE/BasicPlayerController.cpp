#include "BasicPlayerController.h"

#include "MPGameMode.h"
#include "BasicCharacter.h"
#include "InventoryMenu.h"
#include "Inventory.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ABasicPlayerController::ABasicPlayerController() {}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ABasicPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Don't switch camera when possessing.
	bAutoManageActiveCameraTarget = false;

	// Enable mouse.
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// Create InventoryMenu.
	if ( InventoryMenuClass )
	{
		InventoryMenu = CreateWidget<UInventoryMenu>( this, InventoryMenuClass );
	}
	else
	{
		UE_LOG( LogTemp, Error, TEXT( "AMyPlayerController's InventoryMenuClass isn't set!" ) );
		return;
	}
}

ABasicCharacter* ABasicPlayerController::GetActiveCharacter() 
{
	return ActiveCharacter;
}

void ABasicPlayerController::SetActiveCharacter( ABasicCharacter* Character )
{
	// Turn off previous character's Widget_Selected.
	// Do nothing if there's no previous character.
	if ( ActiveCharacter )
	{
		ActiveCharacter->ToggleWidget( false );
	}

	// Update ActiveCharacter.
	ActiveCharacter = Character;

	// Possess and adjust rotation.
	Possess( ActiveCharacter );
	SetControlRotation( FVector::ZeroVector.ToOrientationRotator() );

	// Turn on Widget_Selected.
	ActiveCharacter->ToggleWidget( true );
}

void ABasicPlayerController::SubmitCharacterSelectionRequest_Implementation( const FString& CharacterName )
{
	if ( Role == ROLE_Authority )
	{
		AMPGameMode* MPGameMode = GetWorld()->GetAuthGameMode<AMPGameMode>();

		if ( MPGameMode )
		{
			MPGameMode->ProcessCharacterSelectionRequest( this, CharacterName );
		}
	}
}

bool ABasicPlayerController::SubmitCharacterSelectionRequest_Validate( const FString& CharacterName )
{
	return true;
}

void ABasicPlayerController::ShowInventoryMenu( UInventory* Inventory )
{
	InventoryMenu->ShowInventory( Inventory );
}
