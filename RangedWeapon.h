// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangedWeapon.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API ARangedWeapon : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
		float MaxRange = 100;
	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere)
		float Damage = 10.0f;
	UPROPERTY(EditAnywhere)
		USoundBase* MuzzleSounds;
	UPROPERTY(EditAnywhere)
		USoundBase* ImpactSounds;

public:	
	// Sets default values for this actor's properties
	ARangedWeapon();
	void PullTrigger();
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
