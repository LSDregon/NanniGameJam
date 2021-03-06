// Copyright © 2022 Last Second

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserEmitter.generated.h"

class ALaserLine;
class UNiagaraSystem;
class UArrowComponent;
UCLASS()
class NANNI_2_API ALaserEmitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserEmitter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LaserEmitterMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UArrowComponent> LaserEmitterSource;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ALaserLine> LaserLineClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> MirrorMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor LaserColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool DrawDebugLine;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxJumpNumber;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CastDistanceValue;

	UPROPERTY(VisibleAnywhere)
	TMap<int32, ALaserLine*> Lasers = TMap<int32, ALaserLine*>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FTimerHandle TimerHandle;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SetEmitterState(bool Active);
	UFUNCTION(BlueprintCallable)
	void DeactivateUnusedLaserFX(int32 NumberLaserToKeep);
	UFUNCTION(BlueprintCallable)
	void CastLaserTrace(const FVector CastOrigin, const FVector CastDirection, const float CastDistance);
	UFUNCTION(BlueprintCallable)
	bool LineTraceManager(FVector& TraceStart, FVector& TraceEnd, FVector& NextOrigin, FVector& NextDirection, FVector& ImpactPoint,
	                      int32& cCurrentJumpNumber, bool& bHasImpactPoint, float CastDistance);
	UFUNCTION(BlueprintCallable)
	void LaserFXManager(FVector TraceStart, FVector TraceEnd, FVector ImpactPoint, FRotator NextDirectionRotation,
	                    bool bHasImpactPoint, int32 cCurrentJumpNumber);
	
};
