// Copyright © 2022 Last Second


#include "GenericButton.h"

#include "Nanni_2/GeneralComponents/EventListenerComponent.h"
#include "Nanni_2/GeneralComponents/InteractionComponent.h"

// Sets default values
AGenericButton::AGenericButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(Scene);
	
	OpeningMesh = CreateDefaultSubobject<UStaticMeshComponent>("OpeningMesh");
	OpeningMesh->SetupAttachment(Scene);
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InteractionComponent->SetupAttachment(OpeningMesh);

	EventListener = CreateDefaultSubobject<UEventListenerComponent>(TEXT("Event Listener"));
	if (EventListener) this->AddOwnedComponent(EventListener);

	bIsAlwaysInteractable = false;
}

// Called when the game starts or when spawned
void AGenericButton::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionComponent->OnInteract.AddDynamic(this, &AGenericButton::TriggerTaskCompleted);
}

// Called every frame
void AGenericButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (EventListener->bIsInAEventTask && !EventListener->bIsActorEnable && !(EventListener->bIsTaskDone && bIsAlwaysInteractable))
	{
		OpeningMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		OpeningMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	}

}

void AGenericButton::TriggerTaskCompleted(AMainCharacter* Character)
{
	EventListener->TaskCompleted(this);
}