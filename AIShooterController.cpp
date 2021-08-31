// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterChar.h"
#include "ShooterPlayerController.h"
void AAIShooterController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		ThisPawn = GetPawn();
		bPawnLoaded = true;
	}
	
}
void AAIShooterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(bPawnLoaded && !bPawnSet && ThisPawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got Owner!"));
		FVector AIPos = ThisPawn->GetActorLocation();
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartPos"), AIPos);
		bPawnSet = true;
	}

	
	

}
void AAIShooterController::SetDead(bool bIsDead) {
	bDead = bIsDead;
}
bool AAIShooterController::IsDead() const {
	if (ThisPawn == nullptr) {
		return true;
	}
	else {
		return false;
	}
	return bDead;
}

