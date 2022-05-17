// Copyright © 2022 Last Second


#include "GameMenuControlSettingsWidget.h"

#include "Components/ProgressBar.h"
#include "Components/Slider.h"

bool UGameMenuControlSettingsWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!SensibilitySlider) return false;
		
		SensibilityText = FText::FromString("100");
		
		if (SensibilitySlider) SensibilitySlider->OnValueChanged.AddDynamic(this, &UGameMenuControlSettingsWidget::SensibilitySliderChanged);
		
		//UGameplayStatics::SetBaseSoundMix(GetWorld(), MasterSoundMix);

		return true; //InitializeValuesFromSave();
	}
	return false;
}
/*
bool UGameMenuControlSettingsWidget::InitializeValuesFromSave()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveGameNameSlot, 0))
	{
		USaveGameInformations* SaveGameRef = Cast<USaveGameInformations>(UGameplayStatics::CreateSaveGameObject(SaveGameInformations));

		SaveGameRef->GlobalVolumeValue = 1.f;
		SaveGameRef->MusicVolumeValue = 1.f;
		SaveGameRef->EffectsVolumeValue = 1.f;
		SaveGameRef->EnvironmentVolumeValue = 1.f;
		SaveGameRef->DialoguesVolumeValue = 1.f;
		
		return UGameplayStatics::SaveGameToSlot(SaveGameRef, SaveGameNameSlot, 0);
		
	}
	const USaveGameInformations* SaveGameRef = Cast<USaveGameInformations>(UGameplayStatics::LoadGameFromSlot(SaveGameNameSlot, 0));

	GlobalSliderChanged(SaveGameRef->GlobalVolumeValue);
	MusicSliderChanged(SaveGameRef->MusicVolumeValue);
	EffectsSliderChanged(SaveGameRef->EffectsVolumeValue);
	EnvironmentSliderChanged(SaveGameRef->EnvironmentVolumeValue);
	DialoguesSliderChanged(SaveGameRef->DialoguesVolumeValue);

	return true;
}
*/
void UGameMenuControlSettingsWidget::SensibilitySliderChanged(float Value)
{
	SetSensibilityVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
	const float NewVolumeValue = Value / (SensibilitySlider->MaxValue - SensibilitySlider->MinValue);
	if (SensibilityProgrBar) SensibilityProgrBar->SetPercent(NewVolumeValue);
}