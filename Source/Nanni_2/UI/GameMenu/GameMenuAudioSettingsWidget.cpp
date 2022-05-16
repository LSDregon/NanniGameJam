// Copyright © 2022 Last Second


#include "GameMenuAudioSettingsWidget.h"


bool UGameMenuAudioSettingsWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!GlobalSlider || !MusicSlider || !EffectsSlider || !EnviromentSlider || !DialoguesSlider)
		{
			return false;
		}
		
		GlobalText = FText::FromString("50");
		MusicText = FText::FromString("50");
		EffectsText = FText::FromString("50");
		EnviromentText = FText::FromString("50");
		DialoguesText = FText::FromString("50");
		
		if (GlobalSlider) GlobalSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::GlobalSliderChanged);
		if (MusicSlider) MusicSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::MusicSliderChanged);
		if (EffectsSlider) EffectsSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::EffectsSliderChanged);
		if (EnviromentSlider) EnviromentSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::EnviromentSliderChanged);
		if (DialoguesSlider) DialoguesSlider->OnValueChanged.AddDynamic(this, &UGameMenuAudioSettingsWidget::DialoguesSliderChanged);
		return true;
	}
	return false;
}

void UGameMenuAudioSettingsWidget::GlobalSliderChanged(float Value)
{
	SetGlobalVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
}
void UGameMenuAudioSettingsWidget::MusicSliderChanged(float Value)
{
	SetMusicVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
}
void UGameMenuAudioSettingsWidget::EffectsSliderChanged(float Value)
{
	SetEffectsVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
}
void UGameMenuAudioSettingsWidget::EnviromentSliderChanged(float Value)
{
	SetEnviromentVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
}
void UGameMenuAudioSettingsWidget::DialoguesSliderChanged(float Value)
{
	SetDialoguesVolumeValue(FText::FromString(FString::SanitizeFloat(Value)));
}
