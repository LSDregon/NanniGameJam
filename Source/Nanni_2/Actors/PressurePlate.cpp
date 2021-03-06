// Copyright © 2022 Last Second


#include "PressurePlate.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"
#include "Nanni_2/Miscellaneous/TriggerBoxCustom.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshPressure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pressure Plate"));
	SetRootComponent(GetRootComponent());

	ActivatedMaterialIndex = 1;
}

void APressurePlate::ActionToExecute(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		if (StaticMeshPressure) StaticMeshPressure->SetMaterial(ActivatedMaterialIndex, ActivatedMaterial);
		if (ATriggerBoxCustom* Trigger = Cast<ATriggerBoxCustom>(OverlappedActor))
			Trigger->OnActorBeginOverlap.RemoveDynamic(this, &APressurePlate::ActionToExecute);
		PlaySound();
	}
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ChildActorList = TArray<AActor*>();
	GetAttachedActors(ChildActorList);
	for (AActor* ChildActor : ChildActorList)
	{
		if (ChildActor && UKismetMathLibrary::ClassIsChildOf(ChildActor->GetClass(), ATriggerBoxCustom::StaticClass()))
		{
			if (ATriggerBoxCustom* TriggerArea = Cast<ATriggerBoxCustom>(ChildActor))
			{
				TriggerArea->OnActorBeginOverlap.AddDynamic(this, &APressurePlate::ActionToExecute);
			}
		}
	}
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

