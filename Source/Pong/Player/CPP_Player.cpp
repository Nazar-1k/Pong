// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"

// Sets default values
ACPP_Player::ACPP_Player()
{
	// Create a Root Component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create Paddle
	PaddleStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle"));
	PaddleStaticMeshComponent->SetupAttachment(RootComponent);

	PaddleBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Paddle Box Collision"));
	PaddleBoxComponent->SetupAttachment(PaddleStaticMeshComponent);
	PaddleBoxComponent->SetCollisionProfileName("PhysicsActor");

	// Create a camera booms
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	bReplicates = true;
}

// Called when the game starts or when spawned
void ACPP_Player::BeginPlay()
{

	SetReplicateMovement(true);
	

	Super::BeginPlay();
	
}

