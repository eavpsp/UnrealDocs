// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FFF_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AFFF_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void PawnKilled(APawn* PawnKilled);

};
