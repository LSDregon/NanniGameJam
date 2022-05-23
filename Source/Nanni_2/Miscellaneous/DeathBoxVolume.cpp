// Copyright © 2022 Last Second


#include "DeathBoxVolume.h"

#include "Components/ShapeComponent.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"

void ADeathBoxVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetCollisionComponent())
	{
		GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADeathBoxVolume::DeathEvent);
	}
	
}

void ADeathBoxVolume::DeathEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
					bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		MainCharacter->SetActorLocation(MainCharacter->RespawnPoint);
	}	
}

