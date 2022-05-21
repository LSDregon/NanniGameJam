// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Nanni_2/GeneralComponents/InteractionComponent.h"

bool UInteractionWidget::Initialize()
{
    if (!Super::Initialize())
    {
        return false;
    }
    
    CircularMaterialInstanceDynamicInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), CircularMaterialInstance);
    UWidgetBlueprintLibrary::SetBrushResourceToMaterial(CircularBrash, CircularMaterialInstanceDynamicInstance);
    
    return true;
}
void UInteractionWidget::UpdateInteractionWidget(UInteractionComponent* InteractionComponent) 
{
    OwningInteractionComponent = InteractionComponent;
    OnUpdateInteractionWidget();
}


float UInteractionWidget::GetInteractPercent()
{
    if (OwningInteractionComponent)
    {
        return OwningInteractionComponent->GetInteractPercentage();
    }
    return 0;
}

FSlateBrush UInteractionWidget::GetDynamicBrush()
{
    CircularMaterialInstanceDynamicInstance->SetScalarParameterValue(UKismetStringLibrary::Conv_StringToName("FillBar"), GetInteractPercent());
    return CircularBrash;
}
