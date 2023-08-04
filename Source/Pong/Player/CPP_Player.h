// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_Player.generated.h"

UCLASS()
class PONG_API ACPP_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_Player();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetPaddleSpeed() { return PaddleSpeed ; }

	UStaticMeshComponent* GetPaddelStaticMeshComponent() const { return PaddleStaticMeshComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Paddle Static Mesh Component*/
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PaddleStaticMeshComponent;

	/** Padle Box Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PongPlayer|Components")
	class UBoxComponent* PaddleBoxComponent;

	/** Camera boom */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Paddle Speed */
	UPROPERTY(EditAnywhere)
	float PaddleSpeed;

};
