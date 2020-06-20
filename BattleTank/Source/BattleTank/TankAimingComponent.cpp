// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds) {
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringStatus::Aiming;
	}
	else {
		FiringState = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {

	this->Barrel = BarrelToSet;
	this->Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret))  { return; }

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(TEXT("Projectile"));
	//const TArray<AActor*, FDefaultAllocator> empty;

	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		FireLaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
		//FCollisionResponseParams::DefaultResponseParam,
		//empty,
		//true
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
		
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel && Turret)) { return; }

	//Get the difference between current barrel rotation and AimDirection
	FRotator AimRotation = AimDirection.Rotation();
	
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator DeltaBarrelRotator = AimRotation - BarrelRotation;
	
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator DeltaTurretRotator = AimRotation - TurretRotation;

	Barrel->Elevate(DeltaBarrelRotator.Pitch);
	Turret->Rotate(DeltaTurretRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringStatus::Reloading) {

		if (!ensure(Barrel && ProjectileBlueprint)) { return; }

		//Spawn a projectile at the socket location on the barrel
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(TEXT("Projectile")),
			Barrel->GetSocketRotation(TEXT("Projectile"))
			);

		Projectile->LaunchProjectile(FireLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01f);
}

