// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_GameMode.h"

#include "GameFramework/PlayerState.h"

void ACPP_GameMode::StartGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Start!!!"));
}

void ACPP_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	LoadedPlayersCount++;

	// Check if enough players have loaded to start the game
	if (LoadedPlayersCount >= RequiredLoadedPlayers)
	{
		StartGame();
	}
	else
	{
		// Display the loading message on the screen
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Waiting All Player... \n Count of Downloaded players :") + FString::FromInt(LoadedPlayersCount));
	}
}
