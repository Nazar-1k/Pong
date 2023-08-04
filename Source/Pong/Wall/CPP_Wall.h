// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Wall.generated.h"

UCLASS()
class PONG_API ACPP_Wall : public AActor
{
	GENERATED_BODY()
	

public:
	
	ACPP_Wall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* WallStaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* WallBoxComponent;

};
