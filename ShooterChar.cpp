// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterChar.h"
#include "RangedWeapon.h"
#include "Components/CapsuleComponent.h"
#include "ThirdPersonShooterGameModeBase.h"
// Sets default values
AShooterChar::AShooterChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AShooterChar::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterChar::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterChar::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterChar::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterChar::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

// Called when the game starts or when spawned
void AShooterChar::BeginPlay()
{
	Super::BeginPlay();
	PlayerRangedWeapon = GetWorld()->SpawnActor<ARangedWeapon>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	PlayerRangedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	PlayerRangedWeapon->SetOwner(this);
	APlayerController* Player = Cast<APlayerController>(GetController());
	if (Player != nullptr) {
		MaxHealth = 200.0f;
		Health = MaxHealth;
	}
	Health = MaxHealth;
}



void AShooterChar::Shoot()
{
	PlayerRangedWeapon->PullTrigger();
}

float AShooterChar::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health Left %f"), Health);
	if (Health == 0) {
		AThirdPersonShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AThirdPersonShooterGameModeBase>();
		if (GameMode != nullptr) {
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			if (PlayerController == nullptr) {
				DetachFromControllerPendingDestroy();
				GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
			GameMode->PawnKilled(this);
		}
		PlayerDead = true;
	}
	else {
		PlayerDead = false;
	}
	return DamageToApply;
}

// Called every frame
void AShooterChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AShooterChar::IsDead() const
{
	
	return PlayerDead;
}

float AShooterChar::GetHealthPercent() const
{
	return Health/MaxHealth;
}



// Called to bind functionality to input
void AShooterChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterChar::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterChar::LookUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterChar::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterChar::LookUpRate);
	PlayerInputComponent->BindAxis("LookRightRate", this, &AShooterChar::LookRightRate);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShooterChar::Shoot);





}

