// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrel(UStaticMeshComponent* BarrelToSet)
{
	this->Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) {
		return;
	}

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
		LaunchSpeed,
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
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Get the difference between current barrel rotation and AimDirection
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();

	FRotator DeltaRotator = AimRotation - BarrelRotation;

	UE_LOG(LogTemp, Warning, TEXT("AimRotation: %s"), *AimRotation.ToString());

	//Get the pitch and yaw angle to point toward the AimDirection

	//Move the barrel
}

