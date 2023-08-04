// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ACPP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	
	void StartGame();

protected:

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 RequiredLoadedPlayers = 2;

	int32 LoadedPlayersCount = 0;
};