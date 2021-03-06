// Copyright © 2022 Last Second


#include "LaserEmitter.h"

#include "LaserLine.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Nanni_2/GeneralComponents/SensorComponent.h"

// Sets default values
ALaserEmitter::ALaserEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bIsActive = true;
	
	LaserEmitterMesh = CreateDefaultSubobject<UStaticMeshComponent>("LaserEmitterMesh");
	LaserEmitterMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);

	SetRootComponent(LaserEmitterMesh);
	
	LaserEmitterSource = CreateDefaultSubobject<UArrowComponent>("LaserEmitterSource");
	LaserEmitterSource->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	LaserEmitterSource->SetupAttachment(LaserEmitterMesh);

	LaserColor = FColor::Orange;
}

void ALaserEmitter::SetEmitterState(bool Active)
{
	bIsActive = Active;
	if (!Active)
	{
		Lasers.Empty();
	}
}

// Called when the game starts or when spawned
void ALaserEmitter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALaserEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Set Time to delay the interval
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALaserEmitter::CastLaserTraceManager, 1.0f,  true);
	if (bIsActive)
	{
		CastLaserTrace(LaserEmitterSource->GetComponentLocation(), LaserEmitterSource->GetForwardVector(), CastDistanceValue);
	}
	else if (!bIsActive && !Lasers.IsEmpty())
	{
		DeactivateUnusedLaserFX(0);
	}
}

void ALaserEmitter::CastLaserTrace(const FVector CastOrigin, const FVector CastDirection, const float CastDistance)
{
	//Saving Base vector values
	FVector NextOrigin = CastOrigin;
	FVector NextDirection = CastDirection;
	
	FVector TraceStart;
	FVector TraceEnd;
	
	FVector ImpactPoint;
	
	bool bContinueTracing = true;
	bool bHasImpactPoint = true;
	int32 cCurrentJumpNumber = 0;
	
	//check if has to continue or if he reached the max number of mirror jump
	while (bContinueTracing && cCurrentJumpNumber < MaxJumpNumber)
	{
		bContinueTracing = LineTraceManager(TraceStart, TraceEnd, NextOrigin, NextDirection, ImpactPoint, cCurrentJumpNumber,
		                                    bHasImpactPoint, CastDistance);
		LaserFXManager(TraceStart, TraceEnd, ImpactPoint, NextDirection.Rotation(), bHasImpactPoint, cCurrentJumpNumber);
		cCurrentJumpNumber++;
	}
	//Deactivate all unused LaserFX
	DeactivateUnusedLaserFX(cCurrentJumpNumber);
}


void ALaserEmitter::DeactivateUnusedLaserFX(int32 NumberLaserToKeep)
{
	TArray<int32> KeyToRemove = TArray<int32>();
	for (const TTuple<int32, ALaserLine*> LaserTuple : Lasers)
	{
		if (LaserTuple.Key >= NumberLaserToKeep)
		{
			LaserTuple.Value->Destroy();
			KeyToRemove.Add(LaserTuple.Key);
		}
	}
	for (const int32 IndexToRemove : KeyToRemove)
	{
		Lasers.Remove(IndexToRemove);
	}
}
bool ALaserEmitter::LineTraceManager(FVector& TraceStart, FVector& TraceEnd, FVector& NextOrigin, FVector& NextDirection,
                                     FVector& ImpactPoint, int32& cCurrentJumpNumber, bool& bHasImpactPoint, float CastDistance)
{
	//calc The start point and the end point
	TraceStart = NextOrigin;
	TraceEnd = NextOrigin + NextDirection * CastDistance;
	ImpactPoint = NextOrigin;
		
	FHitResult TraceHit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	bool bHasNextLineTrace = true;
	bHasImpactPoint = false;
	
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd,
											  UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, IgnoreActors,
											  (DrawDebugLine) ? EDrawDebugTrace::Type::ForDuration : EDrawDebugTrace::Type::None,
											  TraceHit, true, FLinearColor::Red, FLinearColor::Green, 1))
	{
		bHasImpactPoint = true;
		ImpactPoint = TraceHit.ImpactPoint;
		
		//Get the Material of the Hit surface
		int32 SectionIndex;
		
		//check if it's a hit
		if (UMaterialInstance* HitMaterial = Cast<UMaterialInstance>(
			TraceHit.GetComponent()->GetMaterialFromCollisionFaceIndex(TraceHit.FaceIndex, SectionIndex)))
		{
			//check if has a Sesnor component
			if (USensorComponent* Sensor = Cast<USensorComponent>(TraceHit.GetComponent()))
			{
				Sensor->LaserDetected.Broadcast();
			}
			//check if it's a mirror material  
			if (HitMaterial == MirrorMaterial)
			{
				//reset the Root origin of the new impacted point and direction of the new jump trace
				NextOrigin = TraceHit.ImpactPoint;
				NextDirection = UKismetMathLibrary::MirrorVectorByNormal(NextDirection, TraceHit.ImpactNormal);
			}
			else
			{
				bHasNextLineTrace = false;
			}
		}
		else
		{
			//NiagaraLaser->SetVectorParameter(UKismetStringLibrary::Conv_StringToName("LaserEnd"), TraceEnd);
			bHasNextLineTrace = false;
		}
	}
	else
	{
		bHasImpactPoint = false;
		bHasNextLineTrace = false;
	}
	return bHasNextLineTrace;
}

void ALaserEmitter::LaserFXManager(FVector TraceStart, FVector TraceEnd, FVector ImpactPoint, FRotator NextDirectionRotation,
                                   bool bHasImpactPoint, int32 cCurrentJumpNumber)
{
	//Reuse already present LaserFX actor
	if (ALaserLine** ExistingLaserDoublePointer = Lasers.Find(cCurrentJumpNumber))
	{
		if (ALaserLine* ExistingLaser = *ExistingLaserDoublePointer)
		{
			ExistingLaser->SetActorLocation(TraceStart);
			ExistingLaser->SetLaser(bHasImpactPoint ? ImpactPoint : TraceEnd);
			ExistingLaser->SetActiveStateLaser(true);
			ExistingLaser->SetActiveStateLaserImpact(bHasImpactPoint);
			if (bHasImpactPoint)
			{
				ExistingLaser->SetLaserImpact(ImpactPoint);
			}
		}
	}
	//Create a new LaserFX actor
	else if (LaserLineClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		if (ALaserLine* Laser = GetWorld()->SpawnActor<ALaserLine>(LaserLineClass, TraceStart, NextDirectionRotation,
					   SpawnParameters))
		{
			Laser->SetColorLaser(LaserColor);
			Laser->SetColorLaserImpact(LaserColor);
			Laser->SetLaser(bHasImpactPoint ? ImpactPoint : TraceEnd);
			Laser->SetActiveStateLaserImpact(bHasImpactPoint);
			if (bHasImpactPoint)
			{
				Laser->SetLaserImpact(ImpactPoint);
			}
			Lasers.Add(cCurrentJumpNumber, Laser);
		}
	}
}

