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
		if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UGameMenuMainPageWidget::QuitSelected);
		
		return true;
	}
	return false;
}

void UGameMenuMainPageWidget::ResumeSelected()
{
	if (IsInGameMenu)
	{
		if (InGameMenuReference) InGameMenuReference->RemoveFromParent();
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(LevelToLoadName), false);
	}
}
void UGameMenuMainPageWidget::OptionsSelected()
{
	if (OptionMenu)
	{
		OptionMenu->FadeInAnimationExec();
		// OptionMenu->SetIsEnabled(true);
		OptionMenu->SetVisibility(ESlateVisibility::Visible);
		OptionMenu->bIsFocusable = true;
	}
	if (BackButton)
	{
		if (InGameMenuReference)
		{
			InGameMenuReference->BackFadeInAnimationExec();
		}
		// BackButton->SetIsEnabled(true);
		BackButton->SetVisibility(ESlateVisibility::Visible);
		BackButton->IsFocusable = true;
	}
	FadeOutAnimationExec();
	// SetIsEnabled(false);
	// SetVisibility(ESlateVisibility::Hidden);
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
