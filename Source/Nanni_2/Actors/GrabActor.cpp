// Copyright © 2022 Last Second


#include "GrabActor.h"

#include "FieldImpactActor.h"
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
	
}

// Called when the game starts or when spawned
void AGrabActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionComponent->OnInteract.AddDynamic(this, &AGrabActor::GrabItem);
	GrabbMesh->OnComponentHit.AddDynamic(this, &AGrabActor::SpawnImpactField);
}

// Called every frame
void AGrabActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrabActor::SpawnImpactField(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const FVector ImpactPoint = Hit.ImpactPoint;
	AFieldImpactActor* ImpactActor = GetWorld()->SpawnActor<AFieldImpactActor>(AFieldImpactActor::StaticClass(), ImpactPoint, NormalImpulse.Rotation());
	ImpactActor->Destroy();
}

void AGrabActor::GrabItem(AMainCharacter* MainCharacter)
{
	if (MainCharacter)
	{
		MainCharacter->GrabbedActorRef = this;
		MainCharacter->GrabbedMesh->SetStaticMesh(GrabbMesh->GetStaticMesh());
		MainCharacter->HasSomthingToThrow = true;
	}
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
}

