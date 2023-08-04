// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Ball.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "../Player/CPP_Player.h"
#include "../Wall/CPP_Wall.h"
#include "../Goal/CPP_Goal.h"

ACPP_Ball::ACPP_Ball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;

	BallStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Static Mesh"));
	RootComponent = BallStaticMeshComponent;
	BallStaticMeshComponent->SetSimulatePhysics(true);
	BallStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BallStaticMeshComponent->SetEnableGravity(false);
	BallStaticMeshComponent->SetConstraintMode(EDOFMode::XYPlane);

	BallSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	BallSphereComponent->SetupAttachment(BallStaticMeshComponent);
	BallSphereComponent->SetCollisionProfileName("Trigger");

	BallSpeed = 500.f;
}

void ACPP_Ball::Tick(float DeltaTime)
{
	if (bGameOver == false)
	{
		float InterpolationSpeed = 1.0f;
		FVector NewPosition = FMath::VInterpTo(GetActorLocation(), GetActorLocation() + BallVelocity, DeltaTime, InterpolationSpeed);

		SetActorLocation(NewPosition);
	}
	else
	{
		SetActorLocation(FVector::ZeroVector);
		BallVelocity = { 0.0f, 0.0f, 0.0f };
	}
}

void ACPP_Ball::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);

	//Set Start Position and Velocity for Ball
	SetActorLocation(FVector::ZeroVector);

	BallStaticMeshComponent->OnComponentHit.AddDynamic(this, &ACPP_Ball::OnPaddleHit);
	BallStaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Ball::BeginOverlap);
}

void ACPP_Ball::OnPaddleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("PongWall Overlap"));

	ACPP_Player* PongPlayer = Cast<ACPP_Player>(OtherActor);
	ACPP_Wall* PongWall = Cast<ACPP_Wall>(OtherActor);

	if (PongWall || PongPlayer)
	{
		//// Get the normal vector of the hit surface
		//FVector HitNormal = Hit.ImpactNormal;

		//// Reflect the ball's velocity based on the hit normal
		//BallVelocity = BallVelocity - 2 * FVector::DotProduct(BallVelocity, HitNormal) * HitNormal;

		if (!HasAuthority())
		{
			Server_Reflect(Hit);
		}
		else
		{
			Multi_Reflect(Hit);
		}
	}
}

void ACPP_Ball::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPP_Goal* Goal = Cast<ACPP_Goal>(OtherActor);
	if (Goal && !bGameOver)
	{
		bGameOver = true;

		if (Goal->ActorHasTag(FName("Red")))
		{
			CountBlueGoal++;
		}
		else if (Goal->ActorHasTag(FName("Blue")))
		{
			CountRedGoal++;
		}

		GetWorldTimerManager().SetTimer(TimerHandleForSpawn, this, &ACPP_Ball::Restart, TimeForSpawn, false);
	}
}

bool ACPP_Ball::Server_Reflect_Validate(const FHitResult& Hit)
{
	return true;
}

void ACPP_Ball::Server_Reflect_Implementation(const FHitResult& Hit)
{
	Multi_Reflect_Validate(Hit);
}

bool ACPP_Ball::Multi_Reflect_Validate(const FHitResult& Hit)
{
	return true;
}

void ACPP_Ball::Multi_Reflect_Implementation(const FHitResult& Hit)
{
	// Get the normal vector of the hit surface
	FVector HitNormal = Hit.ImpactNormal;

	// Reflect the ball's velocity based on the hit normal
	BallVelocity = BallVelocity - 2 * FVector::DotProduct(BallVelocity, HitNormal) * HitNormal;
}

void ACPP_Ball::Restart()
{
	bGameOver = false;

	// Generate a random direction angle in degrees
	float RandomAngle = FMath::FRandRange(0.0f, 360.0f);

	// Convert the angle to a 2D vector direction
	FVector2D RandomDirection = FVector2D(FMath::Cos(FMath::DegreesToRadians(RandomAngle)), FMath::Sin(FMath::DegreesToRadians(RandomAngle)));

	// Use the random direction to set the BallVelocity (we keep the Z component as 0)
	BallVelocity = FVector(RandomDirection.X * BallSpeed, RandomDirection.Y * BallSpeed, 0.0f);
}

void ACPP_Ball::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ACPP_Ball, BallVelocity);
	DOREPLIFETIME(ACPP_Ball, CountRedGoal);
	DOREPLIFETIME(ACPP_Ball, CountBlueGoal);
	DOREPLIFETIME(ACPP_Ball, bGameOver);
}
