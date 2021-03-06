// Copyright © 2022 Last Second


#include "ConfirmChoiceWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UConfirmChoiceWidget::Initialize()
{
	if(Super::Initialize())	if (!YesButton || !NoButton) return false;
	if (YesButton) YesButton->OnClicked.AddDynamic(this, &UConfirmChoiceWidget::YesButtonClicked);
	if (NoButton) NoButton->OnClicked.AddDynamic(this, &UConfirmChoiceWidget::NoButtonClicked);
	return false;
}

void UConfirmChoiceWidget::YesButtonClicked()
{
	OnYesButtonClicked.Broadcast();
}
void UConfirmChoiceWidget::NoButtonClicked()
{
	OnNoButtonClicked.Broadcast();
}

void UConfirmChoiceWidget::SetChoiceText(FText NewText) const
{
	ChoiceText->SetText(NewText);
}
