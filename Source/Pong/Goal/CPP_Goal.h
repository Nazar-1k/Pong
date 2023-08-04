// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Goal.generated.h"

UCLASS()
class PONG_API ACPP_Goal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_Goal();

private:
	/** Padle Box Component */
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;


};
