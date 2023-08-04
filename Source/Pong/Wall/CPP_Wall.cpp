// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Wall.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACPP_Wall::ACPP_Wall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WallStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Static Mesh"));
	WallStaticMeshComponent->SetupAttachment(RootComponent);

	WallBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall Box Collision"));
	WallBoxComponent->SetupAttachment(WallStaticMeshComponent);
	WallBoxComponent->SetCollisionProfileName("PhysicsActor");
}

// Called when the game starts or when spawned
void ACPP_Wall::BeginPlay()
{
	Super::BeginPlay();
	
}

