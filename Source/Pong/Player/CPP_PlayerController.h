// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_PlayerController.generated.h"

class ACPP_Player;
UCLASS()
class PONG_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPP_PlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	
	ACPP_Player* Player;

	void MoveRightLeft(float AxisValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRightLeft(float AxisValue, float PaddleSpeed);
	bool Server_MoveRightLeft_Validate(float AxisValue, float PaddleSpeed);
	void Server_MoveRightLeft_Implementation(float AxisValue, float PaddleSpeed);

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_MoveRightLeft(float AxisValue, float PaddleSpeed);
	bool Multi_MoveRightLeft_Validate(float AxisValue, float PaddleSpeed);
	void Multi_MoveRightLeft_Implementation(float AxisValue, float PaddleSpeed);
};
