// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterChar.h"
UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot Player");
}
EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr) {
		return EBTNodeResult::Failed;
	}
	AShooterChar* Char = Cast<AShooterChar>(OwnerComp.GetAIOwner()->GetPawn());
	if (Char == nullptr) {
		 
			return EBTNodeResult::Failed;

	}
	Char->Shoot();
	return EBTNodeResult::Succeeded;

}