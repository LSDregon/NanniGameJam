// Copyright © 2022 Last Second


#include "GameMenuWidget.h"

#include "GameMenuAudioSettingsWidget.h"
#include "GameMenuControlSettingsWidget.h"
#include "GameMenuGameSettingsWidget.h"
#include "GameMenuMainPageWidget.h"
#include "GameMenuOptionsWidget.h"
#include "GameMenuVideoSettingsWidget.h"
#include "Components/Button.h"


bool UGameMenuWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!BackButton)
		{
			return false;
		}
		BackButton->OnClicked.AddDynamic(this, &UGameMenuWidget::BackPageOperation);
		InitializeSections();
		return true;
	}
	return false;
}

void UGameMenuWidget::BackPageOperation()
{
	if (MainPageMenu)		MainPageMenu->SetVisibility(ESlateVisibility::Visible);
	if (BackButton)			BackButton->SetVisibility(ESlateVisibility::Hidden);
	if (OptionMenu)		OptionMenu->SetVisibility(ESlateVisibility::Hidden);
	if (GameSettings)		GameSettings->SetVisibility(ESlateVisibility::Hidden);
	if (VideoSettings)		VideoSettings->SetVisibility(ESlateVisibility::Hidden);
	if (AudioSettings)		AudioSettings->SetVisibility(ESlateVisibility::Hidden);
	if (ControlSettings)	ControlSettings->SetVisibility(ESlateVisibility::Hidden);
}

void UGameMenuWidget::InitializeSections()
{
	if (OptionMenu)
	{
		OptionMenu->GameSettings = GameSettings;
		OptionMenu->VideoSettings = VideoSettings;
		OptionMenu->AudioSettings = AudioSettings;
		OptionMenu->ControlSettings = ControlSettings;
	}
	if (MainPageMenu)
	{
		MainPageMenu->BackButton = BackButton;
		MainPageMenu->OptionMenu = OptionMenu;
		MainPageMenu->InGameMenuReference = this;
	}
}