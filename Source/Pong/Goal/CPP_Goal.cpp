// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Goal.h"

#include "Components/BoxComponent.h"

#include "../Ball/CPP_Ball.h"

// Sets default values
ACPP_Goal::ACPP_Goal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComponent->SetupAttachment(RootComponent);
}
