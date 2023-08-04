// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Ball.generated.h"

UCLASS()
class PONG_API ACPP_Ball : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ACPP_Ball();

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_BallVelocity();

	void Restart();


	FTimerHandle GetTimerHandleForSpawn() { return TimerHandleForSpawn; }
	float GetTimeForSpawn() { return TimeForSpawn; }
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPaddleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Reflect(const FHitResult& Hit, const FVector Velocity);
	bool Server_Reflect_Validate(const FHitResult& Hit, const FVector Velocity);
	void Server_Reflect_Implementation(const FHitResult& Hit, const FVector Velocity);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CountRedGoal;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CountBlueGoal;

private:

	UPROPERTY(VisibleAnywhere, Category = "PongBall")
	UStaticMeshComponent* BallStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "PongBall")
	class USphereComponent* BallSphereComponent;

	UPROPERTY(EditAnywhere, Category = "Ball Settings")
	float BallSpeed;

	UPROPERTY(Replicated)
	FVector BallVelocity;

	bool bGameOver = true;

	FTimerHandle TimerHandleForSpawn;
	float TimeForSpawn = 3.0f;
};
