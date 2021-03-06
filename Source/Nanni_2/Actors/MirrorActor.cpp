// Copyright © 2022 Last Second


#include "MirrorActor.h"

#include "Components/BoxComponent.h"
#include "Nanni_2/Characters/MainCharacter/MainCharacter.h"

// Sets default values
AMirrorActor::AMirrorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MirrorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mirror Mesh");
	SetRootComponent(MirrorMesh);
	
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("Physics Constraint");
	PhysicsConstraint->SetupAttachment(MirrorMesh);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(MirrorMesh);

	PhysicsConstraint->ComponentName1.ComponentName = TEXT("Mirror Mesh");
}

// Called when the game starts or when spawned
void AMirrorActor::BeginPlay()
{
	Super::BeginPlay();

	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMirrorActor::BeginPush);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMirrorActor::EndPush);
	}	
}

void AMirrorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//for (FMyStruct& ChildActorComponent : ChildActorList)
	//{
		//ChildActorComponent.Mesh->SetRelativeTransform(ChildActorComponent.Tran);
	//};
}

void AMirrorActor::BeginPush(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		//UE_LOG(LogTemp, Warning, TEXT("BeginPush"));
		MirrorMesh->SetSimulatePhysics(true);
	}
}

void AMirrorActor::EndPush(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex)
{
	if (Cast<AMainCharacter>(OtherActor))
	{
		//UE_LOG(LogTemp, Warning, TEXT("EndPush"));
		MirrorMesh->SetSimulatePhysics(false);
	}
	
}

