// Fill out your copyright notice in the Description page of Project Settings.

#include "Brick.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

#include "Ball.h"

// Sets default values
ABrick::ABrick()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));
	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(25.0f, 10.0f, 10.0f));

	RootComponent = Box_Collision;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnOverlapBegin);
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABrick::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
							UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
							bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->ActorHasTag("Ball"))
	{
		ABall *Ball = Cast<ABall>(OtherActor);

		FVector BallVelocity = Ball->GetVelocity();
		BallVelocity *= (SpeedModifier - 1.0f);

		Ball->GetBall()->SetPhysicsLinearVelocity(BallVelocity, true);

		FTimerHandle DestroyTimer;
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &ABrick::DestroyBrick, 0.01f, false);
	}
}

void ABrick::DestroyBrick()
{
	this->Destroy();
}