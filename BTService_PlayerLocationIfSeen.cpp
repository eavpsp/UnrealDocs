// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include"AIShooterController.h"
#include "ShooterChar.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen() {
	NodeName = TEXT("Find Player");
}
void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIShooterController* AIPlayer = Cast<AAIShooterController>(OwnerComp.GetAIOwner());
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AShooterChar* PlayerShooter = Cast<AShooterChar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (AIPlayer == nullptr) {
		return;
	}
	if (PlayerPawn == nullptr) {
		return;
	}
	if (PlayerShooter == nullptr) {
		return;
	}
	if (AIPlayer->LineOfSightTo(PlayerPawn) && !PlayerShooter->IsDead()) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	}
	
}

