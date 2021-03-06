// Copyright © 2022 Last Second


#include "GameMenuControlSettingsWidget.h"

#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/Framework/MainGameInstance.h"

bool UGameMenuControlSettingsWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!SensibilitySlider) return false;
		
		SensibilityText = FText::FromString("100");
		
		if (SensibilitySlider) SensibilitySlider->OnValueChanged.AddDynamic(this, &UGameMenuControlSettingsWidget::SensibilitySliderChanged);

		return InitializeValuesFromSave();
	}
	return false;
}

bool UGameMenuControlSettingsWidget::SaveSensibilityInfos()
{
	UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!MainGameInstance)
	{
		return false;
	}
	return MainGameInstance->SaveSaveGameSlot(SavedGame);
}


bool UGameMenuControlSettingsWidget::InitializeValuesFromSave()
{
	UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!MainGameInstance)
	{
		return false;
	}

	SavedGame = MainGameInstance->LoadSaveGameSlot();
	
	SensibilitySliderChanged(SavedGame->MouseSensitivity);

	return true;
}

void UGameMenuControlSettingsWidget::SensibilitySliderChanged(float Value)
{
	SetSensibilityValue(FText::FromString(FString::FromInt(FMath::FloorToInt(Value))));
	SensibilitySlider->SetValue(Value);
	const float NewVolumeValue = Value / (SensibilitySlider->MaxValue - SensibilitySlider->MinValue);
	if (SensibilityProgrBar) SensibilityProgrBar->SetPercent(NewVolumeValue);

	if(AMainCharacter* MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		MainCharacter->MouseSensitivity = NewVolumeValue;
	}
	
	SavedGame->MouseSensitivity = NewVolumeValue * 100;
	SaveSensibilityInfos();
}