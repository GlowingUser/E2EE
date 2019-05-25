#include "ContainerItemWidget.h"

#include "ContaineritemInfo.h"
#include "DevUtilities.h"

#include "Engine/Engine.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UContainerItemWidget::SetItemInfo( UItemInfo* InItemInfo )
{
	ContainerItemInfo = Cast<UContainerItemInfo>( InItemInfo );
	if ( ContainerItemInfo )
	{
		ContainerItemInfo->OnOccupied.AddDynamic( this, &UContainerItemWidget::HandleOnOccupied );
		ContainerItemInfo->OnVacated.AddDynamic( this, &UContainerItemWidget::HandleOnVacated );
		ContainerItemInfo->OnLocked.AddDynamic( this, &UContainerItemWidget::HandleOnLocked );
		ContainerItemInfo->OnUnlocked.AddDynamic( this, &UContainerItemWidget::HandleOnUnlocked );
	}
	else
	{
		UDevUtilities::PrintError( TEXT( "UContainerItemWidget::SetItemInfo gets a non-ContainerItemInfo!" ) );
	}
}

void UContainerItemWidget::UpdateImage( UTexture2D* NewTexture )
{
	Image_Icon->SetBrushFromTexture( NewTexture );
}
