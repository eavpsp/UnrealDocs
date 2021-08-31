// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIShooterController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AAIShooterController : public AAIController
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;
	void SetDead(bool bIsDead);
private:
	bool bPawnLoaded = false;
	bool bPawnSet = false;
	UPROPERTY(VisibleAnywhere)
	bool bDead = false;
	UPROPERTY(VisibleAnywhere)
	APawn* ThisPawn;
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
