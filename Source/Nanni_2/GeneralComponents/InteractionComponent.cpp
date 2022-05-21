// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "GameFramework/Actor.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/UI/InteractionWidget.h"

UInteractionComponent::UInteractionComponent() 
{
    UActorComponent::SetComponentTickEnabled(false);

    InteractionTime = 1.f;
    InteractionDistance = 200.f;
    InteractionObjectName = FText::FromString("Object Name");
    InteractionObjectAction = FText::FromString("Object Action");

    Space = EWidgetSpace::Screen;
    DrawSize = FIntPoint(this->GetDrawSize().X,this->GetDrawSize().Y);
    bDrawAtDesiredSize = true;
    IsInteractionActive = true;

    UActorComponent::SetActive(true);
    SetHiddenInGame(true);

}

void UInteractionComponent::SetInteractableNameText(const FText& NewNameText) 
{
    InteractionObjectName = NewNameText;
    RefreshWidget();
}

void UInteractionComponent::SetInteractableActionText(const FText& NewActionText) 
{
    InteractionObjectAction = NewActionText;
    RefreshWidget();
}

void UInteractionComponent::BeginFocus(AMainCharacter* Character) 
{
    if (!IsActive() || !GetOwner() || !Character)
    {
        return;
    }
    OnBeginFocus.Broadcast(Character);
    SetHiddenInGame(false);

    TArray<UPrimitiveComponent*> PrimitiveComponents;
    GetOwner()->GetComponents<UPrimitiveComponent>(PrimitiveComponents, true);

    for (UPrimitiveComponent* VisualComp: PrimitiveComponents)
    {
        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
        {
            Prim->SetRenderCustomDepth(true);
        }
    }

    RefreshWidget();
}

void UInteractionComponent::EndFocus(AMainCharacter* Character) 
{
    OnEndFocus.Broadcast(Character);

    SetHiddenInGame(true);

    TArray<UPrimitiveComponent*> PrimitiveComponents;
    GetOwner()->GetComponents<UPrimitiveComponent>(PrimitiveComponents, true);

    for (UPrimitiveComponent* VisualComp : PrimitiveComponents)
    {
        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
        {
            Prim->SetRenderCustomDepth(false);
        }
    }
}

void UInteractionComponent::BeginInteract(AMainCharacter* Character) 
{
    if (Character)
    {
        Interactor = Character;
        OnBeginInteract.Broadcast(Character);
    }
}

void UInteractionComponent::EndInteract(AMainCharacter* Character) 
{
    if (Character)
    {
        Interactor = nullptr;
        OnEndInteract.Broadcast(Character);
    }
}

void UInteractionComponent::Interact(AMainCharacter* Character) const
{
    if (Character)
    {
        OnInteract.Broadcast(Character);
    }    
}

float UInteractionComponent::GetInteractPercentage() const
{
    if (Interactor && Interactor->IsInteracting())
    {
        return 1.f - FMath::Abs(Interactor->GetRemainingInteractTime() / InteractionTime);
    }

    return 0.f;
}

void UInteractionComponent::RefreshWidget()
{
    if(UInteractionWidget* InteractionWidget = Cast<UInteractionWidget>(GetUserWidgetObject()))
    {
        InteractionWidget->UpdateInteractionWidget(this);
    }
}


void UInteractionComponent::Deactivate() 
{
    if (Interactor)
    {
        EndFocus(Interactor);
        EndInteract(Interactor);
    }
    Interactor = nullptr;
}