// Fill out your copyright notice in the Description page of Project Settings.


#include "FFF_GameMode2.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "AIShooterController.h"
#include "ShooterChar.h"
void AFFF_GameMode2::PawnKilled(APawn* PawnKilled) {
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	if (PlayerController != nullptr) {
		EndGame(false);
	}

	for (AAIShooterController* Controller : TActorRange<AAIShooterController>(GetWorld())) {
		if (Controller != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Enemies Still Alive"));
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemies Are Dead"));
	EndGame(true);
}

void AFFF_GameMode2::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);

	}
}
