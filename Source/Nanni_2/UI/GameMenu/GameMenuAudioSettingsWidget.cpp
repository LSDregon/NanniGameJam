// Copyright © 2022 Last Second


#include "GameMenuAudioSettingsWidget.h"

#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"
#include "Nanni_2/Framework/MainGameInstance.h"
#include "Nanni_2/Framework/SaveGameInformations.h"

bool UGameMenuAudioSettingsWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!GlobalSlider || !MusicSlider || !EffectsSlider || !EnvironmentSlider || !DialoguesSlider)
		{
			return false;
		}
		
		if (GlobalSlider) GlobalSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::GlobalSliderChanged);
		if (MusicSlider) MusicSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::MusicSliderChanged);
		if (EffectsSlider) EffectsSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::EffectsSliderChanged);
		if (EnvironmentSlider) EnvironmentSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::EnvironmentSliderChanged);
		if (DialoguesSlider) DialoguesSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::DialoguesSliderChanged);
		
		UGameplayStatics::SetBaseSoundMix(GetWorld(), MasterSoundMix);

		//return true; 
		return InitializeValuesFromSave();
	}
	return false;
}

bool UGameMenuAudioSettingsWidget::InitializeValuesFromSave()
{
	UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!MainGameInstance)
	{
		return false;
	}

	SavedGame = MainGameInstance->LoadSaveGameSlot();

	GlobalSliderChanged(SavedGame->GlobalVolumeValue);
	MusicSliderChanged(SavedGame->MusicVolumeValue);
	EffectsSliderChanged(SavedGame->EffectsVolumeValue);
	EnvironmentSliderChanged(SavedGame->EnvironmentVolumeValue);
	DialoguesSliderChanged(SavedGame->DialoguesVolumeValue);

	return true;
}

bool UGameMenuAudioSettingsWidget::SaveAudioInfos()
{
	UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!MainGameInstance)
	{
		return false;
	}
	return MainGameInstance->SaveSaveGameSlot(SavedGame);
}

void UGameMenuAudioSettingsWidget::GlobalSliderChanged(float Value)
{
	SetGlobalVolumeValue(FText::FromString(FString::FromInt(FMath::FloorToInt(Value))));
	GlobalSlider->SetValue(Value);
	const float NewVolumeValue = Value / (GlobalSlider->MaxValue - GlobalSlider->MinValue);
	if (GlobalProgrBar) GlobalProgrBar->SetPercent(NewVolumeValue);

	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, GlobalSoundClass, NewVolumeValue);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);

	SavedGame->GlobalVolumeValue = NewVolumeValue * 100;
	SaveAudioInfos();	
}
void UGameMenuAudioSettingsWidget::MusicSliderChanged(float Value)
{
	SetMusicVolumeValue(FText::FromString(FString::FromInt(FMath::FloorToInt(Value))));
	MusicSlider->SetValue(Value);
	const float NewVolumeValue = Value / (MusicSlider->MaxValue - MusicSlider->MinValue);
	if (MusicProgrBar) MusicProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MusicSoundClass, NewVolumeValue);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);

	SavedGame->MusicVolumeValue = NewVolumeValue * 100;
	SaveAudioInfos();	
}
void UGameMenuAudioSettingsWidget::EffectsSliderChanged(float Value)
{
	SetEffectsVolumeValue(FText::FromString(FString::FromInt(FMath::FloorToInt(Value))));
	EffectsSlider->SetValue(Value);
	const float NewVolumeValue = Value / (EffectsSlider->MaxValue - EffectsSlider->MinValue);
	if (EffectsProgrBar) EffectsProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, EffectsSoundClass, NewVolumeValue);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);

	SavedGame->EffectsVolumeValue = NewVolumeValue * 100;
	SaveAudioInfos();	
}
void UGameMenuAudioSettingsWidget::EnvironmentSliderChanged(float Value)
{
	SetEnvironmentVolumeValue(FText::FromString(FString::FromInt(FMath::FloorToInt(Value))));
	EnvironmentSlider->SetValue(Value);
	const float NewVolumeValue = Value / (EnvironmentSlider->MaxValue - EnvironmentSlider->MinValue);
	if (EnvironmentProgrBar) EnvironmentProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, EnvironmentSoundClass, NewVolumeValue);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);

	SavedGame->EnvironmentVolumeValue = NewVolumeValue * 100;
	SaveAudioInfos();	
}
void UGameMenuAudioSettingsWidget::DialoguesSliderChanged(float Value)
{
	SetDialoguesVolumeValue(FText::FromString(FString::FromInt(FMath::FloorToInt(Value))));
	DialoguesSlider->SetValue(Value);
	const float NewVolumeValue = Value / (DialoguesSlider->MaxValue - DialoguesSlider->MinValue);
	if (DialoguesProgrBar) DialoguesProgrBar->SetPercent(NewVolumeValue);
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, DialoguesSoundClass, NewVolumeValue);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);

	SavedGame->DialoguesVolumeValue = NewVolumeValue * 100;
	SaveAudioInfos();	
}
