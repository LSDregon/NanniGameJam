// Copyright © 2022 Last Second


#include "GameMenuAudioSettingsWidget.h"

#include "Kismet/GameplayStatics.h"


bool UGameMenuAudioSettingsWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!GlobalSlider || !MusicSlider || !EffectsSlider || !EnvironmentSlider || !DialoguesSlider)
		{
			return false;
		}
		
		GlobalText = FText::FromString("100");
		MusicText = FText::FromString("100");
		EffectsText = FText::FromString("100");
		EnvironmentText = FText::FromString("100");
		DialoguesText = FText::FromString("100");
		
		if (GlobalSlider) GlobalSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::GlobalSliderChanged);
		if (MusicSlider) MusicSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::MusicSliderChanged);
		if (EffectsSlider) EffectsSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::EffectsSliderChanged);
		if (EnvironmentSlider) EnvironmentSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::EnvironmentSliderChanged);
		if (DialoguesSlider) DialoguesSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::DialoguesSliderChanged);
		
		UGameplayStatics::SetBaseSoundMix(GetWorld(), MasterSoundMix);

		return InitializeValuesFromSave();
	}
	return false;
}

bool UGameMenuAudioSettingsWidget::InitializeValuesFromSave()
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

void UGameMenuAudioSettingsWidget::GlobalSliderChanged(float Value)
{
	SetGlobalVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
	const float NewVolumeValue = Value / (GlobalSlider->MaxValue - GlobalSlider->MinValue);
	GlobalProgrBar->SetPercent(NewVolumeValue);

	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, GlobalSoundClass, NewVolumeValue);
}
void UGameMenuAudioSettingsWidget::MusicSliderChanged(float Value)
{
	SetMusicVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
	const float NewVolumeValue = Value / (MusicSlider->MaxValue - MusicSlider->MinValue);
	MusicProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MusicSoundClass, NewVolumeValue);
}
void UGameMenuAudioSettingsWidget::EffectsSliderChanged(float Value)
{
	SetEffectsVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
	const float NewVolumeValue = Value / (EffectsSlider->MaxValue - EffectsSlider->MinValue);
	EffectsProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, EffectsSoundClass, NewVolumeValue);
}
void UGameMenuAudioSettingsWidget::EnvironmentSliderChanged(float Value)
{
	SetEnvironmentVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
	const float NewVolumeValue = Value / (EnvironmentSlider->MaxValue - EnvironmentSlider->MinValue);
	EnvironmentProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, EnvironmentSoundClass, NewVolumeValue);
}
void UGameMenuAudioSettingsWidget::DialoguesSliderChanged(float Value)
{
	SetDialoguesVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
	const float NewVolumeValue = Value / (DialoguesSlider->MaxValue - DialoguesSlider->MinValue);
	DialoguesProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, DialoguesSoundClass, NewVolumeValue);
}
