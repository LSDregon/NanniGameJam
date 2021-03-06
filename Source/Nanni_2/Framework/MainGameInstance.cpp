// Copyright © 2022 Last Second


#include "MainGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UMainGameInstance::Init()
{
	Super::Init();

	if (SaveGameNameSlot.IsEmpty() || SaveGameNameSlot.Equals(""))
	{
		SaveGameNameSlot = "DefaultSaveSlot";
	}
	
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameNameSlot, 0))
	{
		InitializeSaveGameSlot();
		return;
	}
	
	SaveGameSlot = Cast<USaveGameInformations>(UGameplayStatics::LoadGameFromSlot(SaveGameNameSlot, 0));	
}

void UMainGameInstance::InitializeSaveGameSlot()
{
	SaveGameSlot = Cast<USaveGameInformations>(UGameplayStatics::CreateSaveGameObject(USaveGameInformations::StaticClass()));
	
	SaveGameSlot->GlobalVolumeValue = 100.f;
	SaveGameSlot->MusicVolumeValue = 100.f;
	SaveGameSlot->EffectsVolumeValue = 100.f;
	SaveGameSlot->EnvironmentVolumeValue = 100.f;
	SaveGameSlot->DialoguesVolumeValue = 100.f;
	SaveGameSlot->MouseSensitivity = 70.f;
	 	
	UGameplayStatics::SaveGameToSlot(SaveGameSlot, SaveGameNameSlot, 0);
}

USaveGameInformations* UMainGameInstance::LoadSaveGameSlot()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameNameSlot, 0))
	{
		InitializeSaveGameSlot();
	}
	return Cast<USaveGameInformations>(UGameplayStatics::LoadGameFromSlot(SaveGameNameSlot, 0));
}

bool UMainGameInstance::SaveSaveGameSlot(USaveGameInformations* SaveGameSlotRef) const
{
	return UGameplayStatics::SaveGameToSlot(SaveGameSlotRef, SaveGameNameSlot, 0);
}
