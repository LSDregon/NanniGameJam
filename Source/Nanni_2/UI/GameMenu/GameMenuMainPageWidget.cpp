// Copyright © 2022 Last Second


#include "GameMenuMainPageWidget.h"

#include "GameMenuOptionsWidget.h"
#include "GameMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/Characters/MainCharacter/MainPlayerController.h"


bool UGameMenuMainPageWidget::Initialize()
{
	if(Super::Initialize())
	{
		if (!ResumeButton || !OptionsButton || !QuitButton)
		{
			return false;
		}
		ConfirmChoiceText = FText::FromString("Are you sure you want to quit the Game?");
		if (ResumeButton) ResumeButton->OnClicked.AddDynamic(this, &UGameMenuMainPageWidget::ResumeSelected);
		if (OptionsButton) OptionsButton->OnClicked.AddDynamic(this, &UGameMenuMainPageWidget::OptionsSelected);
		if (CreditsButton) CreditsButton->OnClicked.AddDynamic(this, &UGameMenuMainPageWidget::CreditsSelected);
		if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UGameMenuMainPageWidget::QuitSelected);
		
		return true;
	}
	return false;
}

void UGameMenuMainPageWidget::ResumeSelected()
{
	if (IsInGameMenu)
	{
		const UWorld* World = GetWorld();
		AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(MainPlayerController->GetCharacter());

		if (MainPlayerController && MainCharacter)
		{
			if (InGameMenuReference) InGameMenuReference->RemoveFromParent();
			
			MainCharacter->EnableInput(MainPlayerController);
			MainPlayerController->SetShowMouseCursor(false);
			MainPlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
	else
	{
		CallOpenLevel();
	}
}
void UGameMenuMainPageWidget::OptionsSelected()
{
	if (OptionMenu)
	{
		OptionMenu->FadeInAnimationExec();
		OptionMenu->SetVisibility(ESlateVisibility::Visible);
		OptionMenu->ActualOptionIdSelected = -1;
		OptionMenu->bIsFocusable = true;
	}
	if (BackButton)
	{
		if (InGameMenuReference)
		{
			InGameMenuReference->BackFadeInAnimationExec();
		}
		BackButton->SetVisibility(ESlateVisibility::Visible);
		BackButton->IsFocusable = true;
	}
	FadeOutAnimationExec();
	bIsFocusable = false;
}

void UGameMenuMainPageWidget::CreditsSelected()
{
	if (Credits)
	{
		Credits->FadeInAnimationExec();
		Credits->SetVisibility(ESlateVisibility::Visible);
		Credits->bIsFocusable = true;
	}
	if (BackButton)
	{
		if (InGameMenuReference)
		{
			InGameMenuReference->BackFadeInAnimationExec();
		}
		BackButton->SetVisibility(ESlateVisibility::Visible);
		BackButton->IsFocusable = true;
	}
	FadeOutAnimationExec();
	bIsFocusable = false;
}

void UGameMenuMainPageWidget::QuitSelected()
{
	const UWorld* World = GetWorld();
	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(MainPlayerController->GetCharacter());
	WBPConfirmChoice = CreateWidget<UConfirmChoiceWidget>(MainPlayerController, ConfirmChoiceWidget);

	WBPConfirmChoice->SetChoiceText(ConfirmChoiceText);
	WBPConfirmChoice->OnYesButtonClicked.AddDynamic(this, &UGameMenuMainPageWidget::YesSelected);
	WBPConfirmChoice->OnNoButtonClicked.AddDynamic(this, &UGameMenuMainPageWidget::NoSelected);
	WBPConfirmChoice->AddToViewport();
}

void UGameMenuMainPageWidget::YesSelected()
{
	const UWorld* World = GetWorld();
	AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	UKismetSystemLibrary::QuitGame(World, MainPlayerController, EQuitPreference::Type::Quit, false);
}
void UGameMenuMainPageWidget::NoSelected()
{
	WBPConfirmChoice->RemoveFromParent();
}
