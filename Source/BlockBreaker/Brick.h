// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

class UBoxComponent;

UCLASS()
class BLOCKBREAKER_API ABrick : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent *SM_Brick;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent *Box_Collision;

	float SpeedModifier = 1.01f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
						UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult &SweepResult);

	void DestroyBrick();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
