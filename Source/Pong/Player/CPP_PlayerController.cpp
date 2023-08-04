// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"

#include "CPP_Player.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ACPP_PlayerController::ACPP_PlayerController()
{
}

void ACPP_PlayerController::BeginPlay()
{
	Player = Cast<ACPP_Player>(GetPawn());

	PrimaryActorTick.bCanEverTick = false;
}

void ACPP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Movement Paddle
	InputComponent->BindAxis("MoveRigtLeft", this, &ACPP_PlayerController::MoveRightLeft);
}

void ACPP_PlayerController::MoveRightLeft(float AxisValue)
{
	if (Player != nullptr && AxisValue != 0.0f)
	{
		float PaddleSpeed = Player->GetPaddleSpeed();

		FVector DeltaLocation = FVector::ZeroVector;
		DeltaLocation.Y = AxisValue * PaddleSpeed * GetWorld()->DeltaTimeSeconds;

		Player->GetPaddelStaticMeshComponent()->AddLocalOffset(DeltaLocation, true);

		if (!IsLocalController())
		{
			Server_MoveRightLeft(AxisValue, PaddleSpeed);
		}
		else
		{
			Multi_MoveRightLeft(AxisValue, PaddleSpeed);
		}
	}
}

bool ACPP_PlayerController::Server_MoveRightLeft_Validate(float AxisValue, float PaddleSpeed)
{
	return false;
}

void ACPP_PlayerController::Server_MoveRightLeft_Implementation(float AxisValue, float PaddleSpeed)
{
	Multi_MoveRightLeft(AxisValue, PaddleSpeed);
}

bool ACPP_PlayerController::Multi_MoveRightLeft_Validate(float AxisValue, float PaddleSpeed)
{
	return true;
}

void ACPP_PlayerController::Multi_MoveRightLeft_Implementation(float AxisValue, float PaddleSpeed)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.Y = AxisValue * PaddleSpeed * GetWorld()->DeltaTimeSeconds;

	Player->GetPaddelStaticMeshComponent()->AddLocalOffset(DeltaLocation, true);

}


