// Copyright © 2022 Last Second


#include "GrabActor.h"

#include "FieldImpactActor.h"
#include "Nanni_2/GeneralComponents/EventListenerComponent.h"
#include "Nanni_2/GeneralComponents/InteractionComponent.h"

// Sets default values
AGrabActor::AGrabActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GrabbMesh = CreateDefaultSubobject<UStaticMeshComponent>("GrabMesh");
	RootComponent = GrabbMesh;
	
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InteractionComponent->SetupAttachment(GrabbMesh);
	
	EventListener = CreateDefaultSubobject<UEventListenerComponent>(TEXT("Event Listener"));
	if (EventListener) this->AddOwnedComponent(EventListener);

	bIsAlwaysInteractable = true;
	MinZ_BeforeRespawn = -1000;
}

void AGrabActor::SetGrabActor(AGrabActor* RefActor)
{
	EventListener->EventManager = RefActor->EventListener->EventManager;
	EventListener->PositionInTaskList = RefActor->EventListener->PositionInTaskList;
	EventListener->SetIsActorEnable(RefActor->EventListener->IsIsActorEnable());
	EventListener->SetIsTaskDone(RefActor->EventListener->IsIsTaskDone());
	EventListener->SetIsInAEventTask(RefActor->EventListener->IsIsInAEventTask());
	
	InteractionComponent->SetInteractableActionText(RefActor->InteractionComponent->InteractionObjectAction);
	InteractionComponent->SetInteractableNameText(RefActor->InteractionComponent->InteractionObjectName);
	InteractionComponent->InteractionTime = RefActor->InteractionComponent->InteractionTime;
	InteractionComponent->InteractionDistance = RefActor->InteractionComponent->InteractionDistance;
	InteractionComponent->IsInteractionActive = RefActor->InteractionComponent->IsInteractionActive;
	InteractionComponent->Interactor = RefActor->InteractionComponent->Interactor;
	InteractionComponent->SetWidgetClass(RefActor->InteractionComponent->GetWidgetClass());

	OriginalLocation = RefActor->OriginalLocation;
}

// Called when the game starts or when spawned
void AGrabActor::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetActorTransform();

	GrabbMesh->SetSimulatePhysics(false);
	
	InteractionComponent->OnInteract.AddDynamic(this, &AGrabActor::GrabItem);
	InteractionComponent->OnInteract.AddDynamic(this, &AGrabActor::TriggerTaskCompleted);
	GrabbMesh->OnComponentHit.AddDynamic(this, &AGrabActor::SpawnImpactField);

}

// Called every frame
void AGrabActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
	if (EventListener->bIsInAEventTask && !EventListener->bIsActorEnable && !(EventListener->bIsTaskDone && bIsAlwaysInteractable))
	{
		GrabbMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	}
	else
	{
		GrabbMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	}
	if (GetActorLocation().Z < MinZ_BeforeRespawn)
	{
		SetActorTransform(OriginalLocation);
		GrabbMesh->SetSimulatePhysics(false);
	}
}

void AGrabActor::SpawnImpactField(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HitActor || HitActor != OtherActor)
	{
		const FVector ImpactPoint = Hit.ImpactPoint;
		AFieldImpactActor* ImpactActor = GetWorld()->SpawnActor<AFieldImpactActor>(AFieldImpactActor::StaticClass(), ImpactPoint, NormalImpulse.Rotation());
		ImpactActor->Explode();
		ImpactActor->Destroy();
	}
}

void AGrabActor::GrabItem(AMainCharacter* MainCharacter)
{
	if (MainCharacter)
	{
		MainCharacter->GrabbedActorRef = this;
		MainCharacter->GrabbedMesh->SetStaticMesh(GrabbMesh->GetStaticMesh());
		MainCharacter->GrabbedMesh->SetMaterial(0, GrabbMesh->GetMaterial(0));
		MainCharacter->HasSomthingToThrow = true;
	}
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

void AGrabActor::TriggerTaskCompleted(AMainCharacter* Character)
{
	EventListener->TaskCompleted(this);
}

